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
