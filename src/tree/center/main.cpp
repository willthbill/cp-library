struct tree_center {
	int n;
	vector<vector<int>> adj;
	tree_center(vector<vector<int>>& _adj) : adj(_adj), n(_adj.size()) {}
	void dfs(int at, vector<int>& dist, vector<int>& par, int p=-1) {
		dist[at] = p == -1 ? 0 : dist[p] + 1;
		par[at] = p;
		for(int nxt : adj[at]) {
			if(nxt != p) {
				dfs(nxt, dist, par, at);
			}
		}
	}
	 // returns ((x, x), d) if there is one center and ((x,y), d) if x,y are both centers
	 // d is the diameter of the tree
	pair<pair<int,int>, int> get_tree_center() {		
		vector<int> dist(n), par(n);
		dfs(0, dist, par);
		int mxnode = 0;
		rep(i,0,n) if(dist[i] > dist[mxnode]) mxnode = i;
		dfs(mxnode, dist, par);
		int diameter = 0;
		rep(i,0,n) if(dist[i] > diameter) diameter = dist[i];
		if(diameter % 2 == 0) {
			int center = 0;
			rep(i,0,n) if(dist[i] > dist[center]) center = i;
			for(int k = 0; k < diameter / 2; k++) center = par[center];
			return {{center, center}, diameter};
		}else {
			int center1 = 0;
			rep(i,0,n) if(dist[i] > dist[center1]) center1 = i;
			for(int k = 0; k < diameter / 2; k++) center1 = par[center1];
			dfs(center1, dist, par);
			int center2 = 0;
			rep(i,0,n) if(dist[i] > dist[center2]) center2 = i;
			for(int k = 0; k < diameter / 2; k++) center2 = par[center2];
			return {{center1, center2}, diameter};
		}
	}
};