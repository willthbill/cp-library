// https://open.kattis.com/problems/convexhull
// Username: WillTheBill
#include<bits/stdc++.h>
using namespace std;
// shortcuts
#define pb push_back
#define fi first
#define se second
#define all(_v) _v.begin(),_v.end()
#define ll long long
#define fun(ret,x,...) function<ret(__VA_ARGS__)> x;x=[&](__VA_ARGS__)->ret
#define Void(x,...) fun(void,x,__VA_ARGS__)
// reading
#define multitest signed __T; cin >> __T; while(__T--)
template<typename T>void _read(T& t);
template<typename T>void _read(vector<T>&v);
template<typename T1, typename T2>void _read(pair<T1,T2>&p);
template<typename T>void _read(T& t){cin >> t;}
template<typename T>void _read(vector<T>&v){for(unsigned _i=0;_i<v.size();_i++)_read(v[_i]);}
template<typename T1, typename T2>void _read(pair<T1,T2>&p){_read(p.first);_read(p.second);}
void _masterread(){}
template<typename T,typename... V>void _masterread(T& t, V&... v){_read(t);_masterread(v...);}
#define re(...)_masterread(__VA_ARGS__)
// writing
stringstream _effout;
#ifdef __local__
#define _stout cout
#else
#define _stout _effout
#endif
template<typename T>void _print(T t);
template<typename T>void _print(vector<T>&v);
template<typename T1, typename T2>void _print(pair<T1,T2>&p);
template<typename T>void _print(T t){_stout<<t;}
template<typename T>void _print(vector<T>&v){for(unsigned _i=0;_i<v.size();_i++)_print(v[_i]),_stout<<(_i==v.size()-1?"":" ");}
template<typename T1, typename T2>void _print(pair<T1,T2>&p){_print(p.first);_stout<<" ";_print(p.second);}
void _masterprint(){}
template<typename T,typename... V>void _masterprint(T t, V... v){_print(t);if(sizeof...(v))_stout<<" ";_masterprint(v...);}
#define pr(...)_masterprint(__VA_ARGS__)
#define prl(...) (_masterprint(__VA_ARGS__),_stout<<endl)
// debugging, instead of a similar implementation for each container type a seperate generic function could be used
template <typename T> void _debug(T t); //forward declaration
template<typename T1,typename T2> void _debug(pair<T1,T2> p);
template<typename T> void _debug(vector<T> v);
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
template<typename T> void _debug(vector<T>v){cerr<<"(";for(unsigned _i=0;_i<v.size();_i++)_debug(v[_i]),cerr<<(_i==v.size()-1?"":", ");cerr << ")";}
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
void _solve();
void _test();
signed main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  pr(setprecision(10));
  pr(fixed);
  _solve();
  #ifndef __local__
  cout<<_effout.str();
  #endif
}
// #define int long long
#define _mt_ 0
void _solve(){
  if(_mt_) {
    multitest _test();
  } else {
    _test();
  }
}
// BEGIN code block of: geometry/convex-hull
// Standard message: The following is code from https://github.com/williamMBDK/cp-library but was copied from a local copy of the repository. Changes to the original source may have been done here.
template<class T>
class ConvexHull {
    class ConvexHullUtill {
        pair<T, T> p0;
    public:
        ConvexHullUtill(pair<T, T> _p0) {
            p0 = _p0;
        }
        int distPow2(pair<T, T> p1, pair<T, T> p2) {
            return (p1.first-p2.first)*(p1.first-p2.first)+(p1.second-p2.second)*(p1.second-p2.second);
        }
        int orientation(pair<T, T> p, pair<T, T> q, pair<T, T> r) {
            int val = (q.second-p.second)*(r.first-q.first)-(q.first-p.first)*(r.second-q.second);
            if (val == 0)
                return 0;
            return (val > 0) ? 1 : 2;
        }
        bool operator()(const pair<T, T>& p1, const pair<T, T>& p2) {
            int o = orientation(p0, p1, p2);
            if (o == 0)
                return (distPow2(p0, p2) > distPow2(p0, p1)) ? true : false;
            return (o == 2) ? true : false;
        }
    };
    static pair<T, T> below_top(stack<pair<T, T>>& S) {
        pair<T, T> p = S.top();
        S.pop();
        pair<T, T> res = S.top();
        S.push(p);
        return res;
    }
public:
    static void convex_hull(stack<pair<T,T>>& S, vector<pair<T,T>> points) {
        int n = (int)points.size();
        if(n == 0) return;
        set<pair<int,int>> _s;
        for(int i = 0; i < n; i++) _s.insert(points[i]);
        points.resize(_s.size());
        int idx = 0;
        for(auto& e : _s) {
          points[idx++] = e;
        }
        n = (int)points.size();
        int ymn = points[0].second, mn = 0;
        for (int i = 1; i < n; i++) {
            T y = points[i].second;
            if ((y < ymn) || (ymn == y && points[i].first < points[mn].first))
                ymn = points[i].second, mn = i;
        }
        swap(points[0], points[mn]);
        pair<T, T> p0 = points[0];
        ConvexHullUtill util(p0);
        sort(points.begin()+1, points.end(), util);
        int m = 1;
        for (int i = 1; i < n; i++) {
            while (i < n-1 && util.orientation(p0, points[i], points[i+1]) == 0)
                i++;
            points[m] = points[i];
            m++;
        }
        if (m < 3) {
            for(int i = 0; i < m; i++) S.push(points[i]);
            return;
        }
        S.push(points[0]);
        S.push(points[1]);
        S.push(points[2]);
        for (int i = 3; i < m; i++) {
            while (util.orientation(below_top(S), S.top(), points[i]) != 2)
                S.pop();
            S.push(points[i]);
        }
    }
    static vector<pair<T,T>> convex_hull(vector<pair<T, T>>& points) {
        stack<pair<T,T>> s;
        convex_hull(s, points);
        vector<pair<T,T>> res (s.size());
        int idx = (int)s.size();
        while(!s.empty()){
          res[--idx] = s.top();
          s.pop();
        }
        return res;
    }
};

// END code block of: geometry/convex-hull
void _test(){
  int n; re(n);
  while(n != 0) {
    vector<pair<int,int>> points (n); re(points);
    auto res = ConvexHull<int>::convex_hull(points);
    prl(res.size());
    for(auto& e : res) {
      prl(e);
    }
    re(n);
  }
}
