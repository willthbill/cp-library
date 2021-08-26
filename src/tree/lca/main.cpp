%include<data-structures/sparse-table-constant>%

// LCA with 0-indexed nodes, O(n lg n) build and O(1) query
struct LCA {
    int n, root;
    vector<vector<int>> adj;
    vector<pair<int,int>> levels;
    vector<int> idxinlevels;
    static pair<int,int> mn(pair<int,int> a, pair<int,int> b) {
        return min(a,b);
    }
    SPS<pair<int,int>,mn> sps;
    LCA() {}
	LCA(int n, int root = 0) : n(n), root(root), adj(vector<vector<int>> (n)) {}
	LCA(vector<vector<int>>& adj, int root = 0) : n(adj.size()), root(root), adj(adj) {
        build_lca();
    }
    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    void dfs(int node, int p = -1, int level = 0) {
        idxinlevels[node] = levels.size();
        levels.push_back({level, node});
        for(auto& ch : adj[node]) {
            if(ch == p) continue;
            dfs(ch, node, level + 1);
            levels.push_back({level, node});
        }
    }
	void build_lca() {
        idxinlevels = vector<int> (n);
        dfs(root);
        sps = SPS<pair<int,int>, mn> (levels);
    }
	int lca(int a, int b) {
        a = idxinlevels[a], b = idxinlevels[b];
        return sps.q(min(a,b), max(a,b)).second;
	}
};
