#include <bits/stdc++.h>
using namespace std;
#define print(x) cout << x << endl
#define debug(x) cerr << #x << " : " << x << endl

void DFS(vector<int>* adj, vector<bool>& seen, vector<int>& L, int u) {
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (seen[v]) continue;
        seen[v] = true;
        DFS(adj, seen, L, v);
    }
    L.push_back(u);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;

    vector<int> adj[n];
    vector<int> tadj[n];
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        tadj[v].push_back(u);
    }
    
    vector<int> L; {
        vector<bool> seen(n, false);
        for (int i = 0; i < n; i++) {
            if (seen[i]) continue;
            seen[i] = true;
            DFS(adj, seen, L, i);
        }
    }

    vector<int> scc(n, 0); int scc_cnt = 0; {
        vector<bool> seen(n, false);
        for (int i = L.size() - 1; i >= 0; i--) {
            int src = L[i];
            if (seen[src]) continue;
            queue<int> q;
            q.push(src);
            scc_cnt++;
            while (!q.empty()) {
                int curr = q.front();
                q.pop();
                if (seen[curr]) continue;
                scc[curr] = scc_cnt;
                seen[curr] = true;
                for (int i = 0; i < tadj[curr].size(); i++) {
                    q.push(tadj[curr][i]);
                }
            }
        }
    }

    cout << "SCC" << endl;
    for (auto n : scc)
        cout << n << " ";
    cout << endl;

	return 0;
}