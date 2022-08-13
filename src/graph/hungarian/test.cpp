// https://codeforces.com/gym/103466/problem/J
#include <sstream>

#include "bits/stdc++.h"
using namespace std;
// shortcuts
#define pb push_back
#define fs first
#define sc second
#define mkp make_pair
#define all(_v) _v.begin(), _v.end()
#define ll long long
#define fun(ret, x, ...)        \
  function<ret(__VA_ARGS__)> x; \
  x = [&](__VA_ARGS__) -> ret
#define Void(x, ...) fun(void, x, __VA_ARGS__)
// reading
#define multitest \
  signed __T;     \
  cin >> __T;     \
  while (__T--)
template <typename T>
void _read(T& t);
template <typename T>
void _read(vector<T>& v);
template <typename T1, typename T2>
void _read(pair<T1, T2>& p);
template <typename T>
void _read(T& t) {
  cin >> t;
}
template <typename T>
void _read(vector<T>& v) {
  for (unsigned _i = 0; _i < v.size(); _i++) _read(v[_i]);
}
template <typename T1, typename T2>
void _read(pair<T1, T2>& p) {
  _read(p.first);
  _read(p.second);
}
void _masterread() {}
template <typename T, typename... V>
void _masterread(T& t, V&... v) {
  _read(t);
  _masterread(v...);
}
#define re(...) _masterread(__VA_ARGS__)
// writing
stringstream _effout;
#ifdef __local__
#define _stout cout
#else
#define _stout _effout
#endif
template <typename T>
void _print(T t);
template <typename T>
void _print(vector<T>& v);
template <typename T1, typename T2>
void _print(pair<T1, T2>& p);
template <typename T>
void _print(T t) {
  _stout << t;
}
template <typename T>
void _print(vector<T>& v) {
  for (unsigned _i = 0; _i < v.size(); _i++)
    _print(v[_i]), _stout << (_i == v.size() - 1 ? "" : " ");
}
template <typename T1, typename T2>
void _print(pair<T1, T2>& p) {
  _print(p.first);
  _stout << " ";
  _print(p.second);
}
void _masterprint() {}
template <typename T, typename... V>
void _masterprint(T t, V... v) {
  _print(t);
  if (sizeof...(v)) _stout << " ";
  _masterprint(v...);
}
#define pr(...) _masterprint(__VA_ARGS__)
#define prl(...) (_masterprint(__VA_ARGS__), _stout << '\n')
// debugging, instead of a similar implementation for each container type a
// seperate generic function could be used
template <typename T>
void _debug(T t);  // forward declaration
template <typename T1, typename T2>
void _debug(pair<T1, T2> p);
template <typename T>
void _debug(vector<T> v);
template <typename T>
void _debug(set<T> s);
template <typename T>
void _debug(unordered_set<T> s);
template <typename T>
void _debug(multiset<T> s);
template <typename T>
void _debug(unordered_multiset<T> s);
template <typename T1, typename T2>
void _debug(map<T1, T2> mp);
template <typename T1, typename T2>
void _debug(unordered_map<T1, T2> mp);
template <typename T1, typename T2>
void _debug(multimap<T1, T2> mp);
template <typename T1, typename T2>
void _debug(unordered_multimap<T1, T2> mp);  // end forward declaration
template <typename T>
void _debug(T t) {
  cerr << t;
}
template <typename T1, typename T2>
void _debug(pair<T1, T2> p) {
  cerr << "{";
  _debug(p.first);
  cerr << ", ";
  _debug(p.second);
  cerr << "}";
}
template <typename T>
void _debug(vector<T> v) {
  cerr << "(";
  for (unsigned _i = 0; _i < v.size(); _i++)
    _debug(v[_i]), cerr << (_i == v.size() - 1 ? "" : ", ");
  cerr << ")";
}
template <typename T>
void _debug(set<T> s) {
  cerr << "(";
  for (auto e = s.begin(); e != s.end();)
    _debug(*e), cerr << ((++e) == s.end() ? "" : ", ");
  cerr << ")";
}
template <typename T>
void _debug(unordered_set<T> s) {
  cerr << "(";
  for (auto e = s.begin(); e != s.end();)
    _debug(*e), cerr << ((++e) == s.end() ? "" : ", ");
  cerr << ")";
}
template <typename T>
void _debug(multiset<T> s) {
  cerr << "(";
  for (auto e = s.begin(); e != s.end();)
    _debug(*e), cerr << ((++e) == s.end() ? "" : ", ");
  cerr << ")";
}
template <typename T>
void _debug(unordered_multiset<T> s) {
  cerr << "(";
  for (auto e = s.begin(); e != s.end();)
    _debug(*e), cerr << ((++e) == s.end() ? "" : ", ");
  cerr << ")";
}
template <typename T1, typename T2>
void _debug(map<T1, T2> mp) {
  cerr << "(";
  for (auto e = mp.begin(); e != mp.end();)
    _debug(*e), cerr << ((++e) == mp.end() ? "" : ", ");
  cerr << ")";
}
template <typename T1, typename T2>
void _debug(unordered_map<T1, T2> mp) {
  cerr << "(";
  for (auto e = mp.begin(); e != mp.end();)
    _debug(*e), cerr << ((++e) == mp.end() ? "" : ", ");
  cerr << ")";
}
template <typename T1, typename T2>
void _debug(multimap<T1, T2> mp) {
  cerr << "(";
  for (auto e = mp.begin(); e != mp.end();)
    _debug(*e), cerr << ((++e) == mp.end() ? "" : ", ");
  cerr << ")";
}
template <typename T1, typename T2>
void _debug(unordered_multimap<T1, T2> mp) {
  cerr << "(";
  for (auto e = mp.begin(); e != mp.end();)
    _debug(*e), cerr << ((++e) == mp.end() ? "" : ", ");
  cerr << ")";
}
void _masterdebug() { cerr << "]" << endl; }
template <typename T, typename... V>
void _masterdebug(T t, V... v) {
  _debug(t);
  if (sizeof...(v)) cerr << ", ";
  _masterdebug(v...);
}
#define debug(...) \
  (cerr << "[" << #__VA_ARGS__ << "] = [", _masterdebug(__VA_ARGS__))
template <typename T>
void _debugall(T c, string n) {
  _debug("debugall: ");
  _debug(n);
  cerr << endl;
  for (auto _e : c) {
    _debug("  ");
    _debug(_e);
    cerr << endl;
  }
}  // 2d vectors and similar
#define debugall(c) (_debugall(c, #c))  // 2d vectors and similar

// asthor
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define iter(it, c) \
  for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

// main
void _solve();
void _test();
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  pr(setprecision(10));
  pr(fixed);
  _solve();
#ifndef __local__
  cout << _effout.str();
#endif
}

#define int long long
#define _mt_ 0
void _solve() {
  if (_mt_) {
    multitest _test();
  } else {
    _test();
  }
}

/*
for every i, expected gain (times n) is p_i * k_i where k_i is the number of
teams that are >= a_i

For every pair we can sum up up the reputations of all the teams they would beat


if I iterate through Amy's teams in increasing order, and I can guarantee that I
can make k_i teams


*/
// implementation is from: http://zafar.cc/2017/7/19/hungarian-algorithm/
int hungarian(vector<vector<int>>& A, int n) {
  int m = n;
  int INF = 1e18;
  // Given the cost matrix "vector<vector<int>> A {...};"
  // Find the maximum matching "vector<pair<int,int>>result;" with all pairs
  // As well as total cost "int C;" with the minimum assignment cost.
  vector<int> u(n + 1), v(m + 1), p(m + 1), way(m + 1);
  for (int i = 1; i <= n; ++i) {
    p[0] = i;
    int j0 = 0;
    vector<int> minv(m + 1, INF);
    vector<char> used(m + 1, false);
    do {
      used[j0] = true;
      int i0 = p[j0], delta = INF, j1;
      for (int j = 1; j <= m; ++j)
        if (!used[j]) {
          int cur = A[i0][j] - u[i0] - v[j];
          if (cur < minv[j]) minv[j] = cur, way[j] = j0;
          if (minv[j] < delta) delta = minv[j], j1 = j;
        }
      for (int j = 0; j <= m; ++j)
        if (used[j])
          u[p[j]] += delta, v[j] -= delta;
        else
          minv[j] -= delta;
      j0 = j1;
    } while (p[j0] != 0);
    do {
      int j1 = way[j0];
      p[j0] = p[j1];
      j0 = j1;
    } while (j0);
  }

  vector<pair<int, int>> result;
  for (int i = 1; i <= m; ++i) {
    result.push_back(make_pair(p[i], i));
  }

  int C = -v[0];
  return C;
}

int n;
vector<int> A, P, B, C;
vector<vector<pair<int, int>>> edge;
int get_score_of_team(int power) {
  int score = 0;
  rep(i, 0, n) if (A[i] < power) score += P[i];
  return score;
}

void _test() {
  re(n);
  A = P = B = C = vector<int>(n);
  re(A, P, B, C);
  vector<vector<int>> M(405, vector<int>(405));
  int oo = 1e8;
  rep(i, 0, n) rep(j, 0, n) {
    M[i + 1][j + 1] = oo - get_score_of_team(B[i] + C[j]);
  } /*10^8*/
  prl(n * oo - hungarian(M, n));
}