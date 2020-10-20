// https://www.hackerearth.com/practice/algorithms/graphs/breadth-first-search/practice-problems/algorithm/containers-of-choclates-1/description/
#include<bits/stdc++.h>
using namespace std;
struct DSU{
    vector<int> par, rank, size;
    DSU(int n, bool setAll = true){
        par = vector<int> (n, -1);
        rank = vector<int> (n);
        size = vector<int> (n);
        if(setAll) {
            for(int i = 0; i < n; i++) par[i] = i, rank[i] = 1, size[i] = 1;
        }
    }
    void make_set(int a){
        assert(par[a] == -1);
        par[a] = a;
        rank[a] = 1;
        size[a] = 1;
    }
    int find_set(int a){
        if(par[a] != a) par[a] = find_set(par[a]);
        return par[a];
    }
    void union_sets(int a, int b){
        a = find_set(a);
        b = find_set(b);
        if(a != b){
            if(rank[a] > rank[b]) par[b] = a, size[a] += size[b];
            else{
                size[b] += size[a];
                if(rank[a] == rank[b]) rank[b]++;
                par[a] = b;
            }
        }
    }
};
int main(){
    int t; cin >> t;
    for(int k = 1; k <= t; k++){
        int n; cin >> n;
        DSU uf (2e4, true);
        vector<vector<int>> nots (2e4);
        for(int i = 0; i < n; i++){
            int a, b; cin >> a >> b;
            a--, b--;
            nots[a].push_back(b);
            nots[b].push_back(a);
        }
        for(int i = 0; i < 2e4; i++){
            for(int j = 1; j < nots[i].size(); j++){
                uf.union_sets(nots[i][0], nots[i][j]);
            }
        }
        int res = 0;
        vector<bool> seen (2e4);
        for(int i = 0; i < 2e4; i++){
            if(nots[i].size() == 0){
                continue;
            }
            int s1 = uf.find_set(nots[i][0]);
            int s2 = uf.find_set(i);
            if(seen[s1]) continue;
            seen[s1] = 1, seen[s2] = 1;
            res += max(uf.size[s1], uf.size[s2]);
        }
        cout << "Case " << k << ": " << res << endl;
    }
}
