// https://cses.fi/problemset/task/1688/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back

// BEGIN code block of: tree/lca
// Standard message: The following is code from https://github.com/williamMBDK/cp-library but was copied from a local copy of the repository. Changes to the original source may have been done here.
// BEGIN code block of: data-structures/sparse-table-constant
// this is for getting for example min range queries in O(1)
// with O(n log n) precomputation
template<class T, T(*F)(T,T)>
struct SPS { // requires F(x, F(x, x)) = F(F(x, x), x) = x
    vector<vector<T>> M;
    vector<int> hik;
    int n;
    int logn;
    SPS(){}
    SPS(vector<T>& A) {
        n = A.size();
        logn = 0;
        while(1<<logn < n) logn++;
        hik = vector<int> (n + 1);
        for(int i = 2; i <= n; i++) hik[i] = hik[i/2] + 1;
        M = vector<vector<T>>(logn,vector<T>(n));
        for(int i = 0; i < n; i++) M[0][i] = A[i];
        for(int k = 1; k < logn; k++) for(int i = 0; i < n; i++) {
            int nxt = min(n - 1, i + (1 << (k - 1)));
            M[k][i] = F(M[k - 1][i], M[k - 1][nxt]);
        }
    }
    T q(int l, int r) {
        assert(l <= r);
        int k = hik[r - l + 1];
        return F(M[k][l], M[k][r - (1 << k) + 1]);
    }
};
// END code block of: data-structures/sparse-table-constant
// LCA with 0-indexed nodes, O(n lg n) build and O(1) query
struct LCA {
    int n, root;
    vector<vector<int>> adj;
    vector<pair<int,int>> levels;
    vector<int> idxinlevels;
    static pair<int,int> mn(pair<int,int> a, pair<int,int> b) {
        return min(a,b);
    }
    SPS<pair<int,int>,mn> sps;
    LCA() {}
	LCA(int n, int root = 0) : n(n), root(root), adj(vector<vector<int>> (n)) {}
	LCA(vector<vector<int>>& adj, int root = 0) : n(adj.size()), root(root), adj(adj) {
        build_lca();
    }
    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    void dfs(int node, int p = -1, int level = 0) {
        idxinlevels[node] = levels.size();
        levels.push_back({level, node});
        for(auto& ch : adj[node]) {
            if(ch == p) continue;
            dfs(ch, node, level + 1);
            levels.push_back({level, node});
        }
    }
	void build_lca() {
        idxinlevels = vector<int> (n);
        dfs(root);
        sps = SPS<pair<int,int>, mn> (levels);
    }
	int lca(int a, int b) {
        a = idxinlevels[a], b = idxinlevels[b];
        return sps.q(min(a,b), max(a,b)).second;
	}
};
// END code block of: tree/lca
int main(){
	cin.sync_with_stdio(false); cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	LCA lca(n);
	for(int i = 1; i < n; i++) {
		int a;
		cin >> a, a--;
		lca.add_edge(a, i);
	}
	lca.build_lca();
	while(q--) {
		int a, b;
		cin >> a >> b;
		cout << lca.lca(a - 1, b - 1) + 1 << endl;
	}
}

