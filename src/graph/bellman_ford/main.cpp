vector<int> bellman_ford(vector<vector<pair<int, int>>>& adj, int n, int m, int src) {

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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < adj[i].size(); j++) {
            int u = i, v = adj[i][j].first, w = adj[i][j].second;
            if (dist[u] != INT_MAX && dist[u]+w < dist[v])
                // NEGATIVE WEIGHT CYCLE DETECTED
        }
    }

    return dist;
}
