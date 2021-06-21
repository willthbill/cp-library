// this is for getting for example min range queries in O(1)
// with O(n log n) precomputation
template<class T, T(*F)(T,T)>
struct RQA { // requires F(x, F(x, x)) = F(F(x, x), x) = x
    vector<vector<T>> M;
    int n;
    RQA(vector<T> A) {
        n = A.size();
        M = vector<vector<T>>(17,vector<T>(n));
        for(int i = 0; i < n; i++) {
            M[0][i] = A[i];
        }
        for(int k = 1; k < 17; k++) {
            for(int i = 0; i < n; i++) {
                int nxt = min(n - 1, i + (1 << (k - 1)));
                M[k][i] = F(M[k - 1][i], M[k - 1][nxt]);
            }
        }
    }
    T q(int l, int r) {
        int k = hik(r - l + 1);
        return F(M[k][l], M[k][r - (1 << k) + 1]);
    }
};