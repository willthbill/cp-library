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
    https://csacademy.com/contest/round-23/task/no-prime-sum/
    TLE on 1 out of 22 cases because limit is tight (uses 1096ms limit is 1000ms)
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
    vector<int> X;
    MaxFlow() {}
    void init(int n, int src, int sink) {
        this->n = n;
        this->src = src;
        this->sink = sink;
        color.resize(n);
        adj.resize(n);
        adj_t.resize(n);
        X.resize(n);
    }
    void add_edge(int u, int v, i64 w=1) {
        adj[u][v] += w;
        adj_t[v][u] = 0;
        if (u == src) {
            X[v] = 1;
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
            if (X[node] == 0) {
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
    vector<vector<int>> get_edge_disjoint_paths() {
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
    void alternate_path(int node, vector<int>& Z, set<pair<int, int>>& M, bool match) {
        Z[node] = 1;
        vector<int> edges;
        for (auto [nei, weight] : adj[node]) {
            edges.push_back(nei);
        }
        for (auto [nei, weight] : adj_t[node]) {
            edges.push_back(nei);
        }
        for (auto nei : edges) {
            bool matched = M.count({min(node, nei), max(node, nei)});
            if (color[nei] || nei == src || nei == sink || (match && !matched) || (!match && matched)) {
                continue;
            }
            color[nei] = 1;
            alternate_path(nei, Z, M, !match);
        }
    }
    vector<int> get_node_cover() {
        /*
            call compute_max_flow

            link -> https://stackoverflow.com/questions/42836016/algorithm-for-minimum-vertex-cover-in-bipartite-graph

            let M be the maximum matching

            find U the set (possibly empty) of unmatched 
            vertices in X (not connected to any edge in M)

            build Z the set or vertices either in U, or connected 
            to U by alternating paths (paths that alternate between 
            edges of M and edges not in M)

            then K = (X \ Z) U (Y ∩ Z) is a minimum vertex cover
        */
        vector<pair<int, int>> matching = get_max_matching();
        vector<int> unmatched(n, 1);
        set<pair<int, int>> M;
        for (auto [u, v] : matching) {
            M.insert({min(u, v), max(u, v)});
            unmatched[u] = unmatched[v] = 0;
        }
        vector<int> Z(n);
        fill(all(color), 0);
        color[src] = color[sink] = 1;
        for (int node = 0; node < n; node++) {
            if (unmatched[node] && X[node]) {
                if (color[node]) {
                    continue;
                }
                color[node] = 1;
                alternate_path(node, Z, M, false);
            }
        }
        vector<int> node_cover(n);
        for (int node = 0; node < n; node++) {
            if ((X[node] && !Z[node]) || (!X[node] && Z[node])) {
                node_cover[node] = 1;
            }
        }
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

vector<int64_t> compute_sieve(int64_t n) {
    /*
        Sieve algorithm
        Time: n*log(log(n))
    */
    vector<int64_t> sieve(n+1, 0);
    for (int64_t x = 2; x <= n; x++) {
        if (sieve[x]) continue;
        for (int64_t i = x*2; i <= n; i += x) {
            sieve[i] = x;
        }
    }
    return sieve;
}

int main() {
    
    /* 甘草 */
    licorice

    i64 n; cin >> n;
    vector<i64> A(n);
    read(A, n);
    vector<i64> sieve = compute_sieve(2e5);
    int idx = -1;
    for (int i = 0; i < n; i++) {
        if (A[i] == 1) {
            idx = i;
        }
    }
    MaxFlow maxflow;
    maxflow.init(n+2, n, n+1);
    for (int i = 0; i < n; i++) {
        if (A[i] == 1 && i != idx) {
            continue;
        }
        for (int j = i+1; j < n; j++) {
            if (A[j] == 1 && j != idx) {
                continue;
            }
            if (sieve[A[i]+A[j]] == 0) {
                int u = j, v = i;
                if (A[i]%2 == 0) {
                    /* A[j] is odd because sum is prime */
                    swap(u, v);
                }
                maxflow.add_edge(u, v);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (A[i] == 1 && i != idx) {
            continue;
        }
        if (A[i]%2 == 0) {
            maxflow.add_edge(maxflow.src, i);
        } else {
            maxflow.add_edge(i, maxflow.sink);
        }
    }
    maxflow.compute_max_flow();
    vector<int> node_cover = maxflow.get_node_cover();
    for (int i = 0; i < n; i++) {
        if (A[i] == 1 && i != idx) {
            node_cover[i] = 1;
        }
    }
    print(accumulate(all(node_cover), 0));
    for (int i = 0; i < n; i++) {
        if (node_cover[i]) {
            cout << A[i] << " ";
        }
    }
    cout << endl;

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