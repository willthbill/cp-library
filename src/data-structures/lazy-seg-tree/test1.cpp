// https://cses.fi/problemset/task/1735/
#include<bits/stdc++.h>
using namespace std;
template<class T, T(*mergeF)(T,T), T(*addF)(T,int,int,T), T(*setF)(int,int,T), T(*mergeAddsF)(T,T)>
struct LazyST{
	int N;
	T baseval, neutralval;
	LazyST(){}
	vector<T> arr, toadd, toset;
	vector<bool> shouldBeSet;
    void setsize(int _N){
        N=_N;
        int size = 1;
        while(size < 2*N) size<<=1;
        arr=vector<T> (2 * size);
        toadd=vector<T> (2 * size);
        toset=vector<T> (2 * size);
		shouldBeSet=vector<bool> (2 * size);
    }
    LazyST(int _N, T _baseval, T _neutralval){
		setsize(_N); baseval=_baseval; neutralval=_neutralval;
	}
	void _build(int idx, int l, int r, vector<T>& a){
		if(l == r) arr[idx] = a[l];
		else{
			int m = (l + r) / 2;
			_build(idx * 2, l, m, a);
			_build(idx * 2 + 1, m + 1, r, a);
			arr[idx] = mergeF(arr[idx * 2], arr[idx * 2 + 1]);
		}
	}
	LazyST(int _N, T _baseval, T _neutralval, vector<T>&a){
        baseval = _baseval;
		neutralval = _neutralval;
        setsize(_N);
       _build(1,0,N-1,a);
    }
	void lazydown(int idx, int l, int r){
		if(shouldBeSet[idx]){
			shouldBeSet[idx] = 0;
			arr[idx] = setF(l, r, toset[idx]);
			if(l != r){
				toset[idx*2] = toset[idx];
				toadd[idx*2] = neutralval;
				shouldBeSet[idx*2] = 1;
				toset[idx*2+1] = toset[idx];
				toadd[idx*2+1] = neutralval;
				shouldBeSet[idx*2+1] = 1;
			}
			toset[idx] = neutralval;
		}
		if(toadd[idx] != neutralval){
			arr[idx] = addF(arr[idx], l, r, toadd[idx]);
			if(l != r){
				toadd[idx*2] = mergeAddsF(toadd[idx*2], toadd[idx]);
				toadd[idx*2+1] = mergeAddsF(toadd[idx*2+1], toadd[idx]);
			}
			toadd[idx] = neutralval;
		}
	}
	void _addrange(int idx, int l, int r, int ql, int qr, T val){
		if(r < ql || l > qr) lazydown(idx,l,r);
		else if(l >= ql && r <= qr){
			toadd[idx] = mergeAddsF(toadd[idx], val);
			lazydown(idx, l, r);
		}else{
			lazydown(idx, l, r);
			int m = (l + r) / 2;
			_addrange(idx * 2, l, m, ql, qr, val);
			_addrange(idx * 2 + 1, m + 1, r, ql, qr, val);
			arr[idx] = mergeF(arr[idx*2], arr[idx*2+1]);
		}
	}
	void addrange(int ql, int qr, int val){
		_addrange(1, 0, N-1, ql, qr, val);
	}
	void _setrange(int idx, int l, int r, int ql, int qr, T val){
		if(r < ql || l > qr) lazydown(idx,l,r);
		else if(l >= ql && r <= qr){
			toset[idx] = val;
			toadd[idx] = neutralval;
			shouldBeSet[idx] = 1;
			lazydown(idx, l, r);
		}else{
			lazydown(idx, l, r);
			int m = (l + r) / 2;
			_setrange(idx * 2, l, m, ql, qr, val);
			_setrange(idx * 2 + 1, m + 1, r, ql, qr, val);
			arr[idx] = mergeF(arr[idx*2], arr[idx*2+1]);
		}
	}
	void setrange(int ql, int qr, int val){
		_setrange(1, 0, N-1, ql, qr, val);
	}
	T _q(int idx, int l, int r, int ql, int qr){
		if(r < ql || l > qr) return baseval;
		else if(l >= ql && r <= qr){
			lazydown(idx, l, r);
			return arr[idx];
		}else{
			int m = (l + r) / 2;
			lazydown(idx, l, r);
			return mergeF(_q(idx * 2, l, m, ql, qr), _q(idx * 2 + 1, m + 1, r, ql, qr));
		}
	}
	T q(int ql, int qr){
		return _q(1,0,N-1,ql,qr);
	}
};
long long MERGE(long long a, long long b){ // merge two nodes
	return a + b;
}
long long ADD(long long a, int l, int r, long long b){ // add b to a, where a = arr[idx] for some idx
	return a + (r - l + 1) * b;
}
long long SET(int l, int r, long long val){
	return (r - l + 1) * val;
}
long long MERGEADDS(long long a, long long b){
	return a + b;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, q; cin >> n >> q;
	vector<long long> t (n);
	for(int i = 0; i < n; i++){
		cin >> t[i];
	}
	LazyST<long long, MERGE, ADD, SET, MERGEADDS> lst;
	lst = LazyST<long long, MERGE, ADD, SET, MERGEADDS> (n, 0, 0, t);
	for(int i = 0; i < q; i++){
		int type; cin >> type;
		if(type == 1){
			int a,b,x; cin >> a >> b >> x;
			lst.addrange(a-1,b-1,x);
		}else if(type == 2){
			int a,b,x; cin >> a >> b >> x;
			lst.setrange(a-1,b-1,x);
		}else{
			int a,b; cin >> a >> b;
			cout << lst.q(a-1,b-1) << endl;
		}
	}
}
