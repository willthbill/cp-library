// https://open.kattis.com/problems/eastereggs

#include<bits/stdc++.h>
using namespace std;

// Username: WillTheBill
#define _multitest_ 0
#define _multitestexpr_ re(tests)
#define _interactive_ 0
// #define int long long

// defines
#define vec vector
#define pb push_back
#define fi first
#define se second
#define all(_v) _v.begin(),_v.end()
#define ll long long
#define fun(ret,x,...) function<ret(__VA_ARGS__)> x;x=[&](__VA_ARGS__)->ret
#define Void(x,...) fun(void,x,__VA_ARGS__)
#define mp make_pair
// loops
#define foabc(i,a,b,c) for (int i = (a); i < (b); i+=(c))
#define foab(i,a,b) for (int i = (a); i < (b); i++)
#define fon(i,n) for(int i = 0; i < n; i++)
#define foe(e,a) for(auto& e : a)
#define rep(n) for(int _ = 0; _ < n; _++)
// constructing multidimensional vectors
template<typename T> inline void init(vec<T>& v, deque<int> sizes) {
    assert(sizes.size() == 1);
    v = vec<T> (sizes[0]);
}
template<typename T, typename C> inline void init(vec<T>& v, deque<int> sizes, C content) {
    assert(sizes.size() == 1);
    v = vec<T> (sizes[0], content);
}
template<typename T> inline void init(vec<vec<T>>& v, deque<int> sizes) {
    v = vec<vec<T>> (sizes[0]);
    sizes.pop_front();
    if(sizes.size() == 0) return;
    for(auto& subv : v) init(subv, sizes);
}
template<typename T, typename C> inline void init(vec<vec<T>>& v, deque<int> sizes, C content) {
    v = vec<vec<T>> (sizes[0]);
    sizes.pop_front();
    if(sizes.size() == 0) return;
    for(auto& subv : v) init(subv, sizes, content);
}
// reading
template<typename T>void _read(T& t);
template<typename T>void _read(vec<T>&v);
template<typename T1, typename T2>void _read(pair<T1,T2>&p);
template<typename T>void _read(T& t){cin >> t;}
template<typename T>void _read(vec<T>&v){for(unsigned _i=0;_i<v.size();_i++)_read(v[_i]);}
template<typename T1, typename T2>void _read(pair<T1,T2>&p){_read(p.first);_read(p.second);}
void _masterread(){}
template<typename T,typename... V>void _masterread(T& t, V&... v){_read(t);_masterread(v...);}
#define re(...)_masterread(__VA_ARGS__)
// writing
stringstream _effout;
#if defined(__local__) || (_interactive_ == 1)
#define _stdout cout
#else
#define _stdout _effout
#define endl '\n'
#endif
template<typename T>void _print(T t);
template<typename T>void _print(vec<T>&v);
template<typename T1, typename T2>void _print(pair<T1,T2>&p);
template<typename T>void _print(T t){_stdout<<t;}
template<typename T>void _print(vec<T>&v){for(unsigned _i=0;_i<v.size();_i++)_print(v[_i]),_stdout<<(_i==v.size()-1?"":" ");}
template<typename T1, typename T2>void _print(pair<T1,T2>&p){_print(p.first);_stdout<<" ";_print(p.second);}
void _masterprint(){}
template<typename T,typename... V>void _masterprint(T t, V... v){_print(t);if(sizeof...(v))_stdout<<" ";_masterprint(v...);}
#define pr(...)_masterprint(__VA_ARGS__)
#define prl(...) (_masterprint(__VA_ARGS__),_stdout<<endl)
// debugging, instead of a similar implementation for each container type a seperate generic function could be used
template <typename T> void _debug(T t); //forward declaration
template<typename T1,typename T2> void _debug(pair<T1,T2> p);
template<typename T> void _debug(vec<T> v);
template<typename T> void _debug(set<T>s);
template<typename T> void _debug(unordered_set<T>s);
template<typename T> void _debug(multiset<T>s);
template<typename T> void _debug(unordered_multiset<T>s);
template<typename T1,typename T2> void _debug(map<T1,T2>mp);
template<typename T1,typename T2> void _debug(unordered_map<T1,T2>mp);
template<typename T1,typename T2> void _debug(multimap<T1,T2>mp);
template<typename T1,typename T2> void _debug(unordered_multimap<T1,T2>mp); // end forward declaration
template <typename T> void _debug(T t){cerr<<t;}
template<typename T1,typename T2> void _debug(pair<T1,T2> p){cerr<<"{";_debug(p.first);cerr<<", ";_debug(p.second);cerr<<"}";}
template<typename T> void _debug(vec<T>v){cerr<<"(";for(unsigned _i=0;_i<v.size();_i++)_debug(v[_i]),cerr<<(_i==v.size()-1?"":", ");cerr << ")";}
template<typename T> void _debug(set<T>s){cerr<<"(";for(auto e=s.begin();e!=s.end();)_debug(*e),cerr<<((++e)==s.end()?"":", ");cerr << ")";}
template<typename T> void _debug(unordered_set<T>s){cerr<<"(";for(auto e=s.begin();e!=s.end();)_debug(*e),cerr<<((++e)==s.end()?"":", ");cerr << ")";}
template<typename T> void _debug(multiset<T>s){cerr<<"(";for(auto e=s.begin();e!=s.end();)_debug(*e),cerr<<((++e)==s.end()?"":", ");cerr << ")";}
template<typename T> void _debug(unordered_multiset<T>s){cerr<<"(";for(auto e=s.begin();e!=s.end();)_debug(*e),cerr<<((++e)==s.end()?"":", ");cerr << ")";}
template<typename T1,typename T2> void _debug(map<T1,T2>mp){cerr<<"(";for(auto e=mp.begin();e!=mp.end();)_debug(*e),cerr<<((++e)==mp.end()?"":", ");cerr << ")";}
template<typename T1,typename T2> void _debug(unordered_map<T1,T2>mp){cerr<<"(";for(auto e=mp.begin();e!=mp.end();)_debug(*e),cerr<<((++e)==mp.end()?"":", ");cerr << ")";}
template<typename T1,typename T2> void _debug(multimap<T1,T2>mp){cerr<<"(";for(auto e=mp.begin();e!=mp.end();)_debug(*e),cerr<<((++e)==mp.end()?"":", ");cerr << ")";}
template<typename T1,typename T2> void _debug(unordered_multimap<T1,T2>mp){cerr<<"(";for(auto e=mp.begin();e!=mp.end();)_debug(*e),cerr<<((++e)==mp.end()?"":", ");cerr << ")";}
void _masterdebug(){cerr<<"]"<<endl;}
template<typename T,typename... V> void _masterdebug(T t,V... v){_debug(t);if(sizeof...(v))cerr<<", ";_masterdebug(v...);}
#ifdef __local__
#define debug(...)(cerr<<"["<<#__VA_ARGS__<<"] = [",_masterdebug(__VA_ARGS__))
template<typename T> void _debugall(T c, string n){_debug("debugall: ");_debug(n);cerr<<endl;for(auto _e:c){_debug("  ");_debug(_e);cerr<<endl;}} //2d vectors and similar
#define debugall(c)(_debugall(c,#c)) //2d vectors and similar
#else
#define debug(...)
#define debugall(c)
#endif
// main
void prep();
void testcase(signed tc);
signed main(){
    if(!_interactive_) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
    }
    pr(setprecision(10));
    pr(fixed);
    prep();
    if(_multitest_) {
        signed tests; _multitestexpr_;
        for(signed tc = 1; tc <= tests; tc++) {
            testcase(tc);
        }
    } else {
        testcase(1);
    }
#ifndef __local__
    cout<<_effout.str();
#endif
}
void prep(){
}
// BEGIN code block of: graph/maximum-bipartite-matching
// Standard message: The following is code from https://github.com/williamMBDK/cp-library but was copied from a local copy of the repository. Changes to the original source may have been done here.
// https://github.com/williamMBDK/cp-library/blob/main/src/graph/maximum-bipartite-matching/main.cpp
#define NIL 0
#define INF (1<<28)
struct MBP // maximum bipartite matching, 0-INDEXED!
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
        a++,b++;
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
// END code block of: graph/maximum-bipartite-matching
void testcase(__attribute__((unused)) signed tc){
    int n,blue,red; re(n,blue,red);
    vec<pair<double,double>> bs (blue), rs (red); re(bs, rs);
    fun(double, dist, int a, int b) {
        return (
                (bs[a].fi - rs[b].fi) * (bs[a].fi - rs[b].fi) +
                (bs[a].se - rs[b].se) * (bs[a].se - rs[b].se)
        );
    };
    fun(bool, good, double d) {
        d *= d;
        MBP mbp (blue, red);
        for(int i = 0; i < blue; i++) {
            for(int j = 0; j < red; j++) {
                if(dist(i,j) < d) {
                    mbp.add_edge(i,j);
                }
            }
        }
        int res = blue + red - mbp.hopcroft_karp();
        return res >= n;
    };
    double l = 0, r = 1e6;
    while((r - l) > 1e-6) {
        double m = (l + r) / 2;
        if(good(m)) l = m;
        else r = m;
    }
    prl(l);
}
