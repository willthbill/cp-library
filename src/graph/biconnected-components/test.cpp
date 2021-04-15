// https://lthchallenge21.kattis.com/problems/lthchallenge21.ortestpath
#include "bits/stdc++.h"
#include<sstream>
using namespace std;
// shortcuts
#define pb push_back
#define fs first
#define sc second
#define mkp make_pair
#define all(_v) _v.begin(),_v.end()
#define ll long long
#define fun(ret,x,...) function<ret(__VA_ARGS__)> x;x=[&](__VA_ARGS__)->ret
#define Void(x,...) fun(void,x,__VA_ARGS__)
// reading
#define multitest signed __T; cin >> __T; while(__T--)
template<typename T>void _read(T& t);
template<typename T>void _read(vector<T>& v);
template<typename T1, typename T2>void _read(pair<T1, T2>& p);
template<typename T>void _read(T& t) { cin >> t; }
template<typename T>void _read(vector<T>& v) { for (unsigned _i = 0; _i < v.size(); _i++)_read(v[_i]); }
template<typename T1, typename T2>void _read(pair<T1, T2>& p) { _read(p.first); _read(p.second); }
void _masterread() {}
template<typename T, typename... V>void _masterread(T& t, V& ... v) { _read(t); _masterread(v...); }
#define re(...)_masterread(__VA_ARGS__)
// writing
stringstream _effout;
#ifdef __local__
#define _stout cout
#else
#define _stout _effout
#endif
template<typename T>void _print(T t);
template<typename T>void _print(vector<T>& v);
template<typename T1, typename T2>void _print(pair<T1, T2>& p);
template<typename T>void _print(T t) { _stout << t; }
template<typename T>void _print(vector<T>& v) { for (unsigned _i = 0; _i < v.size(); _i++)_print(v[_i]), _stout << (_i == v.size() - 1 ? "" : " "); }
template<typename T1, typename T2>void _print(pair<T1, T2>& p) { _print(p.first); _stout << " "; _print(p.second); }
void _masterprint() {}
template<typename T, typename... V>void _masterprint(T t, V... v) { _print(t); if (sizeof...(v))_stout << " "; _masterprint(v...); }
#define pr(...)_masterprint(__VA_ARGS__)
#define prl(...) (_masterprint(__VA_ARGS__),_stout<<endl)
// debugging, instead of a similar implementation for each container type a seperate generic function could be used
template <typename T> void _debug(T t); //forward declaration
template<typename T1, typename T2> void _debug(pair<T1, T2> p);
template<typename T> void _debug(vector<T> v);
template<typename T> void _debug(set<T>s);
template<typename T> void _debug(unordered_set<T>s);
template<typename T> void _debug(multiset<T>s);
template<typename T> void _debug(unordered_multiset<T>s);
template<typename T1, typename T2> void _debug(map<T1, T2>mp);
template<typename T1, typename T2> void _debug(unordered_map<T1, T2>mp);
template<typename T1, typename T2> void _debug(multimap<T1, T2>mp);
template<typename T1, typename T2> void _debug(unordered_multimap<T1, T2>mp); // end forward declaration
template <typename T> void _debug(T t) { cerr << t; }
template<typename T1, typename T2> void _debug(pair<T1, T2> p) { cerr << "{"; _debug(p.first); cerr << ", "; _debug(p.second); cerr << "}"; }
template<typename T> void _debug(vector<T>v) { cerr << "("; for (unsigned _i = 0; _i < v.size(); _i++)_debug(v[_i]), cerr << (_i == v.size() - 1 ? "" : ", "); cerr << ")"; }
template<typename T> void _debug(set<T>s) { cerr << "("; for (auto e = s.begin(); e != s.end();)_debug(*e), cerr << ((++e) == s.end() ? "" : ", "); cerr << ")"; }
template<typename T> void _debug(unordered_set<T>s) { cerr << "("; for (auto e = s.begin(); e != s.end();)_debug(*e), cerr << ((++e) == s.end() ? "" : ", "); cerr << ")"; }
template<typename T> void _debug(multiset<T>s) { cerr << "("; for (auto e = s.begin(); e != s.end();)_debug(*e), cerr << ((++e) == s.end() ? "" : ", "); cerr << ")"; }
template<typename T> void _debug(unordered_multiset<T>s) { cerr << "("; for (auto e = s.begin(); e != s.end();)_debug(*e), cerr << ((++e) == s.end() ? "" : ", "); cerr << ")"; }
template<typename T1, typename T2> void _debug(map<T1, T2>mp) { cerr << "("; for (auto e = mp.begin(); e != mp.end();)_debug(*e), cerr << ((++e) == mp.end() ? "" : ", "); cerr << ")"; }
template<typename T1, typename T2> void _debug(unordered_map<T1, T2>mp) { cerr << "("; for (auto e = mp.begin(); e != mp.end();)_debug(*e), cerr << ((++e) == mp.end() ? "" : ", "); cerr << ")"; }
template<typename T1, typename T2> void _debug(multimap<T1, T2>mp) { cerr << "("; for (auto e = mp.begin(); e != mp.end();)_debug(*e), cerr << ((++e) == mp.end() ? "" : ", "); cerr << ")"; }
template<typename T1, typename T2> void _debug(unordered_multimap<T1, T2>mp) { cerr << "("; for (auto e = mp.begin(); e != mp.end();)_debug(*e), cerr << ((++e) == mp.end() ? "" : ", "); cerr << ")"; }
void _masterdebug() { cerr << "]" << endl; }
template<typename T, typename... V> void _masterdebug(T t, V... v) { _debug(t); if (sizeof...(v))cerr << ", "; _masterdebug(v...); }
#define debug(...)(cerr<<"["<<#__VA_ARGS__<<"] = [",_masterdebug(__VA_ARGS__))
template<typename T> void _debugall(T c, string n) { _debug("debugall: "); _debug(n); cerr << endl; for (auto _e : c) { _debug("  "); _debug(_e); cerr << endl; } } //2d vectors and similar
#define debugall(c)(_debugall(c,#c)) //2d vectors and similar
// main
void _solve();
void _test();
signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	pr(setprecision(10));
	pr(fixed);
	_solve();
#ifndef __local__
	cout << _effout.str();
#endif
}
#define int long long
#define _mt_ 0
void _solve() {
	if (_mt_) {
		multitest _test();
	}
	else {
		_test();
	}
}

// START Generated output of: graph/maxflow
// Int is capacity type
template<class Int>
struct MaxFlow {
	// ford fulkerson with dfs and capacity scaling
	// works for directed and undirected
	int N;
	bool hasbeeninitialized = false; // useful when using the reset method
	map<int, map<Int, Int>> capacity; // change this to map if memory problems
	vector<int> par;
	vector<vector<pair<int, Int>>> adjList;
	MaxFlow() {}
	// adjList[i][j] = {node, capacity}
	// might be able to handle selfloops
	MaxFlow(vector<vector<pair<int, Int>>>& _adjList) {
		N = (int)_adjList.size();
		reset(_adjList);
		hasbeeninitialized = true;
	}
	// does not reallocate large memory, n*n (capacity matrix)
	void reset(vector<vector<pair<int, Int>>>& _adjList) {
		adjList = _adjList;
		N = (int)adjList.size();
		if (hasbeeninitialized) {
			for (int i = 0; i < N; i++) {
				for (auto& e : _adjList[i]) {
					capacity[i][e.first] = 0;
				}
			}
		}
		for (int i = 0; i < N; i++) {
			for (auto& e : _adjList[i]) {
				capacity[i][e.first] += e.second;
			}
		}
		for (int i = 0; i < N; i++) {
			for (auto& e : _adjList[i]) {
				adjList[e.first].push_back({ i, 0 }); // works for undirected???
			}
		}
	}
	Int getMinFlow(int node, int p, Int constrain, int t) {
		par[node] = p;
		for (auto& e : adjList[node]) {
			int nb = e.first;
			if (nb == p || par[nb] != -1) continue;
			if (capacity[node][nb] >= constrain) {
				if (nb == t) {
					par[nb] = node;
					return capacity[node][nb];
				}
				Int temp = getMinFlow(nb, node, constrain, t);
				if (temp > 0) return min(temp, capacity[node][nb]);
			}
		}
		return 0;
	}
	// s cannot be t
	Int maxFlow(int s, int t) {
		Int flow = 0;
		Int maxCapacity = 1;
		Int constrain = 2;
		while (constrain) {
			Int minFlow = -1;
			while (1) {
				par = vector<int>(N, -1);
				minFlow = getMinFlow(s, -2, constrain, t);
				if (minFlow == 0) break;
				int node = t;
				while (node != s) {
					capacity[par[node]][node] -= minFlow;
					capacity[node][par[node]] += minFlow;
					node = par[node];
				}
				flow += minFlow;
			}
			constrain >>= 1;
		}
		return flow;
	}
};

// END Generated output of: graph/maxflow


// BEGIN code block of: graph/biconnected-components
// Standard message: The following is code from https://github.com/williamMBDK/cp-library but was copied from a local copy of the repository. Changes to the original source may have been done here.
int ROOT;
struct Component { // you can delete this struct if you don't want to use it, but it is very useful for handling components separately
	map<int, int> from, to;
	vector<vector<pair<int, int>>> adj;
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
	vector<bool> vis, points;
	vector<int> low, disc, minSubtree, curs;
	vector<vector<int>> comps;
	vector<vector<pair<pair<int, int>, int>>> compEdges;
	vector<vector<pair<int, int>>> adj;
	BiconnectedComponents(vector<vector<pair<int, int>>> _adj) : adj(_adj) { }
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

// END code block of: graph/biconnected-components

map<pair<pair<int, int>, int>, int> edgeLabels;
vector<int> findRandomPath(int u, int v, vector<vector<pair<int, int>>>& adj) {
	int n = adj.size();
	vector<bool> vis(n, false);
	vector<int> par(n, -1);
	stack<int> s({ u });
	while (s.size()) {
		int cur = s.top();
		s.pop();
		for (auto nxt : adj[cur]) {
			if (!vis[nxt.fs]) {
				vis[nxt.fs] = true;
				par[nxt.fs] = cur;
				s.push(nxt.fs);
			}
		}
	}
	if (!vis[v])
		return { -1 };
	vector<int> ans;
	for (int cur = v; cur != u; cur = par[cur]) {
		ans.pb(cur);
	}
	ans.pb(u);
	reverse(ans.begin(), ans.end());
	return ans;
}

vector<int> findComponentOrder(int u, int v, vector<vector<pair<int, int>>>& adj) {
	int n = adj.size();
	vector<bool> vis(n, false);
	vector<pair<int, int>> par(n, { -1, -1 });
	stack<int> s;
	s.push(u);
	vis[u] = true;
	while (s.size()) {
		int cur = s.top();
		s.pop();
		for (auto nxt : adj[cur]) {
			if (!vis[nxt.fs]) {
				par[nxt.fs] = { cur, nxt.sc };
				vis[nxt.fs] = true;
				s.push(nxt.fs);
			}
		}
	}
	vector<int> order;
	int bst = v;
	while (par[bst].fs != -1) {
		int nxt = par[bst].fs;
		if (!order.size() || order.back() != edgeLabels[{ {bst, nxt}, par[bst].sc}])
			order.pb(edgeLabels[{ {bst, nxt}, par[bst].sc}]);
		bst = nxt;
	}
	reverse(order.begin(), order.end());
	return order;
}

vector<int> findOrtestPath(vector<vector<pair<int, int>>> adjOrg, int s, int t) {
	int n = adjOrg.size();
	vector<vector<pair<int, int>>> adj(2 * (n + 1));
	pair<int, int> edge(-1, -1);
	for (int i = 0; i < n; i++) {
		for (pair<int, int> nxt : adjOrg[i]) {
			adj[2 * i + 1].pb({ 2 * nxt.fs, 1 });
			if (nxt.sc == 1) {
				edge = { i, nxt.fs };
			}
		}
	}
	if (edge.fs == -1ll) {
		return { -1 };
	}
	for (int i = 0; i < n; i++) {
		adj[2 * i].pb({ 2 * i + 1, 1 });
	}
	adj[2 * n] = { {2 * edge.fs, 1}, {2 * edge.sc, 1} };
	adj[2 * s + 1].pb({ 2 * n + 1, 1 });
	adj[2 * t + 1].pb({ 2 * n + 1, 1 });
	MaxFlow<int> mf(adj);
	assert(mf.maxFlow(2 * n, 2 * n + 1) == 2);
	auto cap = mf.capacity;
	vector<int> par(n, -1);
	for (int i = 0; i < n; i++) {
		for (pair<int, int> nxt : adjOrg[i]) {
			if (cap[2 * i + 1][2 * nxt.fs] == 0) {
				par[i] = nxt.fs;
				break;
			}
		}
	}
	vector<int> pref, suff;
	for (int cur = edge.fs; cur != -1; cur = par[cur]) {
		pref.pb(cur);
	}
	for (int cur = edge.sc; cur != -1; cur = par[cur]) {
		suff.pb(cur);
	}
	if (pref.back() == t)
		swap(pref, suff);
	reverse(pref.begin(), pref.end());
	for (int k : suff)
		pref.pb(k);
	return pref;
}

vector<int> findArticulationPointSubsequence(int s, int t, vector<vector<pair<int, int>>>& adj, map<pair<int, int>, bool> w, vector<int>& order) {
	vector<int> path = findRandomPath(s, t, adj);
	vector<int> ans;
	int m = path.size();
	int j = 0;
	for (int i = 0; i < m - 1; i++) {
		int a = path[i], b = path[i + 1];
		if (j < order.size() && edgeLabels[{ {a, b }, w[{a, b}]}] == order[j]) {
			ans.pb(a);
			j++;
		}
	}
	ans.pb(t);
	return ans;
}

void _test() {
	int n, m, s, t; re(n, m, s, t);
	vector<vector<pair<int, int>>> adj(n);
	map<pair<int, int>, bool> w;
	for (int i = 0; i < m; i++) {
		int a, b, c; re(a, b, c);
		adj[a].pb({ b, c });
		adj[b].pb({ a, c });
		w[{a, b}] = w[{b, a}] = c;
	}
	ROOT = s;
	if (findRandomPath(s, t, adj)[0] == -1) {
		prl(-1);
		return;
	}
	BiconnectedComponents bc(adj);
	auto res = bc.findArticulationPointsAndComponents(adj);
	vector<bool> points = res.fs;
	vector<vector<int>> comps = res.sc.fs;
	auto compEdges = res.sc.sc;
	for (int i = 0; i < comps.size(); i++) {
		for (auto e : compEdges[i])
			edgeLabels[e] = i;
	}

	vector<int> order = findComponentOrder(s, t, adj);

	auto articulationPointsSequence = findArticulationPointSubsequence(s, t, adj, w, order);
	vector<Component> components;
	for (int i = 0; i < comps.size(); i++)
		components.pb(Component(comps[i], compEdges[i]));

	bool ok = false;
	vector<int> finalAns;
	for (int i = 0; i < order.size(); i++) {
		int a = articulationPointsSequence[i];
		int b = articulationPointsSequence[i + 1];
		int comp = order[i];
		vector<int> ans = findOrtestPath(components[comp].adj, components[comp].from[a], components[comp].from[b]);
		if (ans[0] == -1)
			ans = findRandomPath(components[comp].from[a], components[comp].from[b], components[comp].adj);
		else
			ok = true;

		for (int j = 0; j < ans.size() - (i != order.size() - 1); j++)
			finalAns.pb(components[comp].to[ans[j]]);
	}

	if (ok)
		prl(finalAns);
	else
		prl(-1);
}