// Username: WillTheBill
// Time of creation: %FDATE%
// Original filename: %FFILE%

#include<bits/stdc++.h>
using namespace std;

// shortcuts
#define pb push_back
#define fi first
#define se second
typedef long long ll;

// IO
#define multitest signed __T; cin >> __T; while(__T--)
void _masterread(){}
template<typename T,typename... V>
void _masterread(T& t, V&... v){cin >> t;_masterread(v...);}
#define read(...)_masterread(__VA_ARGS__)
void _masterprint(){cout << endl;}
template<typename T,typename... V>
void _masterprint(T t, V... v){cout << t;if(sizeof...(v)) cout << " ";_masterprint(v...);}
#define print(...)_masterprint(__VA_ARGS__)

// DEBUG
// colored output???
template <typename T> // start forward declaration
void _print(T t);
template<typename T1,typename T2>
void _print(pair<T1,T2> p);
template<typename T>
void _print(vector<T>v);
template <typename T> // end forward declaration
void _print(T t){cerr<<t;}
template<typename T1,typename T2>
void _print(pair<T1,T2> p){cerr<<"{";_print(p.first);cerr<<", ";_print(p.second);cerr<<"}";}
template<typename T>
void _print(vector<T>v){cerr<<"(";for(unsigned _i=0;_i<v.size();_i++)_print(v[_i]),cerr<<(_i==v.size()-1?"":", ");cerr << ")";}
void _masterdebug(){cerr<<"]\n";}
template<typename T,typename... V>
void _masterdebug(T t,V... v){_print(t);if(sizeof...(v))cerr<<", ";_masterdebug(v...);}
#ifdef __local__
#define debug(...) cerr<<"["<<#__VA_ARGS__<<"] = [";_masterdebug(__VA_ARGS__)
#else
#define debug(...) 
#endif

// ordered_set and ordered_map
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T1, typename T2>
using ordered_map = tree<T1, T2, less<T1>, rb_tree_tag, tree_order_statistics_node_update>;

// TYPES
// #define int ll

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    %HERE%
}
