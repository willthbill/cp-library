// Username: WillTheBill
// Time of creation: 2020-10-25 04:03
// Original filename: test.cp.cpp

#include<bits/stdc++.h>
using namespace std;

// shortcuts
#define pb push_back
#define fi first
#define se second
#define all(_v) _v.begin(),_v.end()
#define ll long long

// IO
#define multitest signed __T; cin >> __T; while(__T--)
template<typename T>
void _read(T& t);
template<typename T>
void _read(vector<T>&v);
template<typename T1, typename T2>
void _read(pair<T1,T2>&p);
template<typename T>
void _read(T& t){cin >> t;}
template<typename T>
void _read(vector<T>&v){for(unsigned _i=0;_i<v.size();_i++)_read(v[_i]);}
template<typename T1, typename T2>
void _read(pair<T1,T2>&p){_read(p.first);_read(p.second);}
void _masterread(){}
template<typename T,typename... V>
void _masterread(T& t, V&... v){_read(t);_masterread(v...);}
#define re(...)_masterread(__VA_ARGS__)

template<typename T>
void _print(T t);
template<typename T>
void _print(vector<T>&v);
template<typename T1, typename T2>
void _print(pair<T1,T2>&p);
template<typename T>
void _print(T t){cout<<t;}
template<typename T>
void _print(vector<T>&v){for(unsigned _i=0;_i<v.size();_i++)_print(v[_i]),cout<<(_i==v.size()-1?"":" ");}
template<typename T1, typename T2>
void _print(pair<T1,T2>&p){_print(p.first);cout<<" ";_print(p.second);}
void _masterprint(){cout<<endl;}
template<typename T,typename... V>
void _masterprint(T t, V... v){_print(t);if(sizeof...(v))cout<<" ";_masterprint(v...);}
#define pr(...)_masterprint(__VA_ARGS__)

// DEBUG
// colored output???
template <typename T> // start forward declaration
void _debug(T t);
template<typename T1,typename T2>
void _debug(pair<T1,T2> p);
template<typename T>
void _debug(vector<T>v);
template <typename T> // end forward declaration
void _debug(T t){cerr<<t;}
template<typename T1,typename T2>
void _debug(pair<T1,T2> p){cerr<<"{";_debug(p.first);cerr<<", ";_debug(p.second);cerr<<"}";}
template<typename T>
void _debug(vector<T>v){cerr<<"(";for(unsigned _i=0;_i<v.size();_i++)_debug(v[_i]),cerr<<(_i==v.size()-1?"":", ");cerr << ")";}
void _masterdebug(){cerr<<"]\n";}
template<typename T,typename... V>
void _masterdebug(T t,V... v){_debug(t);if(sizeof...(v))cerr<<", ";_masterdebug(v...);}
#ifdef __local__
#define debug(...) cerr<<"["<<#__VA_ARGS__<<"] = [";_masterdebug(__VA_ARGS__)
#else
#define debug(...) 
#endif

// TYPES
// #define int long long

template<class T, class Container>
struct Trie{
	// logarithmic queries since map is used. You may change to unordered_map is you dare.
	// might use a lot of memory if removing and inserting a lot. Memory is not freed when removing.
	int MAX_NODES;
	static const int root = 0;
	int next_idx = 1; // next free spot for a new node
	vector<map<T,int>> adj;
	vector<int> paths; // number of paths going 'over' a given node
	vector<int> words; // number of words ending at a given node
	void init(){ // tested in test1
		adj = vector<map<T, int>> (MAX_NODES);
		paths = vector<int> (MAX_NODES);
		words = vector<int> (MAX_NODES);
	}
	Trie(){ // tested in test1
		MAX_NODES = 1;
		init();
	}
	Trie(int MN){ // tested in test1
		MAX_NODES = max(1, MN);
		init();
	}
	Trie(vector<Container>& initialContent){ // tested in test2
		MAX_NODES = 1;
		for(auto& con : initialContent) MAX_NODES += (int)con.size(); // works for strings too.
		init();
		for(auto& con : initialContent) insert(con);
	}
	int size(){ //tested in test2
		return paths[root];
	}
	void insert(Container& elements){ // tested in test1
		int node = root;
		paths[node]++;
		for(auto& e : elements){
			if(!adj[node].count(e)){
				if(next_idx == MAX_NODES){
					MAX_NODES++;
					adj.push_back({});
					paths.push_back(0);
					words.push_back(0);
				}
				adj[node][e] = next_idx;
				node = next_idx;
				next_idx++;
			}else{
				node = adj[node][e];
			}
			paths[node]++;
		}
		words[node]++;
	}
	int countPaths(Container& elements){ // tested in test1
		int t = getnode(elements);
		return t == -1 ? 0 : paths[t];
	}
	int count(Container& elements){ // tested in test2
		int t = getnode(elements);
		return t == -1 ? 0 : words[t];
	}
	int getnode(Container& elements){ // tested in test1
		int node = root;
		for(auto& e : elements){
			if(!adj[node].count(e)) return -1;
			node = adj[node][e];
		}
		return node;
	}
	// if all=true, then all occurrences of elements is removed
	// assumes elements is in the trie
	int remove(Container& elements, bool all = false, int node = root, int idx = 0){ // tested in test2
		if(idx == (int)elements.size()){
			int t = (all ? words[node] : 1);
			paths[node] -= t;
			words[node] -= t;
			return t;
		}else{
			int t = remove(elements, all, adj[node][elements[idx]], idx + 1);
			paths[node] -= t;
			return t;
		}
	}
};

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, q; re(n,q);
	vector<vector<int>> initial (n);
	for(int i = 0; i < n; i++){
		int s; re(s);
		vector<int> a (s); re(a);
		initial[i] = a;
	}
	Trie<int, vector<int>> trie (initial);
	for(int i = 0; i < q; i++){
		char type; re(type);
		int s; re(s);
		vector<int> a (s); re(a);
		if(type == 'a'){
			trie.insert(a);
		}else if(type == 'c'){
			cout << trie.count(a) << endl;
		}else if(type == 's'){
			cout << trie.size() << endl;
		}else if(type == 'r'){
			trie.remove(a);
		}else if(type == 'd'){
			trie.remove(a, true);
		}
	}
}
