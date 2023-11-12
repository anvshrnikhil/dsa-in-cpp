#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> buildGraph(int, vector<vector<int>>);

int counter = 0;
vector<int> output;

// considering unweighted and undirected graph in the use case
void dfs(int vertex, vector<vector<int>>& graph, vector<bool>& visited) 
{
    auto& connectedVertex = graph[vertex];
    int sz = connectedVertex.size();
    for(int i=0;i<sz;i++) {
        if(!visited[connectedVertex[i]]) {
            visited[connectedVertex[i]] = 1;
            output[connectedVertex[i]] = ++counter; // to store the order of visited vertex
            dfs(connectedVertex[i], graph, visited);
        }
    }
}

// test the order of visited node in dfs traversal
bool test_basicScenario() {
    //          0
    //        /   \
    //       7     3
    //           /   \
    //          6     1
    //               /
    //              2
    //            /   \
    //           4     5
    int n = 8;
    int arr[7][2] = { {0, 7}, {0, 3}, {3, 6}, {3, 1}, {1, 2}, {2, 4}, {2,5} };
    vector<vector<int>> edges;
    for(int i=0;i<n-1;i++) {
        edges.push_back(vector<int>{ arr[i][0], arr[i][1] });
    }
    vector<vector<int>> graph = buildGraph(n, edges);
    int root = 0;
    vector<bool> visited(n, false);
    output = vector<int>(n, 0);
    
    // implementation logic
    visited[root] = true;
    output[root] = ++counter;
    dfs(root, graph, visited);

    //verify output
    bool isSame = true;
    vector<int> expected{1, 5, 6, 3, 7, 8, 4, 2};
    for(int i=0;i<expected.size();i++) {
        isSame = isSame && expected[i] == output[i];
    }
    
    return isSame;
}

bool testSuite() {
    bool allTestsPassed = true;
    allTestsPassed = allTestsPassed && test_basicScenario();
    return allTestsPassed;
}

vector<vector<int>> buildGraph(int n, vector<vector<int>> edges) {
    int sz = edges.size();
    vector<vector<int>> graph(n, vector<int>());
    for(int i=0;i<sz;i++) {
        graph[edges[i][0]].push_back(edges[i][1]);
        graph[edges[i][1]].push_back(edges[i][0]);
    }
    return graph;
}

int main() {
    cout << (testSuite() ? "PASS" : "FAIL") << "\n";
    cout << "tests completed\n";
    return 0;
}