//https://cses.fi/problemset/task/1193
#include<bits/stdc++.h>
using namespace std;
struct Shortest_path{
    // could add support for number of shortest paths and so on...
    // 0-indexed nodes
    int N;
    vector<vector<int>> adj;
    vector<int> dist; // distance to node, INT_MAX if not visited
    vector<int> prev; // previous node, -2 if no previous node, -1 if not visited
    Shortest_path(){}
    Shortest_path(vector<vector<int>>& _adj){
        adj = _adj;
        N = (int)adj.size();
    }
	struct QItem{
		int dist, node, prev;
	};
    vector<int>& run(int src){ // returned as reference
		dist = vector<int> (N, INT_MAX);
		prev = vector<int> (N, -1);
		queue<QItem> q;
		q.push({0, src, -2});
		while(!q.empty()){
			auto curr = q.front(); q.pop();
			if(prev[curr.node] != -1) continue;
			prev[curr.node] = curr.prev; 
			dist[curr.node] = curr.dist;
			for(auto& e : adj[curr.node]){
				if(prev[e] == -1){
					q.push({curr.dist + 1, e, curr.node});
				}
			}
		}
		return dist;
    }
};
int main(){
	Shortest_path sp;
	int n, m; cin >> n >> m;
	vector<vector<int>> adj (n * m);
	vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
	vector<string> mp (n);
	for(int i = 0; i < n; i++){
		string s; cin >> s;
		mp[i] = s;
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			for(auto dir : dirs){
				int ni = i + dir.first;
				int nj = j + dir.second;
				if(ni >= 0 && nj >= 0 && ni < n && nj < m && mp[ni][nj] != '#'){
					adj[i * m + j].push_back(ni * m + nj);
				}
			}
		}
	}
	sp = Shortest_path(adj);
	int start, end;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(mp[i][j] == 'A')  start = i * m + j;
			if(mp[i][j] == 'B')  end = i * m + j;
		}
	}
	sp.run(start);
	if(sp.dist[end] == INT_MAX){
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	map<pair<int,int>, char> mpdir = {
		{{0, 1},'R'},
		{{0, -1},'L'},
		{{-1, 0},'U'},
		{{1, 0},'D'},
	};
	int node = end;
	stringstream ss;
	while(node != start){
		int prev = sp.prev[node];
		pair<int,int> a = {node / m, node % m};
		pair<int,int> b = {prev / m, prev % m};
		pair<int,int> diff = {a.first - b.first, a.second - b.second};
		ss << mpdir[diff];
		node = prev;
	}
	auto r = ss.str();
	cout << sp.dist[end] << endl;
	reverse(r.begin(), r.end());
	cout << r << endl;
}
