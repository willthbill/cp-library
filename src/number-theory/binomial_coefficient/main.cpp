%include<number-theory/mod_pow>%

ll choose(ll n, ll k, ll m, vector<ll>& factorials) { // m is big prime
	assert(n >= k);
	assert(int(factorials.size()) > n);
	return factorials[n] * mod_pow(factorials[n - k] * factorials[k] % m, m - 2, m) % m;
}
