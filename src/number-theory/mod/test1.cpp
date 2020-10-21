// https://cses.fi/problemset/task/1095
#pragma GCC Optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MOD 1000000007;
ll mpow(ll a, int b){ // a^b % m
	ll res = 1;
	while(b){
		if(b & 1) res = (res * a) % MOD;
		b >>= 1;
		a = (a * a) % MOD;
	}
	return res;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;
	while(t--)
	{
		int a, b;
		cin >> a >> b;
		cout << mpow(a, b) << endl;
	}
}
