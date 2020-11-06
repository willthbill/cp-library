struct Shortest_path{
    // could add support for number of shortest paths and so on...
    // 0-indexed nodes
    int N;
    vector<vector<int>> adj;
    vector<int> dist; // distance to node, INT_MAX if not visited
    vector<int> prev; // previous node, -2 if no previous node, -1 if not visited
    Shortest_path(){}
    Shortest_path(vector<vector<int>>& _adj){
        adj = _adj;
        N = (int)adj.size();
    }
	struct QItem{
		int dist, node, prev;
	};
    vector<int>& run(int src){ // returned as reference
		dist = vector<int> (N, INT_MAX);
		prev = vector<int> (N, -1);
		queue<QItem> q;
		q.push({0, src, -2});
		while(!q.empty()){
			auto curr = q.front(); q.pop();
			if(prev[curr.node] != -1) continue;
			prev[curr.node] = curr.prev; 
			dist[curr.node] = curr.dist;
			for(auto& e : adj[curr.node]){
				if(prev[e] == -1){
					q.push({curr.dist + 1, e, curr.node});
				}
			}
		}
		return dist;
    }
};
