// https://atcoder.jp/contests/abc218/tasks/abc218_g
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back

struct median_tracker {
    multiset<int, greater<int>> left;
    multiset<int> right; // if odd amount in total, then more in left
    void _balance() {
        while(left.size() > right.size()) {
            right.insert(*left.begin());
            left.erase(left.begin());
        }
        while(left.size() < right.size()) {
            left.insert(*right.begin());
            right.erase(right.begin());
        }
    }
    int median() {
        assert(left.size() + right.size() > 0);
        if((left.size() + right.size()) % 2 == 0) {
            return (*left.begin() + *right.begin()) / 2;
        }else {
            return *left.begin();
        }
    }
    void insert(int val) {
        if(left.empty() || val > *left.begin()) right.insert(val);
        else left.insert(val);
        _balance();
    }
    void erase(int val) {
        if(val > median()) right.erase(right.find(val));
        else left.erase(left.find(val));
        _balance();
    }
};

vector<int> median;
vector<vector<int>> adj;
int dp(int at, int p, bool which) {
    if(adj[at].size() == 1 && at != 0) {
        return median[at];
    }
    if(which) {
        int mx = -100000;
        for(int nxt : adj[at]) {
            if(nxt != p) mx = max(mx, dp(nxt, at, !which));
        }
        return mx;
    } else {
        int mn = LLONG_MAX;
        for(int nxt : adj[at]) {
            if(nxt != p) mn = min(mn, dp(nxt, at, !which));
        }
        return mn;
    }
}


signed main() {
    int n; cin >> n;
    vector<int> A(n);
    for(int i = 0; i < n; i++) cin >> A[i];
    adj = vector<vector<int>>(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    median = vector<int>(n);
    median_tracker vals;
    function<void(int,int)> dfs = [&](int at, int p) {
        vals.insert(A[at]);
        if(adj[at].size() == 1 && at != 0) {
            median[at] = vals.median();
        }
        for(int nxt : adj[at]) {
            if(nxt != p) dfs(nxt, at);
        }
        vals.erase(A[at]);
    };
    dfs(0, -1);
    cout << dp(0, -1, 1) << endl;
}