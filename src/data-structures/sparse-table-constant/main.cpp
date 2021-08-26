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
