// https://www.codechef.com/problems/CHEFSHIP
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
#define pb push_back
#define fs first
#define sc second
#define mkp make_pair
#define endl '\n'

// START Generated output of: number-theory/mod
pair<ll, ll> egcd(ll a, ll b) { // returns pair {x,y} such that a * x + b * y = gcd(a,b)
	if (b == 0) return { 1, 0 };
	auto t = egcd(b, a % b);
	return {
		t.second,
		t.first - a / b * t.second
	};
}


ll mpow(ll a, ll b, ll m) { // a^b % m
	ll res = 1;
	while (b) {
		if (b & 1) res = res * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return res;
}
ll mdiv(ll a, ll b, ll m, bool isPrime) { // a / b % m where isPrime tells whether m is prime. Note: isPrime may be false even though m is prime. b and m must be coprime.
	if (isPrime) return a * mpow(b, m - 2, m) % m;
	return ((a * egcd(b, m).first % m) + m) % m;
}
ll mmul(ll a, ll b, ll m) {
	return a * b % m;
}
ll madd(ll a, ll b, ll m) {
	return (((a + b) % m) + m) % m;
}
ll msub(ll a, ll b, ll m) { // (a-b)%m
	return (((a - b) % m) + m) % m;
}

// END Generated output of: number-theory/mod

struct hash_util {
	const ll P = 1000003;
	const ll MOD = 1e9 + 7;
	vector<ll> pw, inv;
	int range;
	hash_util() {};
	hash_util(int max_length) {
		range = max_length;
		pw = vector<ll>(max_length);
		pw[0] = 1;
		for (int i = 1; i < max_length; i++)
			pw[i] = mmul(pw[i - 1], P, MOD);
		inv = vector<ll>(max_length);
		for (int i = 0; i < max_length; i++)
			inv[i] = mpow(pw[i], MOD - 2, MOD); // IMPROVE
	}
	ll ppow(int e) { // P^e
		//assert(e < range);
		return pw[e];
	}
	ll pinv(int e) { // (P^e)^-1
		//assert(e < range);
		return inv[e];
	}
	ll replace(ll hash, int index, char old, char now) {
		hash = msub(hash, mmul(old, pw[index], MOD), MOD);
		hash = madd(hash, mmul(now, pw[index], MOD), MOD);
		return hash;
	}
};

struct string_hash {
	vector<ll> hashes;
	hash_util* util;
	int m;
	string_hash(string s, hash_util* _util) {
		util = _util;
		m = util->MOD;
		int n = s.size();
		hashes = vector<ll>(n);
		hashes[0] = s[0];
		for (int i = 1; i < n; i++)
			hashes[i] = madd(hashes[i - 1], mmul(s[i], util->ppow(i), m), m);
	}
	int substr_hash(int l, int r) {
		ll range = msub(hashes[r], (l == 0 ? 0 : hashes[l - 1]), m);
		return mmul(range, util->pinv(l), m);
	}
};


hash_util* util;
void solve() {
	string s;
	cin >> s;
	int n = s.size();
	string_hash hash(s, util);
	if (n % 2 != 0) {
		cout << 0 << endl;
		return;
	}
	int ans = 0;
	for (int i = 1; i + 2 < n; i += 2) {
		int t1 = hash.substr_hash(0, i / 2);
		int t2 = hash.substr_hash(i / 2 + 1, i);
		int t3 = hash.substr_hash(i + 1, i + (n - i) / 2);
		int t4 = hash.substr_hash(i + (n - i) / 2 + 1, n - 1);
		if (t1 == t2 && t3 == t4)
			ans++;
	}
	cout << ans << endl;
}

signed main() {
	cin.sync_with_stdio(false), cin.tie(nullptr);
	util = new hash_util(1e5);
	int t;
	cin >> t;
	while (t--)
		solve();
}
