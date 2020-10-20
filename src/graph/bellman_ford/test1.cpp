#include <bits/stdc++.h>
using namespace std;
#define print(x) cout << x << endl
#define debug(x) cerr << #x << " : " << x << endl

vector<int> bellman_ford(vector<pair<int, int>>* adj, int n, int m, int src) {

    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < adj[j].size(); k++) {
                int u = j, v = adj[j][k].first, w = adj[j][k].second;
                if (dist[u] != INT_MAX && dist[u]+w < dist[v])
                    dist[v] = dist[u]+w;
            }
        }
    }

    // BELLMAN FORD ONLY CHECKS IF A NEGATIVE WEIGHT CYCLE EXISTS, NOT WHERE
    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < adj[i].size(); j++) {
            int u = i, v = adj[i][j].first, w = adj[i][j].second;
            if (dist[u] != INT_MAX && dist[u]+w < dist[v])
                // NEGATIVE WEIGHT CYCLE DETECTED
        }
    }
    */

    return dist;
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

        vector<pair<int, int>> adj[n];
        vector<vector<int>> dist(n);
        
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back(make_pair(v, w));
        }
        
        for (int i = 0; i < n; i++)
            dist[i] = bellman_ford(adj, n, m, i);

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