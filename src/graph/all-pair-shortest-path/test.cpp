// https://cses.fi/problemset/task/1672
#include<bits/stdc++.h>
using namespace std;
template<class Int=long long>
struct Dijkstra{
    // could add support for number of shortest paths and so on...
    // 0-indexed nodes
    int N;
    vector<vector<pair<int, Int>>> adj;
    vector<Int> dist; // distance to node, -1 if not visited
    vector<int> prev; // previous node, -2 if no previous node, -1 if not visited
    Dijkstra(){}
    Dijkstra(vector<vector<pair<int, Int>>>& _adj){
        adj = _adj;
        N = (int)adj.size();
    }
    struct Qitem{
        Int dist;
        int node, prev;
    };
    struct Comparator{
        bool operator()(Qitem& i1, Qitem& i2){
            return i1.dist > i2.dist;
        }
    };
    vector<Int>& run(int start){ // returned as reference
        priority_queue<Qitem, vector<Qitem>, Comparator> q;
        q.push({0, start, -2});
        dist = vector<Int> (N, -1);
        prev = vector<int> (N, -1);
        while(!q.empty()){
            Qitem curr = q.top(); q.pop();
            if(dist[curr.node] != -1) continue;
            dist[curr.node] = curr.dist;
            prev[curr.node] = curr.prev;
            for(auto& edge : adj[curr.node]){
                if(dist[edge.first] == -1){
                    q.push({curr.dist + edge.second, edge.first, curr.node});
                }
            }
        }
        return dist;
    }
};
template<class Int=long long>
vector<vector<Int>> APSP(vector<vector<pair<int, Int>>>& adj){
	int N = (int)adj.size();
	vector<vector<Int>> res (N);
	Dijkstra<Int> ds (adj);
	for(int i = 0; i < N; i++){
		res[i] = ds.run(i);
	}
	return res;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n,m,q; cin >> n >> m >> q;
	vector<vector<pair<int, long long>>> adj (n);
	for(int i = 0; i < m; i++){
		int a, b, c; cin >> a >> b >> c; a--, b--;
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
	}
	auto apsp = APSP(adj);
	for(int i = 0; i < q; i++){
		int a, b; cin >> a >> b; a--, b--;
		assert(apsp[a][b] == apsp[b][a]);
		cout << apsp[a][b] << endl;
	}
}
