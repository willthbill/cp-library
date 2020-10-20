vector<vector<ll>> prime_exponentiation_table(ll mx, vector<ll>&primes) { // stops at mx
	vector<vi> mul(primes.size());
	for (int i = 0; i < primes.size() && primes[i] <= mx; i++) {
		ll p = primes[i];
		ll res = p;
		mul[i].pb(1);
		while (res <= mx) {
			mul[i].pb(res);
			res *= p;
		}
	}
	return mul;
}
