// https://cses.fi/problemset/task/1672
#include<bits/stdc++.h>
using namespace std;

template<class Int=long long>
struct Dijkstra{
    // could add support for number of shortest paths and so on...
    // 0-indexed nodes
    int N;
	Int MX;
    vector<vector<pair<int, Int>>> adj;
    vector<Int> dist; // distance to node, MX if not visited
    vector<int> prev; // previous node, -2 if no previous node, -1 if not visited
    Dijkstra(){}
    Dijkstra(vector<vector<pair<int, Int>>>& _adj, Int _MX){
        adj = _adj;
        N = (int)adj.size();
		MX = _MX;
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
        dist = vector<Int> (N, MX);
        prev = vector<int> (N, -1);
        while(!q.empty()){
            Qitem curr = q.top(); q.pop();
            if(prev[curr.node] != -1) continue;
            dist[curr.node] = curr.dist;
            prev[curr.node] = curr.prev;
            for(auto& edge : adj[curr.node]){
                if(prev[edge.first] == -1){
                    q.push({curr.dist + edge.second, edge.first, curr.node});
                }
            }
        }
        return dist;
    }
};


template<class Int>
vector<vector<Int>> floyd_warshall(vector<vector<pair<int, Int>>>& adj, Int MX){
	int n = (int)adj.size();
	vector<vector<Int>> graph(n, vector<Int>(n, MX));
	// INITIALIZE GRAPH WITH DIST 0 FROM NODE TO ITSELF
	for(int i = 0; i < n; i++) graph[i][i] = 0;
	// INPUT ALL EDGES AND UPDATE THE MIN WEIGHT
	for(int i = 0; i < n; i++){
		for(auto& edge : adj[i]){
			graph[i][edge.first] = min(graph[i][edge.first], edge.second);
		}
	}
	// FLOYD WARSHALL
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (graph[i][k] != MX && graph[k][j] != MX)
					graph[i][j] = min(graph[i][j], graph[i][k]+graph[k][j]);
			}
		}
	}
	// FLOYD WARSHALL APPROACH FOR CHECKING NEGATIVE WEIGHT CYCLE BETWEEN TWO NODES
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (graph[k][k] < 0 && graph[i][k] != MX && graph[k][j] != MX)
					graph[i][j] = -MX;
			}
		}
	}
	return graph;
}



template<class Int=long long>
vector<vector<Int>> APSP(vector<vector<pair<int, Int>>>& adj, Int MX, int M){
	// dijkstra: O((n + m log m) * n), c = 5
	// floyd_warshall: O(n^3), c = 1
	int N = (int)adj.size();
	long long timedijk = ((long long)(((long long)(N + M * 20)) * N)) * 5;
	long long timefloyd = ((long long)(((long long)N) * N)) * N;
	if(timedijk <= timefloyd){
		vector<vector<Int>> res (N);
		Dijkstra<Int> ds (adj, MX);
		for(int i = 0; i < N; i++){
			res[i] = ds.run(i);
		}
		return res;
	}else{
		return floyd_warshall(adj, MX);
	}
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
	auto apsp = APSP(adj, LLONG_MAX, m);
	for(int i = 0; i < q; i++){
		int a, b; cin >> a >> b; a--, b--;
		assert(apsp[a][b] == apsp[b][a]);
		long long dist = apsp[a][b];
		if(dist == LLONG_MAX) dist = -1;
		cout << dist << endl;
	}
}
