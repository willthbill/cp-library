%include<number-theory/mod>%

ll choose(ll n, ll k, ll m, vector<ll>& factorials) { // m is big prime
	assert(n >= k);
	assert(int(factorials.size()) > n);
	return factorials[n] * mpow(factorials[n - k] * factorials[k] % m, m - 2, m) % m;
}
