// https://codeforces.com/contest/1428/problem/F
#include<bits/stdc++.h>
using namespace std;

// Username: WillTheBill
#define _multitest_ 0
#define _multitestexpr_ re(tests)
#define _interactive_ 0
#define int long long

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
#if (!defined __local__) || defined _interactive_
#define _stdout cout
#else
#define _stdout _effout
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

// BEGIN code block of: data-structures/sparse-table-constant
// Standard message: The following is code from https://github.com/williamMBDK/cp-library but was copied from a local copy of the repository. Changes to the original source may have been done here.
// this is for getting for example min range queries in O(1)
// with O(n log n) precomputation
template<class T, T(*F)(T,T)>
struct SPS { // requires F(x, F(x, x)) = F(F(x, x), x) = x
    vector<vector<T>> M;
    vector<int> hik;
    int n;
    int logn;
    SPS(){}
    SPS(vector<T>& A) {
        n = A.size();
        logn = 0;
        while(1<<logn <= n) logn++;
        hik = vector<int> (n + 1);
        for(int i = 2; i <= n; i++) hik[i] = hik[i/2] + 1;
        M = vector<vector<T>>(logn,vector<T>(n));
        for(int i = 0; i < n; i++) M[0][i] = A[i];
        for(int k = 1; k < logn; k++) for(int i = 0; i < n; i++) {
            int nxt = min(n - 1, i + (1 << (k - 1)));
            M[k][i] = F(M[k - 1][i], M[k - 1][nxt]);
        }
    }
    T q(int l, int r) {
        assert(l <= r);
        int k = hik[r - l + 1];
        return F(M[k][l], M[k][r - (1 << k) + 1]);
    }
};
// END code block of: data-structures/sparse-table-constant
int mx(int a, int b) { return max(a,b); }
void testcase(__attribute__((unused)) signed tc){
    int n; re(n);
    string s; re(s);
    vec<int> left (n), right (n);
    left[n-1] = s[n-1] == '1';
    right[0] = s[0] == '1';
    foab(i, 1, n) if(s[i] == '1') right[i] = right[i-1] + 1;
    for(int i = n - 2; i >= 0; i--) if(s[i] == '1') left[i] = left[i+1] + 1;
    debug(left, right);
    SPS<int,mx> rightsps (right), leftsps (left);
    int idx = 0;
    vec<pair<int,int>> intervals;
    while(idx < n) {
        int start = idx;
        while(idx < n && s[idx] == '1') idx++;
        int end = idx - 1;
        idx++;
        if(start > end) continue;
        intervals.pb({start, end});
    }
    debug(intervals);
    int res = 0;
    foe(iv, intervals) {
        int len = iv.se - iv.fi + 1;
        foab(i, 1, len + 1) {
            res += (len - i + 1) * i;
        }
    }
    fun(int, leftsearch, int idx, int val) {
        int len = 0;
        for(int i = 1 << 20; i > 0; i >>= 1) {
            int curr = len + i;
            int l = idx - curr, r = idx - 1;
            if(0 <= l && l <= r && leftsps.q(l,r) <= val) {
                len = curr;
            }
        }
        return len;
    };
    fun(int, rightsearch, int idx, int val) {
        int len = 0;
        for(int i = 1 << 20; i > 0; i >>= 1) {
            int curr = len + i;
            int l = idx + 1, r = idx + curr;
            if(l <= r && r < n && rightsps.q(l,r) <= val) {
                len = curr;
            }
        }
        return len;
    };
    foe(iv, intervals) {
        int len = iv.se - iv.fi + 1;
        int cleft = leftsearch(iv.fi, len - 1) + 1;
        int cright = rightsearch(iv.se, len) + 1;
        debug(cleft, cright);
        res += (cleft * cright) * len - len;
    }
    foe(iv, intervals) {
        foab(i, iv.fi, iv.se) {
            int len = i - iv.fi + 1;
            int cleft = leftsearch(iv.fi, len - 1);
            res += cleft * len;
        }
    }
    foe(iv, intervals) {
        foab(i, iv.fi, iv.se) {
            int len = i - iv.fi + 1;
            int cright = rightsearch(iv.se, len);
            res += cright * len;
        }
    }
    debug(res);
    prl(res);
}
