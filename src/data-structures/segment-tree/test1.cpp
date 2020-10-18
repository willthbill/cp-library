// https://cses.fi/problemset/task/1648
#include<bits/stdc++.h>
using namespace std;
template<class T, T(*F)(T,T)>
struct ST{
    int N;
    T baseval;
    vector<T> arr; 
    ST(){}
    void setsize(int _N){
        N=_N;
        int size = 1;
        while(size < 2*N) size<<=1;
        arr=vector<T> (2 * size);
    }
    ST(int _N, T _baseval){setsize(_N); baseval=_baseval;}
    ST(int _N, T _baseval, vector<T>&a){
        baseval = _baseval;
        setsize(_N);
       _build(1,0,N-1,a);
    }
    T _build(int idx, int l, int r, vector<T>& a){
        if(l == r) return (arr[idx] = a[l]);
        int m = (l + r) / 2;
        return (arr[idx] = F(_build(idx*2,l,m,a),_build(idx*2+1,m+1,r,a)));
    }
    void _u(int idx, int l, int r, int qidx, int qval){
        if(l == r) {
            arr[idx] = qval;
            return;
        }
        int m = (l + r) / 2;
        if(qidx >= l && qidx <= m) _u(idx*2,l,m,qidx,qval);
        else _u(idx*2+1,m+1,r,qidx,qval);
        arr[idx] = F(arr[idx*2],arr[idx*2+1]);
    }
    void u(int qidx, int qval){
        _u(1,0,N-1,qidx,qval);
    }
    T _q(int idx, int l, int r, int ql, int qr){
        if(l > qr || r < ql) return baseval;
        if(l >= ql && r <= qr) return arr[idx];
        int m = (l + r) / 2;
        return F(_q(idx*2,l,m,ql,qr),_q(idx*2+1,m+1,r,ql,qr));
    }
    T q(int ql, int qr){
        return _q(1,0,N-1,ql,qr);
    }
};
long long merge(long long a, long long b){
    return a + b;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ST<long long,merge> st;
    int N, Q; cin >> N >> Q;
    vector<long long> arr (N);
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
    st = ST<long long, merge>(N, 0, arr);
    for(int i = 0; i < Q; i++){
        int a, b, c; cin >> a >> b >> c;
        if(a == 1){
            st.u(b - 1, c);
        }else{
            cout << st.q(b-1,c-1) << endl;
        }
    }
}
