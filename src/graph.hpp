#ifndef _GRAPH_HPP
#define _GRAPH_HPP

#include <vector>
#include <algorithm>

using namespace std;

namespace {

    struct Graph {
        // adjecent list graph object
        public:
            Graph(int V) {
                adjlist.resize(V);
            }
            ~Graph() = default;
        public:
            void show() const 
            {
                // print out graph
                for (int u(0); u < adjlist.size(); ++u) {
                    cout << "vertex " << u << ": => ";
                    for (int v : adjlist[u]) {
                        cout << v << " ";
                    }
                    cout << endl;
                }
            }

            void show_adjmat() const 
            {
                // print out graph in adjecent matrix form
                cout << "#\t";
                for (int u(0); u < adjlist.size(); ++u) {
                    cout << u << "\t";
                }
                cout << endl;

                for (int u(0); u < adjlist.size(); ++u) {
                    cout << u << "\t";
                    for (int v(0); v < adjlist.size(); ++v) {
                        if (find(adjlist[u].begin(), adjlist[u].end(), v) != adjlist[u].end()) {
                            cout << "T" << "\t";
                        }
                        else {
                            cout << "" << "\t";
                        }
                    }
                    cout << endl;
                }
            }

            int size() const 
            {
                // get size
                return adjlist.size();
            }

            void add_edge(int u, int v) 
            {
                // add u -> v 
                adjlist[u].push_back(v);
            }

            void connect(int u, int v) 
            {
                // add u <-> v
                add_edge(u, v);
                add_edge(v, u);
            }

        public:
            vector< vector<int> > adjlist;
    };

    // global graph buffers
    vector<bool> visited;
    vector<int> pre, post;
    int clock;

    void reset_buf(int V) {
        // reset buffers: visited, pre, post, clock
        visited.assign(V, false);
        pre.assign(V, -1);
        post.assign(V, -1);
        clock = 0;
    }

    // functions
    void preexplore(int v) {
        clock += 1;
        pre[v] = clock;
    }

    void postexplore(int v) {
        clock += 1;
        post[v] = clock;
    }

    void explore(Graph& G, int v) {
        preexplore(v);
        visited[v] = true;

        for (int u : G.adjlist[v]) {
            if (not visited[u]) {
                explore(G, u);
            }
        }
        postexplore(v);
    }

    void dfs(Graph& G) {
        for (int v(0); v < G.size(); ++v) {
            if (not visited[v]) {
                explore(G, v);
            }
        }
    }

    Graph revGraph(const Graph& G) {
        // get reversed graph GR
        Graph GR(G.size());
        for (int u(0); u < G.size(); ++u) {
            for (int v : G.adjlist[u]) {
                GR.add_edge(v, u);
            }
        }
        return GR;
    }

};

#endif // _GRAPH_HPP
