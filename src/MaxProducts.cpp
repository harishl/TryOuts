#include <iostream>
#include <vector>
#include <utility>

class Solution {
public:
    long maxProductSelection(const std::vector<int>& products) 
    {
        if (products.empty()) { return 0; }
        int productsSz = products.size();
        int startIdx = 0;
        int endIdx = 0;
        long maxSelection = 0;
        while(startIdx <= endIdx && endIdx<productsSz)
        {
            const auto selectionAndStart = numProducts(products, startIdx, endIdx);
            const auto selection = selectionAndStart.first;
            maxSelection = std::max(maxSelection, selection);
            std::cout << "si:" << startIdx << "|ei:" << endIdx << "|maxSelection:" << maxSelection << std::endl;
            startIdx = (maxSelection == selection)? selectionAndStart.second : startIdx;
            endIdx++;
        }
        std::cout << "start:" << startIdx << "|end:" << endIdx << std::endl;
        return maxSelection;
    }

private:
    std::pair<long, int> numProducts(const std::vector<int>& products, int s, int e) const
    {
        if (e < s || products[e] == 0) { return std::make_pair<long, int>(0, std::forward<int>(e)); } 
        long ret = 0;
        int selection = INT32_MAX;
        for (; e>=s; --e) 
        {
            // std::cout << "~" << selection-1 << "~" << products[e] << std::endl;
            selection = std::min(selection-1, products[e]);
            ret += selection;
            if (selection <= 1) { break; }
        }
        if (e < s ) { e = s; }
        return std::make_pair<long, int>(std::forward<long>(ret), std::forward<int>(e));
    }
};

int main() 
{
    std::vector<int> products { 2, 9, 4, 7, 1, 5, 5, 7, 9, 0, 0, 0, 100 };
    Solution soln;
    auto out = soln.maxProductSelection(products);
    std::cout << "max selection:" << out << std::endl;
}