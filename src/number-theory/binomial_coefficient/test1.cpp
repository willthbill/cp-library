#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mod_pow(ll a, ll b, ll m) // a^b % m
{
	ll res = 1;
	while(b)
	{
		if(b & 1) res = res * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return res;
}

ll nck(ll n, ll k, ll m, vector<ll>& factorials) { // m is big prime
	assert(n >= k);
	assert(int(factorials.size()) > n);
	return factorials[n] * mod_pow(factorials[n - k] * factorials[k] % m, m - 2, m) % m;
}

int main(){
	int q;
	cin >> q;
	const int mod = 1e9 + 7;
	vector<ll> f(1e6 + 1); f[0] = 1;
	for(int i = 1; i <= int(1e6); i++) 
		f[i] = f[i - 1] * i % mod;
	while(q--){
		ll a, b;
		cin >> a >> b;
		cout << nck(a, b, mod, f) << endl;
	}
}

