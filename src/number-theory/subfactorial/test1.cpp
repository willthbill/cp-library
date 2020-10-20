#include <bits/stdc++.h>
using namespace std;
typedef long long ll;  

vector<ll> get_subfactorials(ll n, ll m) { // m is modulo
	vector<ll> f(n + 1);
	f[0] = 1, f[1] = 0;
	for(int i = 2; i <= n; i++)
		f[i] = (i - 1)*(f[i - 1] + f[i - 2]) % m;
	return f;
}

int main(){
    ll n;cin >> n;
    vector<ll> A = get_subfactorials(n, 1e9 + 7);
	cout << A[n] << endl;
}
