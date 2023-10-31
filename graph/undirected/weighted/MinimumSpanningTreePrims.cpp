// minimum spanning tree in undirected weighted graph using prims Algorithm
class Solution {

	class Compare{
	public:
		bool operator()(const auto& x, const auto& y) {
			return x[2] > y[2];
		}
	};

	vector<int> getMinimumWeightedEdge(vector<vector<int>>& edges) {
		int edgeCount = 0, minWeight = 1000000;
		vector<int> minWeightEdge{-1, -1, minWeight};
		for(int i=0;i<edges.size();i++) {
			if(edges[i][2] < minWeightEdge[2]) {
				minWeightEdge = edges[i];
			}
		}
		return minWeightEdge;
	}

	vector<vector<vector<int>>> buildGraph(int vertexCount, vector<vector<int>> edges) {
		vector<vector<vector<int>>> graph(vertexCount, vector<vector<int>>());
		for(int i=0;i<edges.size();i++) {
			graph[edges[i][0]].push_back(vector<int>{edges[i][1], edges[i][2]});
			graph[edges[i][1]].push_back(vector<int>{edges[i][0], edges[i][2]});
		}
		return graph;
	}

	void insertUnvisitedVertexConnectedToGivenVertex(int vertex, auto& graph, auto& visited, auto& pq) {
		auto& connectedVertexList = graph[vertex];
		for(int i=0;i<connectedVertexList.size();i++) {
			vector<int> connectedVertex = connectedVertexList[i];
			if(visited[connectedVertex[0]] == false) {
				pq.push(vector<int>{vertex, connectedVertex[0], connectedVertex[1]});
		    }
	    }
    }

public:
	vector<vector<int>> createMinimumSpanningTree(int n, vector<vector<int>> edges) { // edge -> [source, destination, weight]
		int edgeCount = edges.size();
		
		// get minimum weighted edge
		vector<int> minimumWeightedEdge = getMinimumWeightedEdge(edges);
		
		vector<vector<vector<int>>> graph = buildGraph(n, edges);
		vector<vector<int>> minimumSpanningTree;

		priority_queue<vector<int>, vector<vector<int>>, Compare> pq;
		vector<bool> visited(n, false);
		visited[minimumWeightedEdge[0]] = true;
		// pq.push(minimumWeightedEdge);
		insertUnvisitedVertexConnectedToGivenVertex(minimumWeightedEdge[0], graph, visited, pq);
		
		int idealEdgeCount = n - 1, minimumSpanningTreeEdgeCount = 0;
		while(minimumSpanningTreeEdgeCount < idealEdgeCount && pq.size()) {
			vector<int> v = pq.top();
			pq.pop();
			if(visited[v[1]] == false) {
				visited[v[1]] = true;
				minimumSpanningTree.push(v);
				insertUnvisitedVertexConnectedToGivenVertex(v[1], graph, visited, pq);
				minimumSpanningTreeEdgeCount++;
			}
		}
		return minimumSpanningTree;
	}
};