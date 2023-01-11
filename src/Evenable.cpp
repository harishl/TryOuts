#include <vector>
#include <algorithm>

class Node {
    const int id;
    std::vector<int> connections {};
    Node(int ID) : id(ID) {}
};

class Solution {
public:
    bool isPossible(int n, std::vector<std::vector<int>>& edges) {
        // nodeConnections[node] = list of all other nodes connected to node
        std::vector<std::vector<int>> nodeConnections (n+1); 
        for (const auto& e : edges) {
            int n1 = e[0];
            int n2 = e[1];
            if (n1 == n2) { continue; } //ignore self loop
            auto& nodesConnectedToN1 = nodeConnections[n1];
            auto& nodesConnectedToN2 = nodeConnections[n2];
            if (std::find(nodesConnectedToN1.begin(), nodesConnectedToN1.end(), n2) == nodesConnectedToN1.end()) { // don't add duplicate edges
                nodesConnectedToN1.push_back(n2);
                nodesConnectedToN2.push_back(n1);
            }
        }

        std::vector<int> nodesWithOddConnections {};
        for (int i=1; i<=n; ++i)
        {
            const auto& cxns = nodeConnections[i];
            if (cxns.size()%2 == 1) {
                nodesWithOddConnections.push_back(i);
            }
        }
        if (nodesWithOddConnections.size()%2 == 1) { return false; }
        else if (nodesWithOddConnections.size() > 4) { return false; }
        else {
            for (int nodeWithOddConn : nodesWithOddConnections) 
            {
                // if node is already connected to all other edges, it is not possible to make it have an even degree
                if (nodeConnections[nodeWithOddConn].size() == (n-1)) { return false; } 
            }
            std::map<int, vector<int>> pairable;
            for (int i=0; i<nodeWithOddConn.size(); ++i)
            {
                
                for (int j=i+1; j<nodeWithOddConn.size(); ++j) 
                {
                    const auto& conNodes = nodeConnections[j];
                    if (std::find(conNodes.begin(), conNodes.end(), i) == conNodes.end()) {
                        pairable[i] == j
                    }
                }
            }
            return true; 
        } 
    }
};

int main() {

}