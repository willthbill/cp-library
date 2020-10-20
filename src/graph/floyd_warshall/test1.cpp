#include <bits/stdc++.h>
using namespace std;
#define print(x) cout << x << endl
#define debug(x) cerr << #x << " : " << x << endl

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

        // INITIALIZE GRAPH WITH DIST 0 FROM NODE TO ITSELF
        vector<vector<int>> graph(n, vector<int>(n, INT_MAX));
        for (int i = 0; i < n; i++)
            graph[i][i] = 0;

        // INPUT ALL EDGES AND UPDATE THE MIN WEIGHT
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u][v] = min(graph[u][v], w);
        }
        
        // FLOYD WARSHALL
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (graph[i][k] < INT_MAX && graph[k][j] < INT_MAX)
						graph[i][j] = min(graph[i][j], graph[i][k]+graph[k][j]);
                }
            }
        }

        // FLOYD WARSHALL APPROACH FOR CHECKING NEGATIVE WEIGHT CYCLE BETWEEN TWO NODES
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (graph[k][k] < 0 && graph[i][k] != INT_MAX && graph[k][j] != INT_MAX)
                        graph[i][j] = -INT_MAX;
                }
            }
        }
        
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