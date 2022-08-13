#include <bits/stdc++.h>
using namespace std;
#define printl(x, y) for (auto z = x.begin(); z != x.end(); z++) cout << *z << (z == x.end()-1 ? "\n" : y)
#define nextpow2(x) __builtin_popcount(x) == 1 ? x : (1 << (32-__builtin_clz(x)))
#define licorice ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define read(x, y) for (int z = 0; z < y; z++) cin >> x[z]
#define mkunique(x) x.resize(unique(all(x))-x.begin())
#define debug(x) cerr << #x << " : " << x << endl
#define print(x) cout << x << endl
#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()
#define first(x) get<0>(x)
#define second(x) get<1>(x)
#define third(x) get<2>(x)
#define i64 int64_t
#define oo INT64_MAX

/*
    https://cses.fi/problemset/task/1694/
    note that the class might have been changed slightly
    the class in main.cpp is up to date for all problems
*/
class MaxFlow {
public:
    int n;
    int src;
    int sink;
    vector<int> color;
    vector<map<i64, i64>> adj;
    vector<map<i64, i64>> adj_t;
    vector<int> left;
    MaxFlow() {}
    void init(int n, int src, int sink) {
        this->n = n;
        this->src = src;
        this->sink = sink;
        color.resize(n);
        adj.resize(n);
        adj_t.resize(n);
        left.resize(n);
    }
    void add_edge(int u, int v, i64 w=1) {
        adj[u][v] += w;
        adj_t[v][u] = 0;
        if (u == src) {
            left[v] = 1;
        }
    }
    pair<bool, i64> max_flow(i64 node, i64 mn, i64 threshold) {
        if (node == sink) {
            return {true, mn};
        }
        for (auto [nei, weight] : adj[node]) {
            if (color[nei] || weight < threshold) {
                continue;
            }
            color[nei] = 1;
            auto [done, flow] = max_flow(nei, min(mn, weight), threshold);
            if (done) {
                adj[node][nei] -= flow;
                adj_t[nei][node] += flow;
                return {done, flow};
            }
        }
        for (auto [nei, weight] : adj_t[node]) {
            if (color[nei] || weight < threshold) {
                continue;
            }
            color[nei] = 1;
            auto [done, flow] = max_flow(nei, min(mn, weight), threshold);
            if (done) {
                adj_t[node][nei] -= flow;
                adj[nei][node] += flow;
                return {done, flow};
            }
        }
        return {false, 0};
    }
    void compute_max_flow() {
        fill(all(color), 0);
        i64 threshold = oo;
        while (threshold) {
            threshold = oo;
            color[src] = 1;
            while (threshold && !max_flow(src, oo, threshold).first) {
                fill(all(color), 0);
                color[src] = 1;
                threshold /= 2;
            }
        }
    }
    i64 get_max_flow() {
        /* call compute_max_flow */
        i64 flow = 0;
        for (auto [nei, weight] : adj_t[sink]) {
            flow += weight;
        }
        return flow;
    }
    void dfs(int node) {
        for (auto [nei, weight] : adj[node]) {
            if (color[nei] || weight == 0) {
                continue;
            }
            color[nei] = 1;
            dfs(nei);
        }
    }
    void min_cut(int node, vector<pair<int, int>>& cut) {
        for (auto [nei, weight] : adj[node]) {
            if (color[nei] == 0) {
                cut.push_back({node, nei});
                continue;
            }
            if (color[nei] == 2) {
                continue;
            }
            color[nei] = 2;
            min_cut(nei, cut);
        }
    }
    vector<pair<int, int>> get_min_cut() {
        /* call compute_max_flow */
        fill(all(color), 0);
        color[src] = 1;
        dfs(src);
        color[src] = 2;
        vector<pair<int, int>> cut;
        min_cut(src, cut);
        return cut;
    }
    vector<pair<int, int>> get_max_matching() {
        /* call compute_max_flow */
        vector<pair<int, int>> matching;
        for (int node = 0; node < n; node++) {
            if (left[node] == 0) {
                continue;
            }
            for (auto [nei, weight] : adj[node]) {
                if (weight == 0) {
                    matching.push_back({node, nei});
                }
            }
        }
        return matching;
    }
    bool find_path(int node, vector<int>& path) {
        if (node == sink) {
            return true;
        }
        for (auto [nei, weight] : adj[node]) {
            if (weight == 0) {
                path.push_back(nei+1);
                adj[node].erase(nei);
                return find_path(nei, path);
            }
        }
        return false;
    }
    vector<vector<int>> edge_disjoint_paths() {
        /* call compute_max_flow */
        vector<vector<int>> paths;
        bool found = true;
        while (found) {
            vector<int> path;
            path.push_back(src+1);
            found = find_path(src, path);
            if (found) {
                paths.push_back(path);
            }
        }
        return paths;
    }
    void alternate_path(int node, vector<int>& node_cover) {
        for (auto [nei, weight] : adj[node]) {
            if (color[nei]) {
                continue;
            }
            color[nei] = 1;
            node_cover[nei] = !node_cover[node];
            alternate_path(nei, node_cover);
        }
    }
    vector<int> get_node_cover() {
        /* call compute_max_flow */
        vector<int> unmatched(n, 1);
        vector<pair<int, int>> matching = get_max_matching();
        for (auto [u, v] : matching) {
            unmatched[u] = unmatched[v] = 0;
        }
        vector<int> node_cover(n);
        fill(all(color), 0);
        color[src] = color[sink] = 1;
        for (int node = 0; node < n; node++) {
            if (unmatched[node]) {
                if (color[node]) {
                    continue;
                }
                color[node] = 1;
                alternate_path(node, node_cover);
            }
        }
        alternate_path(src, node_cover);
        return node_cover;
    }
    vector<int> get_independent_set() {
        /* call compute_max_flow */
        vector<int> node_cover = get_node_cover();
        for (int node = 0; node < n; node++) {
            if (node == src || node == sink || node_cover[node]) {
                node_cover[node] = 0;
            } else {
                node_cover[node] = 1;
            }
        }
        return node_cover;
    }
};

int main() {
    
    /* 甘草 */
    licorice

    i64 n, m; cin >> n >> m;
    MaxFlow maxflow;
    maxflow.init(n, 0, n-1);
    for (int i = 0; i < m; i++) {
        i64 u, v, w; cin >> u >> v >> w; u--, v--;
        maxflow.add_edge(u, v, w);
    }
    maxflow.compute_max_flow();
    print(maxflow.get_max_flow());

    return 0;
}

/*
    stuck?
    - binary search
    - prefix
    - hidden graph
    - compact dp
    - hidden observations
    - stack dp
    - reverse
    - reroot
    - rewrite the math
    - index vs value
    - fix variable
*/

/*
g++ -std=c++17 main.cpp -o a.exe

a.exe < input.txt
*/