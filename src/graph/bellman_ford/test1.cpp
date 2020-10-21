// https://open.kattis.com/problems/allpairspath
#include <bits/stdc++.h>
using namespace std;
#define print(x) cout << x << endl
#define debug(x) cerr << #x << " : " << x << endl

template<class Int>
vector<Int> bellman_ford(vector<vector<pair<int, Int>>>& adj, Int MX, int src) {
	int n = (int)adj.size();
    vector<Int> dist(n, MX);
    dist[src] = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < (int)adj[j].size(); k++) {
                int u = j, v = adj[j][k].first, w = adj[j][k].second;
                if (dist[u] != MX && dist[u]+w < dist[v])
                    dist[v] = dist[u]+w;
            }
        }
    }
    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int)adj[i].size(); j++) {
            int u = i, v = adj[i][j].first, w = adj[i][j].second;
            if (dist[u] != MX && dist[u]+w < dist[v])
                // NEGATIVE WEIGHT CYCLE DETECTED
        }
    }*/
    return dist;
}
// only check for negative cycles, not where it is

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

        vector<vector<pair<int, int>>> adj (n);
        vector<vector<int>> dist(n);
        
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back(make_pair(v, w));
        }
        
        for (int i = 0; i < n; i++)
            dist[i] = bellman_ford(adj, INT_MAX, i);

        // FLOYD WARSHALL APPROACH FOR CHECKING NEGATIVE WEIGHT CYCLE BETWEEN TWO NODES
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (dist[k][k] < 0 && dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                        dist[i][j] = -INT_MAX;
                }
            }
        }
        
        for (int i = 0; i < q; i++) {
            int u, v;
            cin >> u >> v;

            if (dist[u][v] == -INT_MAX)
                cout << "-Infinity" << endl;
            else if (dist[u][v] == INT_MAX)
                cout << "Impossible" << endl;
            else
                cout << dist[u][v] << endl;
        }
    }

    return 0;
}
