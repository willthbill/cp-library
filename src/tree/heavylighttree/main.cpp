#include <bits/stdc++.h>
using namespace std;
#define printl(x, y) for (auto z = x.begin(); z != x.end(); z++) cout << *z << (z == x.end()-1 ? "\n" : y)
#define nextpow2(x) __builtin_popcount(x) == 1 ? x : (1 << (32-__builtin_clz(x)))
#define read(x, y) for (int i = 0; i < y; i++) cin >> x[i]
#define debug(x) cerr << #x << " : " << x << endl
#define print(x) cout << x << endl
#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()

class HL {
public:
    int n;
    const int HEAVY = 0;
    const int LIGHT = 1;
    vector<vector<tuple<int, int>>> sparse;
    vector<vector<int>> adj;
    vector<int> sz;
    vector<int> depth;
    vector<int> lft;
    vector<int> rht;
    vector<int> trav;
    vector<vector<int64_t>> hl_trees;
    vector<vector<int>> hlc;
    vector<int> hl_idx;
    vector<int> hl_edge_weight;
    vector<int> hl_comp;
    vector<int> hl_parent;

    HL(int n) {
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
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int64_t> A(n);
    read(A, n);
    HL tree(n);
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
