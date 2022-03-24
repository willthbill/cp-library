// thanks to https://codeforces.com/blog/entry/72488
template<class Int>
vector<Int> mobius_transform(int n, vector<Int> f) {
    for(int i = 0; i < n; i++) {
        for(int mask = 0; mask < (1 << n); mask++) {
            if((mask & (1 << i)) != 0) {
                f[mask] -= f[mask ^ (1 << i)];
            }
        }
    }
    return f;
}
