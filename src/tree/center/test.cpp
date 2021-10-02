//https://atcoder.jp/contests/abc221/tasks/abc221_f
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
#define prl(...) (_masterprint(__VA_ARGS__),_stout<<'\n')
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

// asthor
#define rep(i,a,b) for(int i = (a); i < (b); ++i)
#define iter(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end();++it)

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
		for(int i = 0; i < n; i++) if(dist[i] > dist[mxnode]) mxnode = i;
		dfs(mxnode, dist, par);
		int diameter = 0;
		for(int i = 0; i < n; i++) if(dist[i] > diameter) diameter = dist[i];
		if(diameter % 2 == 0) {
			int center = 0;
			for(int i = 0; i < n; i++) if(dist[i] > dist[center]) center = i;
			for(int k = 0; k < diameter / 2; k++) center = par[center];
			return {{center, center}, diameter};
		}else {
			int center1 = 0;
			for(int i = 0; i < n; i++) if(dist[i] > dist[center1]) center1 = i;
			for(int k = 0; k < diameter / 2; k++) center1 = par[center1];
			dfs(center1, dist, par);
			int center2 = 0;
			for(int i = 0; i < n; i++) if(dist[i] > dist[center2]) center2 = i;
			for(int k = 0; k < diameter / 2; k++) center2 = par[center2];
			return {{center1, center2}, diameter};
		}
	}
};

vector<vector<int>> adj;
int dfs2(int at, int d, int target, int node, int p = -1) {
	if(at == node) return 0;
	if(d == target) return 1;
	int sm = 0;
	for(int nxt : adj[at]) {
		if(nxt != p) {
			sm += dfs2(nxt, d + 1, target, node, at);
		}
	}
	return sm;
}
const int M = 998244353;

void _test() {
	int n; re(n);
	adj = vector<vector<int>>(n);
	for(int i = 0; i < n - 1; i++) {
		int a, b; re(a, b); a--, b--;
		adj[a].pb(b); adj[b].pb(a);
	}
	tree_center tc(adj);
	auto center = tc.get_tree_center();
	int node;
	if(center.fs.fs != center.fs.sc) {
		int node1 = center.fs.fs, node2 = center.fs.sc;
		adj.pb({node1, node2});
		node = n;
		for(int i = 0; i < adj[node1].size(); i++) {
			if(adj[node1][i] == node2) {
				adj[node1].erase(adj[node1].begin() + i);
				break;
			}
		}for(int i = 0; i < adj[node2].size(); i++) {
			if(adj[node2][i] == node1) {
				adj[node2].erase(adj[node2].begin() + i);
				break;
			}
		}
	}else {
		node = center.fs.fs;
	}
	
	int target = (center.sc + 1) / 2;
	vector<int> lens;
	int ans = 1;
	int sm = 0;
	for(int nxt : adj[node]) {
		int res = dfs2(nxt, 1, target, node);
		ans = (ans * (res + 1)) % M;
		sm += res;
	}
	prl((ans - sm - 1 + M) % M);
}
