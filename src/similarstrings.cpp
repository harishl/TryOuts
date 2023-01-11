/**
Count Pairs Of Similar Strings
Difficulty: Easy
You are given a 0-indexed string array words.
Two strings are similar if they consist of the same characters.
For example, "abca" and "cba" are similar since both consist of characters 'a', 'b', and 'c'.
However, "abacba" and "bcfd" are not similar since they do not consist of the same characters.
Return the number of pairs (i, j) such that 0 <= i < j <= word.length - 1 and the two strings words[i] and words[j] are similar.
 
Example 1:
Input: words = ["aba","aabb","abcd","bac","aabc"]
Output: 2
Explanation: There are 2 pairs that satisfy the conditions:
- i = 0 and j = 1 : both words[0] and words[1] only consist of characters 'a' and 'b'. 
- i = 3 and j = 4 : both words[3] and words[4] only consist of characters 'a', 'b', and 'c'. 

Example 2:
Input: words = ["aabb","ab","ba"]
Output: 3
Explanation: There are 3 pairs that satisfy the conditions:
- i = 0 and j = 1 : both words[0] and words[1] only consist of characters 'a' and 'b'. 
- i = 0 and j = 2 : both words[0] and words[2] only consist of characters 'a' and 'b'.
- i = 1 and j = 2 : both words[1] and words[2] only consist of characters 'a' and 'b'.

Example 3:
Input: words = ["nba","cba","dba"]
Output: 0
Explanation: Since there does not exist any pair that satisfies the conditions, we return 0.
 
Constraints:
1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consist of only lowercase English letters.
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class Solution {
public:
    int similarPairs(std::vector<std::string>& words) 
    {
        for (const auto& w : words) { cleanedWords.push_back(cleanWord(w)); }
        const size_t n = words.size();
        int numSimilarPairs = 0;
        for (int i=0; i<n; ++i) 
        {
            for (int j=i+1; j<n; ++j) 
            {
                if (cleanedWords[i] == cleanedWords[j]) { numSimilarPairs++; }
            }
        }
        return numSimilarPairs;
    }

private:
    std::vector<std::string> cleanedWords {};
    std::string cleanWord(std::string word) const 
    {
        std::sort(word.begin(), word.end());
        auto last = std::unique(word.begin(), word.end());
        word.erase(last, word.end());
        return word;
    }
};

int main() 
{
    Solution soln1, soln2, soln3;
    std::vector<std::string> words1 { "aba","aabb","abcd","bac","aabc" };
    std::cout << soln1.similarPairs(words1) << std::endl;
    std::vector<std::string> words2 { "aabb","ab","ba" };
    std::cout << soln2.similarPairs(words2) << std::endl;
    std::vector<std::string> words3 { "nba","cba","dba" };
    std::cout << soln3.similarPairs(words3) << std::endl;
}
