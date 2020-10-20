// mul is prime exponentiation table, and primes is a list of primes
vector<pair<ll, ll>> prime_factorize(ll n, const vi& primes, const vector<vi>& mul)
{
	vector<pair<ll, ll>> ans;
	for (int i = 0; i < primes.size() && primes[i] <= n; i++) {
		ll p = primes[i];
		if (n % p == 0) {
			int l = 1, r = mul[i].size() - 1, bst = 1;
			while (l <= r)
			{
				int mid = (l + r) / 2;
				if (n % mul[i][mid] == 0) {
					l = mid + 1;
					bst = mid;
				}
				else {
					r = mid - 1;
				}
			}
			n /= mul[i][bst];
			ans.pb(pair<ll, ll>(p, bst));
		}
	}
	if (n != 1) {
		ans.pb(pair<ll, ll>(n, 1));
	}
	return ans;
}
