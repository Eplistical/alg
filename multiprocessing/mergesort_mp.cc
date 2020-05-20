#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * This program implemented the following 3 functions:
 *  Normal merge sort (recursive)
 *  Multi-threading merge sort (with pthread)
 *  Multi-processing merge sort (with fork+pipe)
 *
 *  and compare their results.
 *  standard C qsort function is used for benchmarking.
 */


// --- quick sort --- //


int cmpfunc (const void * a, const void * b) {
   // qsort compare func
   return ( *(int*)a - *(int*)b );
}

void sortWithQuickSort(int N, int* arr) {
    // qsort 
    printf("Before NM quick sort: ");
    for (int i = 0; i < N; ++i) {
        printf("%8d ", arr[i]);
    }
    printf("\n");
    // copy arr
    int* sortedArr = (int*) malloc(sizeof(int) * N);
    for (int i = 0; i < N; ++i) {
        sortedArr[i] = arr[i];
    }
    // sort
    qsort(sortedArr, N, sizeof(int), cmpfunc);
    // output
    printf("After  NM quick sort: ");
    for (int i = 0; i < N; ++i) {
        printf("%8d ", sortedArr[i]);
    }
    printf("\n\n");
    free(sortedArr);
}


// --- normal merge sort --- //


void merge(const int* a, int la, int ra, const int* b, int lb, int rb, int* merged) {
    // merge two arrays a & b -> merged
    int ia = la;
    int ib = lb;
    int k = 0;
    while (ia <= ra and ib <= rb) {
        if (a[ia] <= b[ib]) {
            merged[k] = a[ia];
            ia += 1;
        }
        else {
            merged[k] = b[ib];
            ib += 1;
        }
        k += 1;
    }
    while (ia <= ra) {
        merged[k] = a[ia];
        ia += 1;
        k += 1;
    }
    while (ib <= rb) {
        merged[k] = b[ib];
        ib += 1;
        k += 1;
    }
}


void mergesort(int* arr, int l, int r) {
    // normal merge sort impl
    if (r - l < 1) {
        return ;
    }
    else {
        int* mergedArr = (int*) malloc(sizeof(int) * (r - l + 1));

        const int m = (l + r) >> 1;
        mergesort(arr, l, m);
        mergesort(arr, m+1, r);
        merge(arr, l, m, arr, m+1, r, mergedArr);
        for (int i = l; i <= r; ++i) {
            arr[i] = mergedArr[i-l];
        }
    }
}


void sortWithMergeSort(int N, int* arr) {
    // normal merge sort 
    printf("Before NM merge sort: ");
    for (int i = 0; i < N; ++i) {
        printf("%8d ", arr[i]);
    }
    printf("\n");
    // copy arr
    int* sortedArr = (int*) malloc(sizeof(int) * N);
    for (int i = 0; i < N; ++i) {
        sortedArr[i] = arr[i];
    }
    // sort 
    mergesort(sortedArr, 0, N-1);
    // output
    printf("After  NM merge sort: ");
    for (int i = 0; i < N; ++i) {
        printf("%8d ", sortedArr[i]);
    }
    printf("\n\n");
    free(sortedArr);
}


// --- multi-threading merge sort --- //


struct thread_args_t {
    int l;
    int r;
    int* arr;
};


void* mergesort_mt(void* thread_args) {
    thread_args_t* args = (thread_args_t*) thread_args;
    const int l = args->l;
    const int r = args->r;
    int* arr = args->arr;
    // multi-threading merge sort impl
    if (r - l < 1) {
        return NULL;
    }
    else {
        int* mergedArr = (int*) malloc(sizeof(int) * (r - l + 1));
        const int m = (l + r) >> 1;
        // create threads
        pthread_t thl;
        pthread_t thr;
        thread_args_t argsl { l, m, arr };
        thread_args_t argsr { m+1, r, arr };
        // run w/ threads 
        pthread_create(&thl, NULL, mergesort_mt, &argsl);
        pthread_create(&thr, NULL, mergesort_mt, &argsr);
        void* rst;
        pthread_join(thl, &rst);
        pthread_join(thr, &rst);
        // merge
        merge(arr, l, m, arr, m+1, r, mergedArr);
        for (int i = l; i <= r; ++i) {
            arr[i] = mergedArr[i-l];
        }
    }
    return NULL;
}


void sortWithMergeSortMT(int N, int* arr) {
    // multi-threading merge sort 
    printf("Before MT merge sort: ");
    for (int i = 0; i < N; ++i) {
        printf("%8d ", arr[i]);
    }
    printf("\n");
    // copy arr
    int* sortedArr = (int*) malloc(sizeof(int) * N);
    for (int i = 0; i < N; ++i) {
        sortedArr[i] = arr[i];
    }
    // sort 
    thread_args_t args { 0, N-1, sortedArr };
    mergesort_mt((void*) (&args));
    // output
    printf("After  MT merge sort: ");
    for (int i = 0; i < N; ++i) {
        printf("%8d ", sortedArr[i]);
    }
    printf("\n\n");
    free(sortedArr);
}



// --- multi-processing merge sort --- //


void mergesort_mp(int* arr, int l, int r) {
    // normal merge sort impl
    if (r - l < 1) {
        return ;
    }
    else {
        int* mergedArr = (int*) malloc(sizeof(int) * (r - l + 1));
        const int m = (l + r) >> 1;

        int myPipeP2Cl[2];
        int myPipeP2Cr[2];
        int myPipeC2Pl[2];
        int myPipeC2Pr[2];
        pipe(myPipeP2Cl);
        pipe(myPipeP2Cr);
        pipe(myPipeC2Pl);
        pipe(myPipeC2Pr);

        pid_t pidl, pidr;
        if ((pidl = fork()) > 0) {
            if ((pidr = fork()) > 0) {
                // Parent
                close(myPipeP2Cl[0]);
                close(myPipeP2Cr[0]);
                close(myPipeC2Pl[1]);
                close(myPipeC2Pr[1]);
                // send arr size
                const int Nl = m - l + 1;
                const int Nr = r - m;
                write(myPipeP2Cl[1], &Nl, sizeof(int));
                write(myPipeP2Cr[1], &Nr, sizeof(int));
                // send arr content & receive sorted results
                if (Nl > 1) {
                    write(myPipeP2Cl[1], arr+l, Nl * sizeof(int));
                    read(myPipeC2Pl[0], arr+l, Nl * sizeof(int));
                }
                if (Nr > 1) {
                    write(myPipeP2Cr[1], arr+m+1, Nr * sizeof(int));
                    read(myPipeC2Pr[0], arr+m+1, Nr * sizeof(int));
                }
                waitpid(pidl, NULL, 0);
                waitpid(pidr, NULL, 0);
                // merge data segments
                merge(arr, l, m, arr, m+1, r, mergedArr);
                // result
                for (int i = 0; i < r-l+1; ++i) {
                    arr[i] = mergedArr[i];
                }
            }
            else {
                // Child l
                close(myPipeP2Cl[1]);
                close(myPipeC2Pl[0]);
                close(myPipeP2Cr[0]);
                close(myPipeP2Cr[1]);
                close(myPipeC2Pr[0]);
                close(myPipeC2Pr[1]);
                // receive arr size
                int Nl;
                read(myPipeP2Cl[0], &Nl, sizeof(int));
                if (Nl > 1) {
                    int* arrl = (int*) malloc(sizeof(int) * Nl);
                    read(myPipeP2Cl[0], arrl, Nl * sizeof(int));
                    mergesort_mp(arrl, 0, Nl-1);
                    write(myPipeC2Pl[1], arrl, Nl * sizeof(int));
                    free(arrl);
                }
                exit(0);
            }
        }
        else {
            // Child r
            close(myPipeP2Cr[1]);
            close(myPipeC2Pr[0]);
            close(myPipeP2Cl[0]);
            close(myPipeP2Cl[1]);
            close(myPipeC2Pl[0]);
            close(myPipeC2Pl[1]);
            // receive arr size
            int Nr;
            read(myPipeP2Cr[0], &Nr, sizeof(int));
            if (Nr > 1) {
                int* arrr = (int*) malloc(sizeof(int) * Nr);
                read(myPipeP2Cr[0], arrr, Nr * sizeof(int));
                mergesort_mp(arrr, 0, Nr-1);
                write(myPipeC2Pr[1], arrr, Nr * sizeof(int));
                free(arrr);
            }
            exit(0);
        }
    }
}


void sortWithMergeSortMP(int N, int* arr) {
    // multi-processing merge sort 
    printf("Before MP merge sort: ");
    for (int i = 0; i < N; ++i) {
        printf("%8d ", arr[i]);
    }
    printf("\n");
    // copy arr
    int* sortedArr = (int*) malloc(sizeof(int) * N);
    for (int i = 0; i < N; ++i) {
        sortedArr[i] = arr[i];
    }
    // sort 
    mergesort_mp(sortedArr, 0, N-1);
    // output
    printf("After  MP merge sort: ");
    for (int i = 0; i < N; ++i) {
        printf("%8d ", sortedArr[i]);
    }
    printf("\n\n");
    free(sortedArr);
}



int main(int argc, char** argv) {
    int N = 10;
    if (argc > 1) {
        N = atoi(argv[1]);
    }
    const int seed = time(NULL);
    srand(seed);
    // generate & show original array
    int* arr = (int*) malloc(sizeof(int) * N);
    for (int i = 0; i < N; ++i) {
        arr[i] = rand() % 1000000 - 50000;
    }
    printf("\n");

    // get correct answer with qsort
    sortWithQuickSort(N, arr);

    // get merge sort result 
    sortWithMergeSort(N, arr);

    // get multithread merge sort result
    sortWithMergeSortMT(N, arr);

    // get multiprocess merge sort result
    sortWithMergeSortMP(N, arr);

    free(arr);
    return 0;
}
