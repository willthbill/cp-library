// Find brigdes and articulation points in undirected graphs
// Vertices numbered from 0 to n-1
struct BridgesAndArtPoints {
    int n = -1;
    vector<vector<int>> adj; // adjacency list
    vector<int> low_link; // smallest depth reachable from a subtree
    vector<int> depth; // depth of node in dfs tree
    vector<pair<int,int>> bridges;
    vector<int> art_points;
    BridgesAndArtPoints() {}
    BridgesAndArtPoints(vector<vector<int>>& _adj) {
        n = (int)_adj.size();
        adj = _adj;
        depth = vector<int> (n,-1); // -1 means not visited
        low_link = vector<int> (n);
    }
    vector<pair<int,int>> get_bridges() {_init(); return bridges;}
    vector<int> get_art_points() {_init(); return art_points;}
    void _init() {
        assert(n != -1);
        for(int i = 0; i < n; i++) {
            if(depth[i] == -1) {
                _dfs(i,0,-1);
            }
        }
    }
    // gets low link values: smallest depth reachable from a subtree using back edges
    void _dfs(int node, int d, int parent) {
        low_link[node] = d;
        depth[node] = d;
        int cnt_fwd_edges = 0;
        bool is_art_point = 0;
        for(int& nb : adj[node]) {
            if(nb == parent) continue;
            if(depth[nb] != -1) { // node is visited, its a back-edge
                low_link[node] = min(low_link[node], depth[nb]);
            } else { // forward edge
                _dfs(nb, d + 1, node);
                low_link[node] = min(low_link[node], low_link[nb]);
                cnt_fwd_edges++;
                if(d < low_link[nb]) {
                    bridges.push_back({node, nb});
                }
                if(parent != -1 && d <= low_link[nb]) {
                    is_art_point = 1;
                }
            }
        }
        if(parent == -1 && cnt_fwd_edges >= 2) {
            is_art_point = 1;
        }
        if(is_art_point) {
            art_points.push_back(node);
        }
    }
};
