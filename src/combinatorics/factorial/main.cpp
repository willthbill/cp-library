vector<ll> get_factorials(ll n, ll m) {
	vector<ll> f(n + 1);
	f[0] = 1;
	for(ll i = 1; i <= n; i++)
		f[i] = f[i-1]*i % m;
	return f;
}
