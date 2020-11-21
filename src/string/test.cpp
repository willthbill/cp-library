// https://codeforces.com/edu/course/1/lesson/2/1/practice/contest/269100/problem/A
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
#define fs first
#define sc second
#define endl '\n'

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
		sort(P.begin(), P.end(), [&](int a, int b) {
			int nxta = (a + (1 << (k - 1))) % n, nxtb = (b + (1 << (k - 1))) % n;
			return eq[a] < eq[b] || (eq[a] == eq[b] && eq[nxta] < eq[nxtb]);
			});

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
	string s;
	cin >> s;
	vector<int> P = suffix_array<string>(s);
	for (int i = 0; i < P.size(); i++)
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
