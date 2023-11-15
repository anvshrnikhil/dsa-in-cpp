/**
 * getting least common ancestor in log(N) time complexity
*/

#include <bits/stdc++.h>
using namespace std;

int k = 0;
vector<vector<int>> parent;
vector<int> depth;
vector<vector<int>> graph;

int LOG(int n) {
    for(int i=0;i<31;i++)
        if(n < (1 << i)) 
            return i;
    return 30;
}

/**
 * passing current node and its parent node as parameters
*/
void dfs(int node, int par = -1) {
    for(auto connNode : graph[node]) {
        if(connNode != par) {
            depth[connNode] = depth[node] + 1;
            parent[connNode][0] = node; // binary lifting store parent nodes
            dfs(connNode, node);
        }
    }
}

void prework(int n, vector<vector<int>> edges) {
    // store log n parents
    k = LOG(n) + 1;
    parent = vector<vector<int>>(n, vector<int>(k, 0));
    depth = vector<int>(n, 0);
    
    graph = vector<vector<int>>(n, vector<int>());
    for(int i=0;i<edges.size();i++) {
        graph[edges[i][0]].push_back(edges[i][1]);
        graph[edges[i][1]].push_back(edges[i][0]);
    }

    dfs(0);

    //binary lifting logic to store parent nodes
    for(int i=1;i<k;i++) {
        for(int j=0;j<n;j++) {
            int par = parent[j][i-1];
            parent[j][i] = parent[par][i-1];
        }
    }
}

int lca(int a, int b) {
    if(depth[a] < depth[b])
        swap(a,b);

    int diff = depth[a] - depth[b];

    for(int i=0;i<k;i++) {
        if(diff & (1<<i)) {
            a = parent[a][i]; // using binary lifting parent nodes
        }
    }

    if(a == b)
        return a;

    for(int i=k-1;i>=0;i--) {
        if(parent[a][i] != parent[b][i]) { //using binary lifting parent nodes
            a = parent[a][i];
            b = parent[b][i];
        }
    }

    return parent[a][0];
}

bool test_basicScenario() {
    //       0
    //     /  \
    //    1    2
    //       / | \
    //     3  4  5
    //    / \
    //   6   7
    int n = 8; // no of vertices
    vector<vector<int>> edges{ vector<int>{0,1}, vector<int>{0,2}, 
                                vector<int>{2,3}, vector<int>{2,4},
                                vector<int>{2,5}, vector<int>{3,6}, vector<int>{3,7} };
    
    // builds the graph and store parents at powers of 2.
    prework(n, edges);

    vector<int> actualResult = vector<int>{ lca(6, 5), lca(0, 1), lca(0,4), lca(1, 7), lca(3, 4), lca(2,5), lca(6,7), lca(7, 4)};
    vector<int> expectedResult = vector<int>{ 2, 0, 0, 0, 2, 2, 3, 2 };
    int isSame = true;
    for(int i=0;i<expectedResult.size();i++) {
        isSame = isSame && expectedResult[i] == actualResult[i];
    }
    return isSame;
}

bool testSuite() {
    bool allTestsPassed = true;
    allTestsPassed = allTestsPassed && test_basicScenario();
    return allTestsPassed;
}

int main() {
    cout << (testSuite() ? "PASS" : "FAIL") << "\n";
    cout << "tests completed\n";
    return 0;
}