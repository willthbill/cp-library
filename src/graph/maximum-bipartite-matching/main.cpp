// https://github.com/williamMBDK/cp-library/blob/main/src/graph/maximum-bipartite-matching/main.cpp
#define NIL 0
#define INF (1<<28)
struct MBP // maximum bipartite matching, 1-INDEXED!
{
public:
	MBP(int _n, int _m) : n(_n), m(_m), sz(_n + _m + 2)
	{
		G = vector<vector<int>>(sz), match = vector<int>(sz), dist = vector<int>(sz);
	}

	void clear()
	{
		for(int i = 0; i < sz; i++)
		{
			G[i].clear();
		}
	}

	void add_edge(int a, int b)
	{
		G[a].pb(b + n);
		G[b + n].pb(a);
	}

	int hopcroft_karp() {
		int matching = 0, i;
		// match[] is assumed NIL for all vertex in G
		for (int i = 0; i < sz; i++) match[i] = NIL;
		while (bfs())
			for (i = 1; i <= n; i++)
				if (match[i] == NIL && dfs(i))
					matching++;
		return matching;
	}

private:
	vector< vector<int> > G;
	vector<int> match, dist;
	int n, m, sz;
	// n: number of nodes on left side, nodes are numbered 1 to n
	// m: number of nodes on right side, nodes are numbered n+1 to n+m
	// G = NIL[0] ? G1[G[1---n]] ? G2[G[n+1---n+m]]

	bool bfs() {
		int i, u, v, len;
		queue< int > Q;
		for (i = 1; i <= n; i++) {
			if (match[i] == NIL) {
				dist[i] = 0;
				Q.push(i);
			}
			else dist[i] = INF;
		}
		dist[NIL] = INF;
		while (!Q.empty()) {
			u = Q.front(); Q.pop();
			if (u != NIL) {
				len = G[u].size();
				for (i = 0; i < len; i++) {
					v = G[u][i];
					if (dist[match[v]] == INF) {
						dist[match[v]] = dist[u] + 1;
						Q.push(match[v]);
					}
				}
			}
		}
		return (dist[NIL] != INF);
	}

	bool dfs(int u) {
		int i, v, len;
		if (u != NIL) {
			len = G[u].size();
			for (i = 0; i < len; i++) {
				v = G[u][i];
				if (dist[match[v]] == dist[u] + 1) {
					if (dfs(match[v])) {
						match[v] = u;
						match[u] = v;
						return true;
					}
				}
			}
			dist[u] = INF;
			return false;
		}
		return true;
	}
};
