#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
std::vector<string> split(const string &);



/*
 * Complete the 'bfs' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 *  3. 2D_INTEGER_ARRAY edges
 *  4. INTEGER s
 */

constexpr int EDG_WT { 6 };

class Node {
public:
    Node(int num) : id(num) {};
    const int id;
    std::vector<int> connections {};
    
    bool operator ==(const Node* rhs) const {
        return (id == rhs->id);
    }
    bool operator !=(const Node* rhs) const {
        return !(this==rhs);
    }
};

std::vector<int> bfs(int n, int m, std::vector<std::vector<int>> edges, int s) {
    std::cout << "n:" << n << "|m:" << m << "|s:" << s << std::endl;
    std::vector<std::unique_ptr<Node>> nodes {};
    for (int i=1; i<=n; ++i) {
        nodes.push_back(std::move(std::make_unique<Node>(i)));
    }
    for (const auto& edg : edges) {
        std::cout << "edg:" << edg[0] << " " << edg[1] << std::endl;
        auto& n1 = nodes[edg[0]-1];
        auto& n2 = nodes[edg[1]-1];
        if(std::find(n1->connections.cbegin(), n1->connections.cend(), n2->id) == n1->connections.cend()) { // edge not already added
            n1->connections.push_back(n2->id); 
            n2->connections.push_back(n1->id); //undirected
        }
    }

    std::vector<int> rootDist(n, -1);
    std::vector<bool> visited(n, false);
    auto visit = [&rootDist, &visited] (int id, int depth) {
        id = id-1; //for index on vector
        rootDist[id] = EDG_WT*depth;
        visited[id] = true;
    };

    std::queue<std::pair<int, int>> nextNode {};
    nextNode.push(std::make_pair(0, s)); // push root
    while (!nextNode.empty()) {
        const int nodeDepth = nextNode.front().first;
        const auto& curr = nodes[nextNode.front().second-1];
        visit(curr->id, nodeDepth);
        nextNode.pop();
        for (const int conn : curr->connections) {
            if (visited[conn-1]) { continue; }
            nextNode.push(std::make_pair(nodeDepth+1, conn));
        }
    }
    auto it = rootDist.begin();
    std::advance(it, s-1);
    rootDist.erase(it); // remove root dist
    return rootDist;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        std::vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        std::vector<std::vector<int>> edges(m);

        for (int i = 0; i < m; i++) {
            edges[i].resize(2);

            string edges_row_temp_temp;
            getline(cin, edges_row_temp_temp);

            std::vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int edges_row_item = stoi(edges_row_temp[j]);

                edges[i][j] = edges_row_item;
            }
        }

        string s_temp;
        getline(cin, s_temp);

        int s = stoi(ltrim(rtrim(s_temp)));

        std::vector<int> result = bfs(n, m, edges, s);

        for (size_t i = 0; i < result.size(); i++) {
            fout << result[i];

            if (i != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

std::vector<string> split(const string &str) {
    std::vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

/* input in stdin
2
4 2
1 2
1 3
1
3 1
2 3
2
*/
