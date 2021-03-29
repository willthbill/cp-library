#include "bits/stdc++.h"
#include<sstream>
using namespace std;
// shortcuts
#define pb push_back
#define fs first
#define sc second
#define mkp make_pair
#define all(_v) _v.begin(),_v.end()
#define ll long long
#define fun(ret,x,...) function<ret(__VA_ARGS__)> x;x=[&](__VA_ARGS__)->ret
#define Void(x,...) fun(void,x,__VA_ARGS__)
// reading
#define multitest signed __T; cin >> __T; while(__T--)
template<typename T>void _read(T& t);
template<typename T>void _read(vector<T>& v);
template<typename T1, typename T2>void _read(pair<T1, T2>& p);
template<typename T>void _read(T& t) { cin >> t; }
template<typename T>void _read(vector<T>& v) { for (unsigned _i = 0; _i < v.size(); _i++)_read(v[_i]); }
template<typename T1, typename T2>void _read(pair<T1, T2>& p) { _read(p.first); _read(p.second); }
void _masterread() {}
template<typename T, typename... V>void _masterread(T& t, V& ... v) { _read(t); _masterread(v...); }
#define re(...)_masterread(__VA_ARGS__)
// writing
stringstream _effout;
#ifdef __local__
#define _stout cout
#else
#define _stout _effout
#endif
template<typename T>void _print(T t);
template<typename T>void _print(vector<T>& v);
template<typename T1, typename T2>void _print(pair<T1, T2>& p);
template<typename T>void _print(T t) { _stout << t; }
template<typename T>void _print(vector<T>& v) { for (unsigned _i = 0; _i < v.size(); _i++)_print(v[_i]), _stout << (_i == v.size() - 1 ? "" : " "); }
template<typename T1, typename T2>void _print(pair<T1, T2>& p) { _print(p.first); _stout << " "; _print(p.second); }
void _masterprint() {}
template<typename T, typename... V>void _masterprint(T t, V... v) { _print(t); if (sizeof...(v))_stout << " "; _masterprint(v...); }
#define pr(...)_masterprint(__VA_ARGS__)
#define prl(...) (_masterprint(__VA_ARGS__),_stout<<endl)
// debugging, instead of a similar implementation for each container type a seperate generic function could be used
template <typename T> void _debug(T t); //forward declaration
template<typename T1, typename T2> void _debug(pair<T1, T2> p);
template<typename T> void _debug(vector<T> v);
template<typename T> void _debug(set<T>s);
template<typename T> void _debug(unordered_set<T>s);
template<typename T> void _debug(multiset<T>s);
template<typename T> void _debug(unordered_multiset<T>s);
template<typename T1, typename T2> void _debug(map<T1, T2>mp);
template<typename T1, typename T2> void _debug(unordered_map<T1, T2>mp);
template<typename T1, typename T2> void _debug(multimap<T1, T2>mp);
template<typename T1, typename T2> void _debug(unordered_multimap<T1, T2>mp); // end forward declaration
template <typename T> void _debug(T t) { cerr << t; }
template<typename T1, typename T2> void _debug(pair<T1, T2> p) { cerr << "{"; _debug(p.first); cerr << ", "; _debug(p.second); cerr << "}"; }
template<typename T> void _debug(vector<T>v) { cerr << "("; for (unsigned _i = 0; _i < v.size(); _i++)_debug(v[_i]), cerr << (_i == v.size() - 1 ? "" : ", "); cerr << ")"; }
template<typename T> void _debug(set<T>s) { cerr << "("; for (auto e = s.begin(); e != s.end();)_debug(*e), cerr << ((++e) == s.end() ? "" : ", "); cerr << ")"; }
template<typename T> void _debug(unordered_set<T>s) { cerr << "("; for (auto e = s.begin(); e != s.end();)_debug(*e), cerr << ((++e) == s.end() ? "" : ", "); cerr << ")"; }
template<typename T> void _debug(multiset<T>s) { cerr << "("; for (auto e = s.begin(); e != s.end();)_debug(*e), cerr << ((++e) == s.end() ? "" : ", "); cerr << ")"; }
template<typename T> void _debug(unordered_multiset<T>s) { cerr << "("; for (auto e = s.begin(); e != s.end();)_debug(*e), cerr << ((++e) == s.end() ? "" : ", "); cerr << ")"; }
template<typename T1, typename T2> void _debug(map<T1, T2>mp) { cerr << "("; for (auto e = mp.begin(); e != mp.end();)_debug(*e), cerr << ((++e) == mp.end() ? "" : ", "); cerr << ")"; }
template<typename T1, typename T2> void _debug(unordered_map<T1, T2>mp) { cerr << "("; for (auto e = mp.begin(); e != mp.end();)_debug(*e), cerr << ((++e) == mp.end() ? "" : ", "); cerr << ")"; }
template<typename T1, typename T2> void _debug(multimap<T1, T2>mp) { cerr << "("; for (auto e = mp.begin(); e != mp.end();)_debug(*e), cerr << ((++e) == mp.end() ? "" : ", "); cerr << ")"; }
template<typename T1, typename T2> void _debug(unordered_multimap<T1, T2>mp) { cerr << "("; for (auto e = mp.begin(); e != mp.end();)_debug(*e), cerr << ((++e) == mp.end() ? "" : ", "); cerr << ")"; }
void _masterdebug() { cerr << "]" << endl; }
template<typename T, typename... V> void _masterdebug(T t, V... v) { _debug(t); if (sizeof...(v))cerr << ", "; _masterdebug(v...); }
#define debug(...)(cerr<<"["<<#__VA_ARGS__<<"] = [",_masterdebug(__VA_ARGS__))
template<typename T> void _debugall(T c, string n) { _debug("debugall: "); _debug(n); cerr << endl; for (auto _e : c) { _debug("  "); _debug(_e); cerr << endl; } } //2d vectors and similar
#define debugall(c)(_debugall(c,#c)) //2d vectors and similar

#define int long long
#define double long double																																								
// main
void _solve();
void _test();
signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cout << setprecision(10);
	cout << fixed;
	_solve();
#ifndef __local__
	cout << _effout.str();
#endif
}

#define _mt_ 0
void _solve() {
	if (_mt_) {
		int t; cin >> t; for (int i = 1; i <= t; i++) _test();
	}
	else {
		_test();
	}
}

int n;
pair<int, int> a, b;
set<pair<int, int>> moves;
bool isPossible(pair<int, int> from, int i, int j) {
	if (from == mkp(i, j)) return true;
	for (auto move : moves) {
		pair<int, int> cur = { from.fs + move.fs, from.sc + move.sc };
		if (min(cur.fs, cur.sc) < 1 || max(cur.fs, cur.sc) > n) {
			continue;
		}
		pair<int, int> find = { i - cur.fs, j - cur.sc };
		if (find == mkp(0ll, 0ll)) {
			return true;
		}
		//debug(cur, find);
		if (moves.count(find)) {
			return true;
		}
	}
	return false;
}

struct randint {
	random_device device;
	mt19937 generator;
	uniform_int_distribution<int> distribution;
	randint(int l, int r) {
		generator = mt19937(device());
		distribution = uniform_int_distribution<int>(l, r);
	}
	int get() {
		return distribution(generator);
	}
};


void _test() {
	re(n, a, b);
	moves = set<pair<int, int>>();
	randint rand(1, n);
	for (int i = 0; i < n; i++) {
		int x, y; re(x, y);
		moves.insert({ x, y });
	}

	if (isPossible(a, b.fs, b.sc)) {
		pr("Alice wins");
		return;
	}
	if (n > 3) {
		while (true) {
			int i = rand.get(), j = rand.get();
			if (!isPossible(b, i, j)) {
				prl("tie", i, j);
				return;
			}
		}
	}
	else {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (!isPossible(b, i, j)) {
					prl("tie", i, j);
					return;
				}
			}
		}
		prl("Bob wins");
	}
}
