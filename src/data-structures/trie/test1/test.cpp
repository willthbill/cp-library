// https://www.hackerearth.com/practice/data-structures/advanced-data-structures/trie-keyword-tree/practice-problems/algorithm/tries-78733022/
#include<bits/stdc++.h>
using namespace std;
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
int main(){
	int n; cin >> n;
	Trie<char, string> trie;
	trie = Trie<char,string>(200);
	for(int i = 0; i < n; i++){
		string t, s; cin >> t >> s;
		if(t == "add"){
			trie.insert(s);
		}else {
			cout << trie.countPaths(s) << endl;
		}
	}
}
