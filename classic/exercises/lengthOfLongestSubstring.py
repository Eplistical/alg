'''
Given a string, find the length of the longest substring without repeating characters.
'''

class Solution:
    def lengthOfLongestSubstring(self, s):
        maxL = 0
        cur = set()

        i = 0
        for j, c in enumerate(s):
            if c not in cur:
                cur.add(c)
            else:
                while s[i] != c:
                    cur.remove(s[i])
                    i += 1
                i += 1
            maxL = max(maxL, j - i + 1)
        return maxL

    def test(self, s):
        print(s, self.lengthOfLongestSubstring(s))


S = Solution()
S.test('asbkksdfxlka')
S.test('aaaaaaaaaaa')
S.test('')
S.test('aab')
S.test('aabbbbbccccab')
