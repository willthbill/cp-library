/*
    link -> https://cses.fi/book/book.pdf

    tested on:
    - https://codeforces.com/contest/808/problem/F
    - https://cses.fi/problemset/task/1694/
    - https://cses.fi/problemset/task/1695/
    - https://cses.fi/problemset/task/1696/
    - https://cses.fi/problemset/task/1711/
    - https://csacademy.com/contest/round-23/task/no-prime-sum/
      TLE on 1 out of 22 cases because limit is tight (uses 1096ms limit is 1000ms)

    scaling algorithm is used to find max flow
    time complexity is O(m^2 log(c))

    compared to edmonds-karp algorithm that is O(m^2 n)

    min-cut = maximum matching in bipartite graph

    edge-disjoint paths:
    max number of edge-disjoint paths = max flow when capacity of all edges = 1
    edge-disjoint paths are found by greedily following paths from src to 
    sink after max flow computation

    node-disjoint paths:
    divide each node such that first node has incoming edges and second node 
    has outgoing edges. make edge between the two nodes
    then problem becomes edge-disjoint paths

    hall's theorem:
    if the number of left and right nodes is the same, 
    hall's theorem tells us IF it is possible to construct a perfect matching
    that contains all nodes of the graph
    a matching that contains all left nodes exists exactly when for
    each X, the condition |X| <= |f(X)| holds
    where X is any set of left nodes and f(X) is the set of their neighbors

    konig's theorem:
    the size of a minimum node cover and the size of a maximum matching are always equal

    independent set:
    nodes that do not belong to a minimum node cover form a maximum
    independent set. this is the largest possible set of nodes such that no two
    nodes in the set are connected with an edge

    minimum node-disjoint path cover:
    found by constructing a bipartite graph where each node of the original graph 
    is represented by two nodes: a left node and a right node
    there is an edge from a left node to a right node if there
    is such an edge in the original graph. 
    a maximum matching is then a minimum node-disjoint path cover

    minimum general path cover:
    almost same as minimum node-disjoint path cover
    there is an edge from left to right if there is a path in original graph

    dilworth's theorem:
    an antichain is a set of nodes of a graph such that there is no path from any
    node to another node using the edges of the graph.
    in a directed acyclic graph, the size of a minimum general path cover equals
    the size of a maximum antichain
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