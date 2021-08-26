%include<tree/binary_lifting>%

struct LCA : public binary_lifting {
	vector<int> dist;
	LCA(int _n, int _levels, int _root) : binary_lifting(_n, _levels, _root) {
		dist = vector<int>(n + 1);
		dist[root] = 0;
	}
	void build_lca() {
		build();
		stack<int> s;
		vector<bool> vis(n + 1, false);
		s.push(root), vis[root] = true;
		while(s.size()){
			int cur = s.top();
			s.pop();
			for(int nxt : edg[cur]) {
				if(!vis[nxt]) {
					vis[nxt] = true;
					s.push(nxt);
					dist[nxt] = dist[cur] + 1;
				}
			}
		}
	}
	int lca(int a, int b) {
		a++,b++;
		int da = dist[a], db = dist[b];
		a = query(a - 1, max(0, da - db)) + 1, b = query(b - 1, max(0, db - da)) + 1;
		if(a == b) return a - 1;
		for(int i = levels - 1; i >= 0; i--)
			if(jump[a][i] != jump[b][i])
				a = jump[a][i], b = jump[b][i];
		return par[a] - 1;
	}
};
