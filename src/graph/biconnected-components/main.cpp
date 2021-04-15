struct Component { // you can delete this struct if you don't want to use it, but it is very useful for handling components separately
	map<int, int> from, to;
	vector<vector<pair<int,int>>> adj;
	Component(vector<int>& nodes, vector<pair<pair<int, int>, int>> edges) {
		int idx = 0;
		for (int node : nodes) {
			from[node] = idx;
			to[idx] = node;
			idx++;
		}
		adj = vector<vector<pair<int, int>>>(idx);
		for (auto e : edges) {
			int a = from[e.fs.fs];
			int b = from[e.fs.sc];
			adj[a].pb({ b, e.sc });
		}
	}
};
struct BiconnectedComponents {
	int ROOT;
	vector<bool> vis, points;
	vector<int> low, disc, minSubtree, curs;
	vector<vector<int>> comps;
	vector<vector<pair<pair<int, int>, int>>> compEdges;
	vector<vector<pair<int, int>>> adj;
	BiconnectedComponents(vector<vector<pair<int, int>>> _adj, int root) : adj(_adj), ROOT(root) { }
	int findArticulationPoints(int at, int& t) {
		if (vis[at])
			return INT_MAX; // will never happen since I check vis before entering a node
		vis[at] = true;
		disc[at] = t++;
		int mn = INT_MAX;
		int cnt = 0;
		for (pair<int, int> nxt : adj[at]) {
			if (vis[nxt.fs]) {
				low[at] = min(low[at], disc[nxt.fs]);
			}
			else {
				cnt++;
				int val = findArticulationPoints(nxt.fs, t);
				mn = min(mn, val);
				if (disc[at] <= val && at != ROOT) {
					points[at] = true;
				}
			}
		}
		if (at == ROOT && cnt > 1)
			points[at] = true;
		return minSubtree[at] = min(mn, low[at]);
	}

	void findBiconnectedComponents(int at, int cur, int& next) {
		if (vis[at])
			return;
		vis[at] = true;
		if (comps.size())
			comps[cur].pb(at);
		curs[at] = cur;
		for (auto nxt : adj[at]) {
			int edgeLabel;
			pair<pair<int, int>, int> edge = { {at, nxt.fs}, nxt.sc };
			if (!vis[nxt.fs]) {
				if (minSubtree[nxt.fs] >= disc[at]) {
					edgeLabel = next;
					comps.pb({ at });
					compEdges.pb({});
					next++;
					findBiconnectedComponents(nxt.fs, next - 1, next);
				}
				else {
					edgeLabel = cur;
					findBiconnectedComponents(nxt.fs, cur, next);
				}
			}
			else {
				edgeLabel = (disc[at] < disc[nxt.fs] ? curs[nxt.fs] : cur);
			}
			compEdges[edgeLabel].pb(edge);
		}
	}
	// returns a pair of a bool vector of articulation points, a 2d vector containing the components, and a 2d vectors of edges corresponding to the edges of
	// their respective component in the previous vector
	// Fx. component number 1 is at index 1 of the vector<vector<int>> and component 1's edges is at index 1 of the vector<vector<pair<pair<int,int>, int>>>
	pair<vector<bool>, pair<vector<vector<int>>, vector<vector<pair<pair<int, int>, int>>>>> findArticulationPointsAndComponents(vector<vector<pair<int, int>>>& adj) {
		int n = adj.size();
		vis = vector<bool>(n, false);
		points = vector<bool>(n, false);
		disc = vector<int>(n, -1);
		low = vector<int>(n, INT_MAX);
		minSubtree = vector<int>(n, -1);
		int t = 0;
		findArticulationPoints(ROOT, t);

		t = 0;
		vis = vector<bool>(n, false);
		int next = 0;
		curs = vector<int>(n, -1);
		findBiconnectedComponents(ROOT, -1, next);

		return { points, {comps, compEdges } };
	}
};
