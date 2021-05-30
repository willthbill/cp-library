// https://codeforces.com/problemset/problem/1526/D
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back

template<class Int>
struct BIT{ // all input should be 0-indexed, only supports sum-queries
    // one of the following may be used
        // rangequery: q(idx), q(a,b), add(idx,val), set(idx,Val), setupsingle(initial)
        // rangeupdate: q(idx), rangeadd(a,b,val), setuprange(initial)
    int n;
    vector<Int> arr, values;
    Int q(int idx){
        idx++; Int s = 0;
        while(idx>0) s+=arr[idx], idx-=(idx&(-idx));
        return s;
    }
    Int q(int a, int b){
        if(a == b) return values[a];
        return q(b)-q(a-1);
    }
    void add(int idx, Int val){
        values[idx]+=val;
        idx++;
        while(idx<n) arr[idx]+=val, idx+=(idx&(-idx));
    }
    void set(int idx, Int val){
        add(idx, val - values[idx]);
    }
    void rangeadd(int a, int b, Int val){
        add(a, val);
        if(b < n - 2) add(b + 1, -val);
    }
    BIT(){}
    void setup(int _n){
        n=_n+1, arr=vector<Int>(n), values=vector<Int> (_n);
    }
    BIT(int _n){
        setup(_n);
    }
    void setupsingle(vector<Int>& initial){
        for(int i = 0; i < n - 1; i++) add(i,initial[i]);
    }
    void setuprange(vector<Int>& initial){
        for(int i = 0; i < n - 1; i++) rangeadd(i,i,initial[i]);
    }
};

int invNumber(vector<int> A) { // A is a permutation
	int n = A.size();
	BIT<int> ft(n);
	vector<int> tmp(n, 0);
	ft.setupsingle(tmp);
	int ans = 0;
	for(int i = n - 1; i >= 0; i--) {
		ans += A[i] > 0 ? ft.q(A[i] - 1) : 0;
		ft.add(A[i], 1);
	}
	return ans;
}

// snýst um að finna inversion sem að heldur ákveðnum increasing subsequences (
// þau subsequence sem að innihalda sömu stafina).
int calc(string a, string b) {
	int n = a.size();
	map<char, vector<int>> idx;
	map<char, int> at;
	for(int i = 0; i < n; i++) {
		idx[a[i]].pb(i);
	}
	vector<int> p;
	for(int i = 0; i < n; i++) {
		p.pb(idx[b[i]][at[b[i]]]);
		at[b[i]]++;
	}
	return invNumber(p);
}

signed main() {
	int t; cin >> t;
	while(t--) {
		string a; cin >> a;
		char alph[4] = {'A', 'N', 'O', 'T'};
		map<char, int> cnt;
		for(char k : a)
			cnt[k]++;
		int mn = -1;
		string ans = "";
		do {
			string res = "";
			for(char c : alph) {
				for(int i = 0; i < cnt[c]; i++)
					res.pb(c);
			}
			int r = calc(a, res);
			if(r > mn) {
				mn = r;
				ans = res;
			}
		}while(next_permutation(alph, alph + 4));
		cout << ans << endl;
	}
}