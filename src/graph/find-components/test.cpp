// https://cses.fi/problemset/task/1666
#include<bits/stdc++.h>
using namespace std;
pair<vector<int>, vector<vector<int>>> get_components(vector<vector<int>>& adj){
	int n = (int)adj.size();
	vector<int> component_map (n, -1);
	vector<vector<int>> component_groups;
	for(int i = 0; i < n; i++){
		if(component_map[i] == -1){
			queue<int> q;
			q.push(i);
			component_groups.push_back({});
			int idx = (int)component_groups.size() - 1;
			while(!q.empty()){
				int curr = q.front(); q.pop();
				if(component_map[curr] != -1) continue;
				component_groups[idx].push_back(curr);
				component_map[curr] = idx;
				for(auto& e : adj[curr]){
					if(component_map[e] == -1) q.push(e);
				}
			}
		}
	}
	// component_map[node] is the component of the node
	// node is in component_groups[component_map[node]]
	return {component_map, component_groups};
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m; cin >> n >> m;
	vector<vector<int>> adj (n);
	for(int i = 0; i < m; i++){
		int a, b; cin >> a >> b; a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	auto components = get_components(adj);
	cout << (int)components.second.size() - 1 << endl;
	for(int i = 1; i < (int) components.second.size(); i++){
		int a = components.second[i][0];
		int b = components.second[i-1][0];
		cout << a + 1 << " " << b + 1 << endl;
	}
}
