#pragma GCC optimize("Ofast","unroll-loops")
#pragma GCC target("avx2,fma")
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

ll mod_pow(ll b, ll e, ll m) {
    ll res = ll(1);
    while (e) {
        if (e & ll(1)) res = res * b % m;
        b = b * b % m, e >>= ll(1);
    }
    return res;
}

const double EPS = 1e-9;
const int MOD = 1e9 + 7; // CHANGE MODULO DEPENDING ON PROBLEM, it is here only because matrix exponentiation usually gets large
template <class K> bool eq(K a, K b) { return a == b; }
template <> bool eq<double>(double a, double b) {
    return abs(a - b) < EPS; }
template <class T> struct matrix {
  int rows, cols, cnt; vector<T> data;
  inline T& at(int i, int j) { return data[i * cols + j]; }
  matrix(int r, int c) : rows(r), cols(c), cnt(r * c) {
    data.assign(cnt, T(0)); }
  matrix(const matrix& other) : rows(other.rows),
    cols(other.cols), cnt(other.cnt), data(other.data) { }
  T& operator()(int i, int j) { return at(i, j); }
  matrix<T> operator +(const matrix& other) {
    matrix<T> res(*this); for(int i = 0; i < cnt; i++)
      res.data[i] += other.data[i]; return res; }
  matrix<T> operator -(const matrix& other) {
    matrix<T> res(*this); for(int i = 0; i < cnt; i++)
      res.data[i] -= other.data[i]; return res; }
  matrix<T> operator *(T other) {
    matrix<T> res(*this);
    for(int i = 0; i < cnt; i++) res.data[i] *= other; return res; }
  matrix<T> operator *(const matrix& other) {
    matrix<T> res(rows, other.cols);
    for(int i = 0; i < rows; i++) 
		for(int k = 0; k < cols; k++)
			for(int  j= 0; j < other.cols; j++)
				res(i, j) = (res(i,j) + at(i, k) * other.data[k * other.cols + j]) % MOD;
    return res; }
  matrix<T> pow(ll p) {
    matrix<T> res(rows, cols), sq(*this);
    for(int i = 0; i < rows; i++) res(i, i) = T(1);
    while (p) {
      if (p & 1) res = res * sq;
      p >>= 1;
      if (p) sq = sq * sq;
    } return res; }
  matrix<T> rref(T &det, int &rank) {
    matrix<T> mat(*this); det = T(1), rank = 0;
    for (int r = 0, c = 0; c < cols; c++) {
      int k = r;
      for(int i = k+1; i < rows; i++) if (abs(mat(i,c)) > abs(mat(k,c))) k = i;
      if (k >= rows || eq<T>(mat(k, c), T(0))) continue;
      if (k != r) {
        det *= T(-1);
		for(int i = 0; i < cols; i++) swap(mat.at(k, i), mat.at(r, i));
      } det *= mat(r, r); rank++;
      T d = mat(r,c);
      for(int i = 0; i < cols; i++) mat(r, i) /= d;
      for(int i = 0; i < rows; i++) {
        T m = mat(i, c);
        if (i != r && !eq<T>(m, T(0)))
          for(int j = 0; j < cols; j++) mat(i, j) -= m * mat(r, j);
      } r++;
    } return mat; }
  matrix<T> transpose() {
    matrix<T> res(cols, rows);
    for(int i = 0; i < rows; i++) for(int j = 0; j < cols; j++) res(j, i) = at(i, j);
    return res; } };

int main()
{
    cin.sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    ll n, l;
    cin >> n >> l;
    matrix<ll> A = matrix<ll>(n, n);
    for(int i = 0; i < n; i++)
    {
        vector<int> tmp(n);
        ll sm = 0;
        for(int j = 0; j < n; j++)
        {
            cin >> tmp[j];
            sm = sm + tmp[j];
        }
        for(int j = 0; j < n; j++)
        {
            if (sm == 0)
                A(i, j) = 0;
            else
                A(i, j) = (tmp[j] * mod_pow(sm % MOD, MOD - 2, MOD)) % MOD;
        }
    }
    A.data[n * n - 1] = 1;
    ll b = ((19ll) * mod_pow(20ll, MOD - 2, MOD)) % MOD;
    matrix<ll> B(A.pow(l));
    matrix<ll> C(1, n);
    C(0, 0) = 1ll;
    for(int k = l; k <= l + 9; k++)
    {
        matrix<ll> res = C * B;
        ll a = res(0, n - 1) % MOD;
        if (a == b)
        {
            cout << k << endl;
            return 0;
        }
        B = B * A;
    }
    cout << -1 << endl;
    return 0;
}
