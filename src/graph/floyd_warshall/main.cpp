template<class Int>
vector<vector<Int>> floyd_warshall(vector<vector<pair<int, Int>>>& adj, Int MX){
	int n = (int)adj.size();
	vector<vector<Int>> graph(n, vector<int>(n, MX));
	// INITIALIZE GRAPH WITH DIST 0 FROM NODE TO ITSELF
	for(int i = 0; i < n; i++) graph[i][i] = 0;
	// INPUT ALL EDGES AND UPDATE THE MIN WEIGHT
	for(int i = 0; i < n; i++){
		for(auto& edge : adj[i]){
			graph[i][edge.first] = min(graph[i][edge.first], edge.second);
		}
	}
	// FLOYD WARSHALL
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (graph[i][k] != MX && graph[k][j] != MX)
					graph[i][j] = min(graph[i][j], graph[i][k]+graph[k][j]);
			}
		}
	}
	// FLOYD WARSHALL APPROACH FOR CHECKING NEGATIVE WEIGHT CYCLE BETWEEN TWO NODES
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (graph[k][k] < 0 && graph[i][k] != MX && graph[k][j] != MX)
					graph[i][j] = -MX;
			}
		}
	}
	return graph;
}

