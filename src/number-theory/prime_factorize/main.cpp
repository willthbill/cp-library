// mul is prime exponentiation table, and primes is a list of primes
vector<pair<ll, ll>> prime_factorize(ll n, const vector<ll>& primes, const vector<vector<ll>>& mul)
{
	vector<pair<ll, ll>> ans;
	for (int i = 0; i < (int) primes.size() && primes[i] <= n && n > 1; i++) {
		ll p = primes[i];
		if (n % p == 0) {
			int l = 1, r = (int)mul[i].size() - 1, bst = 1;
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
			ans.push_back(pair<ll, ll>(p, bst));
		}
	}
	if (n != 1) {
		ans.push_back(pair<ll, ll>(n, 1));
	}
	return ans;
}
vector<pair<ll,ll>> prime_factorize(ll n){ // O(sqrt(n)) at most (if n is prime)
	vector<pair<ll,ll>> res;
	if(n % 2 == 0){
		res.push_back({2,0});
		while(n % 2 == 0) n/=2, res[0].second++;
	}
	for(ll i = 3; i * i <= n; i+=2){
		if(n % i == 0){
			res.push_back({i, 0});
			int idx = (int)res.size() - 1;
			while(n%i == 0) n/=i, res[idx].second++;
		}
	}
	if(n > 1) res.push_back({n, 1});
	return res;
}
