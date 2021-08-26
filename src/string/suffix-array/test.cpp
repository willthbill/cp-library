//https://codeforces.com/edu/course/2/lesson/2/2/practice/contest/269103/problem/A
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
#define fs first
#define sc second
#define endl '\n'
// BEGIN code block of: string/suffix-array
// Standard message: The following is code from https://github.com/williamMBDK/cp-library but was copied from a local copy of the repository. Changes to the original source may have been done here.
// BEGIN code block of: other/counting-sort
// sorts elements in range [0,max_val]
template<class Int, class Auxiliary>
vector<pair<Int, Auxiliary>> counting_sort(vector<pair<Int, Auxiliary>> A, int max_val) {
	int n = A.size();
	vector<int> cnt(max_val + 1, 0);
	for (int i = 0; i < n; i++)
		cnt[A[i].fs + 1]++;
	for (int i = 1; i <= max_val; i++)
		cnt[i] += cnt[i - 1];
	vector<pair<Int, Auxiliary>> res(n);
	for (int i = 0; i < n; i++)
		res[cnt[A[i].fs]++] = A[i];
	return res;
}
// END code block of: other/counting-sort
vector<int> get_suffix_array(string s) {
    s += "$";
    int n = (int)s.size();
    const int alphabet = 256;
        vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    p.erase(p.begin()); // empty suffix
    return p;
}
// END code block of: string/suffix-array
void solve() {
	cin.sync_with_stdio(false), cin.tie(NULL);
	string s;
	cin >> s;
	vector<int> P = get_suffix_array(s);
    cout << s.size() << ' ';
	for (int i = 0; i < s.size(); i++)
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
