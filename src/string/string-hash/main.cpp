%include<number-theory/mod>%

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
		int pinv = mpow(P, MOD - 2, MOD);
		inv[0] = 1;
		for (int i = 1; i < max_length; i++)
			inv[i] = mmul(inv[i - 1], pinv, MOD); 
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
