#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
#define rep(i,a,b) for(ll i = (a); i < (b); ++i)
#define rrep(i,a,b) for(ll i = (a); i > b; --i)
#define iter(it,c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define pb push_back
#define fs first
#define sc second
#define MOD 1000000007ll
#define MOD2 998244353
#define INF 1000000000000000000ll
#pragma GCC optimize("Ofast")
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
template <class T> T smod(T a, T b) {
	return (a % b + b) % b;
}
 
ll pw(ll a, ll b)
{
	ll res = 1;
	while (b) {
		if (b & 1) res *= a;
		b /= 2;
		a *= a;
	}
	return res;
}
 
vector<ll> sieve(ll n)
{
	vector<int> cnt(n + 1);
	for (int i = 2; i <= n; i++)
	{
		for (int j = i; j <= n; j += i)
		{
			cnt[j]++;
		}
	}
	vi P;
	for (int i = 2; i <= n; i++) if (cnt[i] == 1) P.pb(i);
	return P;
}
const int mxa = 1e7; 
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

void solve()
{
	ll n;
	cin >> n;
	ll sq = sqrt(mxa) + 1;
	vi P = sieve(sq);
	vector<vi> mul = prime_exponentiation_table(mxa, P);
	vi ans1, ans2;
	for (int q = 0; q < n; q++) {
		ll a;
		cin >> a;
		vii pf = prime_factorize(a, P, mul);
		if (pf.size() == 1) {
			ans1.pb(-1), ans2.pb(-1);
			continue;
		}
 
		ll res1 = 1, res2 = 1;
		for (int j = 0; j < pf[0].sc; j++)
			res1 *= pf[0].fs;
 
		res2 = a / res1;
 
		ans1.pb(res1), ans2.pb(res2);
	}
	for (int i = 0; i < n; i++) cout << ans1[i] << ' '; cout << endl;
	for (int i = 0; i < n; i++) cout << ans2[i] << ' '; cout << endl;
}
 
signed main() {
	cin.sync_with_stdio(false); cin.tie(nullptr);
	/*ll t;
	cin >> t;
	rep(i, 0, t)*/
		solve();
	return 0;
}
