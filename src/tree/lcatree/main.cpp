#include <bits/stdc++.h>
using namespace std;
#define printl(x, y) for (auto z = x.begin(); z != x.end(); z++) cout << *z << (z == x.end()-1 ? "\n" : y)
#define nextpow2(x) __builtin_popcount(x) == 1 ? x : (1 << (32-__builtin_clz(x)))
#define read(x, y) for (int i = 0; i < y; i++) cin >> x[i]
#define debug(x) cerr << #x << " : " << x << endl
#define print(x) cout << x << endl
#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()

class LCA {
public:
    int n;
    vector<vector<tuple<int, int>>> sparse;
    vector<vector<int>> succ;
    vector<vector<int>> adj;
    vector<int> adj_t;
    vector<int> sz;
    vector<int> depth;
    vector<int> lft;
    vector<int> rht;
    vector<int> trav;

    LCA(int n) {
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
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int64_t> A(n);
    LCA tree(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v; u--, v--;
        tree.add_edge(u, v);
    }
    tree.compute_lca();

	return 0;
}
