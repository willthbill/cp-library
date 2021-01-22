//https://codeforces.com/edu/course/2/lesson/2/2/practice/contest/269103/problem/A
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
#define fs first
#define sc second
#define endl '\n'

template<class Int, class Auxiliary>
vector<pair<Int, Auxiliary>> counting_sort(vector<pair<Int, Auxiliary>> A, int max_val) {
	int n = A.size();
	vector<int> cnt(n + 1, 0);
	for (int i = 0; i < n; i++)
		cnt[A[i].fs + 1]++;
	for (int i = 1; i < n; i++)
		cnt[i] += cnt[i - 1];
	vector<pair<Int, Auxiliary>> res(n);
	for (int i = 0; i < n; i++)
		res[cnt[A[i].fs]++] = A[i];
	return res;
}

template<class Container>
vector<int> suffix_array(Container s) {
	s += '$';
	int n = s.size();
	vector<int> P(n);
	for (int i = 0; i < n; ++i)
		P[i] = i;
	sort(P.begin(), P.end(), [&](int a, int b) {
		return s[a] < s[b];
		});

	// Create equivalence classes
	int j = 0;
	vector<int> eq(n);
	eq[P[0]] = j;
	for (int i = 0; i < n - 1; ++i) {
		int cur = P[i], nxt = P[i + 1];
		if (s[cur] < s[nxt])
			++j;
		eq[nxt] = j;
	}
	for (int k = 1; (1 << (k - 1)) <= n; ++k) { // Set this value to log2 n for increased speed
		// radix sort 
		vector<pair<int, int>> frst(n);
		for (int i = 0; i < n; i++) {
			frst[i] = make_pair(eq[(i + (1 << (k - 1))) % n], i);
		}
		frst = counting_sort<int, int>(frst, n);
		vector<pair<int, int>> scnd(n);
		for (int i = 0; i < n; i++)
			scnd[i] = make_pair(eq[frst[i].sc], frst[i].sc);

		scnd = counting_sort<int, int>(scnd, n);
		for (int i = 0; i < n; i++)
			P[i] = scnd[i].sc;

		// Create equivalence classes
		vector<int> oldeq = eq;
		int j = 0;
		eq = vector<int>(n);
		eq[P[0]] = j;
		for (int i = 0; i < n - 1; i++) {
			int cur = P[i], nxt = P[i + 1];
			int nxtcur = (cur + (1 << (k - 1))) % n, nxtnxt = (nxt + (1 << (k - 1))) % n;
			if (oldeq[cur] < oldeq[nxt] || (oldeq[cur] == oldeq[nxt] && oldeq[nxtcur] < oldeq[nxtnxt]))
				j++;
			eq[nxt] = j;
		}
	}
	return P;
}

void solve() {
	cin.sync_with_stdio(false), cin.tie(NULL);
	string s;
	cin >> s;

	vector<int> P = suffix_array<string>(s);
	for (int i = 0; i <= s.size(); i++)
		cout << P[i] << ' ';
}

signed main() {
	cin.sync_with_stdio(false); cin.tie(nullptr);
	/*ll t;
	cin >> t;
	rep(i, 0, t)*/
	solve();
	return 0;
}
