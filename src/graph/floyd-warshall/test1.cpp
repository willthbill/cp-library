// https://open.kattis.com/problems/allpairspath
#include <bits/stdc++.h>
using namespace std;
#define print(x) cout << x << endl
#define debug(x) cerr << #x << " : " << x << endl

template<class Int>
vector<vector<Int>> floyd_warshall(vector<vector<pair<int, Int>>>& adj, Int MX){
	int n = (int)adj.size();
	vector<vector<Int>> graph(n, vector<Int>(n, MX));
	// INITIALIZE GRAPH WITH DIST 0 FROM NODE TO ITSELF
	for(int i = 0; i < n; i++) graph[i][i] = 0;
	// INPUT ALL EDGES AND UPDATE THE MIN WEIGHT
	for(int i = 0; i < n; i++){
		for(auto& edge : adj[i]){
			if(graph[i][edge.first] > edge.second){
				graph[i][edge.first] = edge.second;
			}
		}
	}
	// FLOYD WARSHALL
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (graph[i][k] != MX && graph[k][j] != MX && graph[i][j] > graph[i][k] + graph[k][j]){
					graph[i][j] = graph[i][k]+graph[k][j];
				}
			}
		}
	}
	// FLOYD WARSHALL APPROACH FOR CHECKING NEGATIVE WEIGHT CYCLE BETWEEN TWO NODES
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (graph[k][k] < 0 && graph[i][k] != MX && graph[k][j] != MX){
					graph[i][j] = -MX;
				}
			}
		}
	}
	return graph;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bool f = true;

    while(true) {
        int n, m, q;
        cin >> n >> m >> q;
        if (!n) break;

        if (!f) cout << endl;
        else f = false;

		vector<vector<pair<int,int>>> adj (n);
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
			adj[u].push_back({v, w});
        }

		auto graph = floyd_warshall(adj, INT_MAX);
        
        for (int i = 0; i < q; i++) {
            int u, v;
            cin >> u >> v;

            if (graph[u][v] == -INT_MAX)
                cout << "-Infinity" << endl;
            else if (graph[u][v] == INT_MAX)
                cout << "Impossible" << endl;
            else
                cout << graph[u][v] << endl;
        }
    }

    return 0;
}
