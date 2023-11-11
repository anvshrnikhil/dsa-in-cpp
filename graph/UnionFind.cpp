class UnionFind {
public:
    vector<int> group;
    vector<int> rank;

    UnionFind(int n) {
        group = vector<int>(n);
        rank = vector<int>(n);
        for(int i=0;i<n;i++)
            group[i] = i;
    }

    int find(int node) {
        if(group[node] != node) {
            group[node] = find(group[node]);
        }
        return group[node];
    }

    void join(int node1, int node2) {
        int group1 = find(node1);
        int group2 = find(node2);

        if(group1 == group2)
            return;

        if(rank[group1] > rank[group2])
            group[group2] = group1;
        if(rank[group2] > rank[group1])
            group[group1] = group2;
        else {
            group[group2] = group1;
            rank[group2] += 1;
        }
    }

    bool areConnected(int node1, int node2) {
        int group1 = find(node1);
        int group2 = find(node2);
        return group1 == group2;
    }
};