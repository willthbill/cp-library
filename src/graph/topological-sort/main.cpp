struct TopoSort{ // must be a DAG, O(n) complexity
	vector<vector<int>> adj;
	TopoSort(){}
	TopoSort(vector<vector<int>>& _adj){adj = _adj; res = vector<int> (adj.size(), -1);}
	int idx;
	vector<int> res;
	void dfs(int node){
		if(res[node] != -1) return;
		for(auto& e : adj[node]) dfs(e);
		res[node] = idx--;
	}
	vector<int>& run(){
		int n = (int)adj.size();
		idx = n - 1;
		for(int i = 0; i < n; i++){
			if(res[i] == -1) dfs(i);
		}
		return res;
	}
};
