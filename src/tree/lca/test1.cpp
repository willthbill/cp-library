#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back


struct binary_lifting // 0-indexed
{
	int n, levels, root;
	vector<int> par;
	vector<vector<int>> edg;
	vector<vector<int>> jump;
	binary_lifting(int _n, int _levels, int _root) : n(_n), levels(_levels), root(_root + 1)
	{
		jump = vector<vector<int>>(n + 1, vector<int>(levels));
		edg = vector<vector<int>>(n + 1);
		par = vector<int>(n + 1);
		par[root] = 0, par[0] = 0;
	}
	void add_edge(int a, int b) // must be parent first and then child
	{
		edg[a + 1].pb(b + 1);
		edg[b + 1].pb(a + 1);
	}
	void assign_parents()
	{
		stack<int> s;
		s.push(root);
		vector<bool> vis(n + 1);
		vis[root] = true;
		while(!s.empty())
		{
			ll cur = s.top(); s.pop();
			for(auto nxt : edg[cur])
			{
				if(!vis[nxt])
				{
					vis[nxt] = true;
					par[nxt] = cur;
					s.push(nxt);
				}
			}
		}
	}
	void build() // after all edges have been added, build sparse table
	{
		assign_parents();
		for(int i = 2; i <= n; ++i)
		{
			jump[i][0] = par[i];
		}
		for(int k = 1; k < levels; ++k)
		{
			for(int i = 2; i <= n; ++i)
			{
				jump[i][k] = jump[jump[i][k-1]][k-1];
			}
		}
	}
	int query(int start, int up) // finds the node up-levels up from start
	{
		if(up == 0) return start;
		int cur = start + 1;
		for(int i = 0; i < levels; ++i)
		{
			if(up & (1 << i))
			{
				cur = jump[cur][i];
			}
		}
		return cur - 1;
	}
};

struct LCA : public binary_lifting {
	vector<int> dist;
	LCA(int _n, int _levels, int _root) : binary_lifting(_n, _levels, _root) {
		dist = vector<int>(n + 1);
		dist[root] = 0;
	}
	void build_lca() {
		build();
		//cout << "boop" << endl;
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

int main(){
	cin.sync_with_stdio(false); cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	LCA lca(n, 18, 0);
	for(int i = 1; i < n; i++) {
		int a;
		cin >> a, a--;
		lca.add_edge(a, i);
	}
	//cout << "boop" << endl;
	lca.build_lca();
	
	//cout << "boop" << endl;
	while(q--) {
		int a, b;
		cin >> a >> b;
		cout << lca.lca(a - 1, b - 1) + 1 << endl;
	}

}

