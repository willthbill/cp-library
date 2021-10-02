#include <bits/stdc++.h>
using namespace std;
#define printl(x, y) for (auto z = x.begin(); z != x.end(); z++) cout << *z << (z == x.end()-1 ? "\n" : y)
#define nextpow2(x) __builtin_popcount(x) == 1 ? x : (1 << (32-__builtin_clz(x)))
#define read(x, y) for (int i = 0; i < y; i++) cin >> x[i]
#define debug(x) cerr << #x << " : " << x << endl
#define print(x) cout << x << endl
#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()

class SuperTree {
public:
    int n;
    const int HEAVY = 0;
    const int LIGHT = 1;
    vector<vector<tuple<int, int>>> sparse;
    vector<vector<int>> succ;
    vector<vector<int>> adj;
    vector<int> adj_t;
    vector<int> sz;
    vector<int> depth;
    vector<int> dist_I;
    vector<int> dist_II;
    vector<int> lft;
    vector<int> rht;
    vector<int> trav;
    vector<int> array_idx;
    vector<int> array_sz;
    vector<int64_t> array_value;
    vector<vector<int64_t>> hl_trees;
    vector<vector<int>> hlc;
    vector<int> hl_idx;
    vector<int> hl_edge_weight;
    vector<int> hl_comp;
    vector<int> hl_parent;
    vector<int> centroid;

    SuperTree(int n) {
        this->n = n;
        adj.resize(n);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void compute_size(int root) {
        /*
            Computes the size of all subtrees
            Stores result in sz vector
            Time: n
        */
        sz.resize(n, 1);
        compute_size_dfs(root, -1);
    }

    void compute_size_dfs(int node, int parent) {
        for (auto nei : adj[node]) {
            if (nei == parent) continue;
            compute_size_dfs(nei, node);
            sz[node] += sz[nei];
        }
    }

    void compute_depth(int root, int root_depth) {
        /*
            Computes the depth of all nodes
            Stores result in depth vector
            Time: n
        */
        depth.resize(n, -1);
        compute_size_dfs(root, -1, root_depth);
    }

    void compute_size_dfs(int node, int parent, int d) {
        depth[node] = d;
        for (auto nei : adj[node]) {
            if (nei == parent) continue;
            compute_size_dfs(nei, node, d+1);
        }
    }

    int diameter() {
        /*
            Computes diameter of the tree
            Diameter is the maximum distance between two nodes
            Time: n
        */
        return get<0>(diameter_dfs(get<1>(diameter_dfs(0, -1, 0)), -1, 0));
    }

    tuple<int, int> diameter_dfs(int node, int parent, int d) {
        tuple<int, int> mx = make_tuple(d, node);
        for (auto nei : adj[node]) {
            if (nei == parent) continue;
            mx = max(mx, diameter_dfs(nei, node, d+1));
        }
        return mx;
    }

    void compute_dist_I() {
        /*
            Computes the maximum distance from all nodes to any other node
            The dist is stored in dist_I vector
            Time: n
        */
        vector<int> mx_depth(n);
        vector<int> second_mx_depth(n);
        dist_I.resize(n);
        dist_I_precompute(mx_depth, second_mx_depth, 0, -1, 0);
        dist_I_dfs(mx_depth, second_mx_depth, 0, -1, 0);
    }

    int dist_I_precompute(vector<int>& mx_d, vector<int>& snd_mx_d, int node, int parent, int d) {
        for (auto nei : adj[node]) {
            if (nei == parent) continue;
            int current = dist_I_precompute(mx_d, snd_mx_d, nei, node, d+1)-d;
            if (mx_d[node] < current) {
                snd_mx_d[node] = mx_d[node];
                mx_d[node] = current;
            } else if (snd_mx_d[node] < current) {
                snd_mx_d[node] = current;
            }
        }
        return d+mx_d[node];
    }
    
    void dist_I_dfs(vector<int>& mx_d, vector<int>& snd_mx_d, int node, int parent, int mx) {
        dist_I[node] = max(mx_d[node], mx);
        for (auto nei : adj[node]) {
            if (nei == parent) continue;
            int current = max(mx, mx_d[node] == mx_d[nei]+1 ? snd_mx_d[node] : mx_d[node])+1;
            dist_I_dfs(mx_d, snd_mx_d, nei, node, current);
        }
    }

    void compute_dist_II() {
        /*
            Computes the sum of distances from all nodes all other node
            The sum is stored in dist_II vector
            Time: n
        */
        dist_II.resize(n);
        compute_size(0);
        compute_depth(0, 0);
        int64_t sum = 0;
        for (auto x : depth) sum += x;
        dist_II_dfs(0, -1, sum);
    }

    void dist_II_dfs(int node, int parent, int64_t sum) {
        for (auto nei : adj[node]) {
            if (nei == parent) continue;
            dist_II_dfs(nei, node, sum+sz[0]-2*sz[nei]);
        }
        dist_II[node] = sum;
    }

    void compute_binary_lifting() {
        /*
            Precomputes information to call binary_lift
            Time: n*log(n)
        */
        int size = __builtin_popcount(n) == 1 ? n : (1 << (32-__builtin_clz(n)));
        succ.resize(n, vector<int>(size, -1));
        adj_t.resize(n, n-1);
        compute_adj_t(0, n-1);
        for (int x = 0; x < n; x++) succ[x][0] = adj_t[x];
        for (int k = 1; k < size; k++) {
            for (int x = 0; x < n; x++) {
                succ[x][k] = succ[succ[x][k-1]][k-1];
            }
        }
    }

    void compute_adj_t(int node, int parent) {
        adj_t[node] = parent;
        for (auto nei : adj[node]) {
            if (nei == parent) continue;
            compute_adj_t(nei, node);
        }
    }
 
    int binary_lift(int x, int k) {
        /*
            Who is node x, kth ancestor
            Time: log(n)
        */
        int p = x;
        for (int i = 0; i < (int)succ[0].size(); i++) {
            if ((k >> i) & 1) {
                p = succ[p][i];
            }
        }
        return p;
    }

    void compute_lca() {
        /*
            Precomputes information used when calculating lca
            Time: n*log(n)
        */
        int N = 2*n-1;
        int K = 32-__builtin_clz(N);
        sparse.resize(N, vector<tuple<int, int>>(K));
        lft.resize(n);
        rht.resize(n);
        adj.resize(n);
        compute_lca_dfs(0, -1, 1);
        for (int i = 0; i < N; i++) sparse[i][0] = make_tuple(depth[i], trav[i]);
        for (int i = 1; i <= K; i++) {
            for (int j = 0; j+(1 << i) <= N; j++) {
                sparse[j][i] = min(sparse[j][i-1], sparse[j+(1 << (i-1))][i-1]);
            }
        }
    }
    
    void compute_lca_dfs(int node, int parent, int d) {
        trav.push_back(node);
        depth.push_back(d);
        lft[node] = len(trav)-1;
        for (auto nei : adj[node]) {
            if (nei == parent) continue;
            compute_lca_dfs(nei, node, d+1);
            trav.push_back(node);
            depth.push_back(d);
        }
        rht[node] = len(trav)-1;
    }

    int lca(int a, int b) {
        /*
            Computes the lowest common ancestor of a and b
            Time: 1
        */
        a = lft[a];
        b = rht[b];
        if (b < a) swap(a, b);
        int i = 31-__builtin_clz(b-a+1);
        int j = 1 << i;
        return get<1>(min(sparse[a][i], sparse[b-j+1][i]));
    }

    int dist(int u, int v) {
        /*
            Computes the distance between u and v
            OBS: requires call to compute_lca() first
            Time: 1
        */
        return depth[lft[u]]+depth[lft[v]]-2*depth[lft[lca(u, v)]];
    }

    void compute_tree_array() {
        /*
            Computes the information for array_sz and array_idx
            OBS: array_value should be taken care of outside this class
            idx   : 0 1 5 2 3 6 7 8 4
            sz    : 9 2 1 1 4 1 1 1 1
            value : 2 3 4 5 3 4 3 1 1
            -------------------------
            example of how to use:
            node 4 links to sz[3]
            subtree have size sz[3] = 4
            values of nodes in subtree is
            value[3], ... , value[6]
            idx   : 0 1 5 2 # 6 7 8 4
            sz    : 9 2 1 1 # 1 1 1 1
            value : 2 3 4 5 # # # # 1
            Time: n
        */
       array_sz.resize(n);
       array_idx.resize(n);
       array_value.resize(n);
       compute_tree_array_dfs(0, -1);
    }

    int compute_tree_array_dfs(int node, int parent) {
        array_sz.push_back(1);
        array_idx[node] = len(sz)-1;
        for (auto nei : adj[node]) {
            if (nei == parent) continue;
            array_sz[array_idx[node]] += compute_tree_array_dfs(nei, node);
        }
        return array_sz[array_idx[node]];
    }

    void compute_heavy_light(vector<int64_t>& A) {
        /*
            Computes the information used in heavy light decomposition
            Sets value in heavy light components to A
            node i have value A[i]
            Time: n*log(n)
        */
        compute_size(0);
        hl_idx.resize(n, 0);
        hl_edge_weight.resize(n, 0);
        hl_comp.resize(n, 0);
        hl_parent.resize(n, 0);
        compute_heavy_light_dfs(0, -1);
        for (int i = 0; i < n; i++) {
            int first_on_path = 1;
            for (auto nei : adj[i]) {
                if (nei == hl_parent[i]) continue;
                if (hl_edge_weight[nei] == HEAVY) {
                    first_on_path = 0;
                    break;
                }
            }
            if (first_on_path) {
                int node = i;
                vector<int> path = {node};
                hl_comp[node] = len(hlc);
                while (true) {
                    if (node == 0) break;
                    int p = hl_parent[node];
                    if (hl_edge_weight[node] == HEAVY) {
                        path.push_back(p);
                        hl_comp[p] = len(hlc);
                    } else {
                        break;
                    }
                    node = p;
                }
                hlc.push_back(path);
            }
        }
        hl_trees.resize(len(hlc));
        for (int i = 0; i < len(hlc); i++) {
            int tree_sz;
            if (__builtin_popcount(len(hlc[i])) == 1) tree_sz = len(hlc[i]);
            else tree_sz = 1 << (32-__builtin_clz(len(hlc[i])));
            hl_trees[i].resize(2*tree_sz, 0);
            for (int j = 0; j < len(hlc[i]); j++) {
                int node = hlc[i][j];
                hl_idx[node] = j;
                hl_segtree_upd(i, j, A[node], tree_sz);
            }
        }
    }

    void compute_heavy_light_dfs(int node, int parent) {
        for (auto nei : adj[node]) {
            if (nei == parent) continue;
            if ((double)sz[nei] >= (double)sz[node]/2) {
                hl_edge_weight[nei] = HEAVY;
            } else {
                hl_edge_weight[nei] = LIGHT;
            }
            hl_parent[nei] = node;
            compute_heavy_light_dfs(nei, node);
        }
    }

    int64_t hl_segtree_qry(int t, int a, int b, int k, int x, int y) {
        if (y < a || b < x) return (int64_t)0;
        if (x >= a && b >= y) return hl_trees[t][k];
        int d = x+(y-x)/2;
        return max(hl_segtree_qry(t, a, b, k*2, x, d), hl_segtree_qry(t, a, b, k*2+1, d+1, y));
    }

    void hl_segtree_upd(int t, int k, int64_t x, int tree_sz) {
        k += tree_sz;
        hl_trees[t][k] += x;
        for (k /= 2; k >= 1; k /= 2) hl_trees[t][k] = max(hl_trees[t][k*2], hl_trees[t][k*2+1]);
    }
    
    void hl_segtree_upd(int k, int64_t x) {
        /*
            Adds x to node k
            Time: log(n)
        */
        int t = hl_comp[k];
        int tree_sz = len(hl_trees[hl_comp[k]])/2;
        k = hl_idx[k];
        k += tree_sz;
        hl_trees[t][k] += x;
        for (k /= 2; k >= 1; k /= 2) hl_trees[t][k] = max(hl_trees[t][k*2], hl_trees[t][k*2+1]);
    }

    int64_t heavy_light_qry(int a, int b) {
        /*
            This is an example of a heavy light query
            This queries for the maximum value on the path
            between node a and b
            OBS: this example uses lca and therefore compute_lca()
            should be called before using
            Time: log(n)
        */
        int64_t mx = 0;
        int l = lca(a, b);
        for (auto r : {a, b}) {
            while (true) {
                int path_sz = len(hlc[hl_comp[r]]);
                int tree_sz = len(hl_trees[hl_comp[r]]);
                if (hl_comp[r] == hl_comp[l]) {
                    // hl_comp[i] is the identifier for the segtree where i lies
                    // hl_idx[i] is the index on the segree where i lies
                    // hl_segtree_qry is always called with (x, x, x, 1, 0, tree_sz/2-1)
                    mx = max(mx, hl_segtree_qry(hl_comp[r], hl_idx[r], hl_idx[l], 1, 0, tree_sz/2-1));
                    break;
                }
                mx = max(mx, hl_segtree_qry(hl_comp[r], hl_idx[r], path_sz-1, 1, 0, tree_sz/2-1));
                if (hlc[hl_comp[r]][path_sz-1] == 0) break;
                // hlc contains the heavy light paths
                // hlc[hl_comp[i]] is the path i lies on
                // hlc[hl_comp[i]][path_sz-1] is the last node on the path i lies on
                r = hl_parent[hlc[hl_comp[r]][path_sz-1]];
            }
        }
        return mx;
    }

    int find_centroid(int node) {
        /*
            Finds the centroid fro the component where node is
            OBS: call compute_size() first
            Time: n, size of the component
        */
        if (centroid.empty()) centroid.resize(n, 0);
        return find_centroid_dfs(node, -1, sz[node]/2);
    }

    int find_centroid_dfs(int node, int parent, int threshold) {
        for (auto nei : adj[node]) {
            if (nei != parent && !centroid[nei] && sz[nei] > threshold) {
                return find_centroid_dfs(nei, node, threshold);
            }
        }
        return node;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int64_t> A(n);
    read(A, n);
    SuperTree tree(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v; u--, v--;
        tree.add_edge(u, v);
    }
    tree.compute_heavy_light(A);
    tree.compute_lca();
    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        if (t == 1) {
            int k, x; cin >> k >> x; k--;
            tree.hl_segtree_upd(k, x-A[k]);
            A[k] = x;
        } else {
            int a, b; cin >> a >> b; a--; b--;
            cout << tree.heavy_light_qry(a, b) << " ";
        }
    }
    cout << "\n";

	return 0;
}
