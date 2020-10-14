struct binary_lifting // Rooted at 0, 0-indexed
{
	int n, levels, root;
	vector<int> par;
	vector<vector<int>> edg;
	vector<vector<int>> jump;
	binary_lifting(int _n, int _levels, int _root) : n(_n), levels(_levels), root(_root)
	{
		jump = vector<vector<int>>(n + 1, vector<int>(levels));
		edg = vector<vector<int>>(n + 1);
		par = vector<int>(n + 1);
		par[root + 1] = 0;
	}
	void add_edge(int a, int b) // must be parent first and then child
	{
		edg[a + 1].pb(b + 1);
		edg[b + 1].pb(a + 1);
	}
	void assign_parents()
	{
		stack<int> s;
		s.push(root + 1);
		vector<bool> vis(n + 1);
		vis[root + 1] = true;
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
