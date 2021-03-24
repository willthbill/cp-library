#include<bits/stdc++.h>
using namespace std;
pair<vector<int>, vector<vector<int>>> getSCC(vector<vector<int>>& adj){
	int n = (int) adj.size();
	vector<vector<int>> tadj (n);
	for(int i = 0; i < n; i++){
		for(auto& e : adj[i]) tadj[e].push_back(i);
	}
	stack<int> s;
	vector<bool> v (n);
	function<void(int)> dfs1;
	dfs1 = [&](int node){
		if(v[node]) return;
		v[node] = true;
		for(auto& nb : adj[node]) dfs1(nb);
		s.push(node);
	};
	for(int i = 0; i < n; i++) dfs1(i);
	vector<int> mp (n, -1);
	function<void(int,int)> dfs2;
	dfs2 = [&](int node, int component){
		if(mp[node] != -1) return;
		mp[node] = component;
		for(auto& nb : tadj[node]) dfs2(nb, component);
	};
	int component = 0;
	while(!s.empty()){
		int node = s.top(); s.pop();
		if(mp[node] == -1) dfs2(node, component++);
	}
	vector<vector<int>> components (component);
	for(int i = 0; i < n; i++) components[mp[i]].push_back(i);
	return {mp, components};
}
int main(){
	int n,m; cin >> n >> m;
	vector<vector<int>> adj (n);
	for(int i = 0; i < m; i++){
		int a,b; cin >> a >> b; a--; b--;
		adj[a].push_back(b);
	}
	auto sccs = getSCC(adj);
	cout << sccs.second.size() << endl;
	for(int i = 0; i < n; i++){
		cout << sccs.first[i] + 1 << " ";
	}
	cout << endl;
}
