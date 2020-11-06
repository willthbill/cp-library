#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
#define pb push_back
#define fs first
#define sc second

void sieve(ll n, vector<ll>& P)
{
	vector<int> cnt(n + 1, 0);
	for (int i = 2; i <= n; i++)
	{
		for (int j = i; j <= n; j += i)
		{
			cnt[j]++;
		}
	}

	for (int i = 2; i < n + 1; i++) 
		if (cnt[i] == 1) 
			P.pb(i);
}

// START Generated output of: number-theory/prime_factorize
// mul is prime exponentiation table, and primes is a list of primes
vector<pair<ll, ll>> prime_factorize(ll n, const vector<ll>& primes, const vector<vector<ll>>& mul)
{
	vector<pair<ll, ll>> ans;
	for (int i = 0; i < (int)primes.size() && primes[i] <= n && n > 1; i++) {
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
vector<pair<ll, ll>> prime_factorize(ll n) { // O(sqrt(n)) at most (if n is prime)
	vector<pair<ll, ll>> res;
	if (n % 2 == 0) {
		res.push_back({ 2,0 });
		while (n % 2 == 0) n /= 2, res[0].second++;
	}
	for (ll i = 3; i * i <= n; i += 2) {
		if (n % i == 0) {
			res.push_back({ i, 0 });
			int idx = (int)res.size() - 1;
			while (n % i == 0) n /= i, res[idx].second++;
		}
	}
	if (n > 1) res.push_back({ n, 1 });
	return res;
}

// END Generated output of: number-theory/prime_factorize

// START Generated output of: number-theory/prime_exponentiation_table
vector<vector<ll>> prime_exponentiation_table(ll mx, vector<ll>& primes) { // stops at mx
	vector<vector<ll>> mul(primes.size());
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

// END Generated output of: number-theory/prime_exponentiation_table



ll get_lowest_prime_factor(ll n, const vector<ll>& P)
{
	for (int i = 0; i < P.size() && P[i] <= n; i++)
	{
		if (n % P[i] == 0) return P[i];
	}
	return n;
}

void solve()
{
	ll n;
	cin >> n;
	vector<ll> P;
	sieve(sqrt(n), P);
	vector<vector<ll>> mul = prime_exponentiation_table(ll(1e9), P);
	
	vector<pair<ll,ll>> pf = prime_factorize(n, P, mul);
	if (pf.size() == 2 && pf[0].sc == 1 && pf[1].sc == 1)
	{
		cout << pf[0].fs << ' ' << pf[1].fs << ' ' << n << endl;
		cout << 1 << endl;
	}
	else
	{
		vector<ll> F;
		for(int i = 2; i < sqrt(n) + 1; i++)
		{
			if (n % i == 0)
			{
				F.pb(i);
				if (i != (ll)sqrt(n)) F.pb(n / i);
			}
		}

		map<ll, vector<ll>> mp;
		for(int i = 0; i < F.size(); i++)
		{
			ll p = get_lowest_prime_factor(F[i], P);
			if (!mp.count(p)) mp[p] = vector<ll>();
			mp[p].pb(F[i]);
		}


		ll m = pf.size();
		set<ll> U;
		for(int i = 0; i < m; i++)
		{
			cout << pf[i].fs << ' ';
			U.insert(pf[i].fs);
			if (i < m - 1) U.insert(pf[i].fs * pf[i + 1].fs);
			for (auto v : mp[pf[i].fs])
			{
				if (!U.count(v))
					cout << v << ' ';
				U.insert(v);
			}
			if (i < m - 1) cout << pf[i].fs * pf[i + 1].fs << ' ';
		}
		if (!U.count(n)) cout << n << ' ';
		cout << endl << 0 << endl;
	}
}


signed main() {
	cin.sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	ll t;
	cin >> t;
	while(t--)
		solve();
	return 0;
}
