/*
    https://codeforces.com/contest/1279/problem/D
*/
#include <bits/stdc++.h>
using namespace std;
#define printl(x, y) for (auto z = x.begin(); z != x.end(); z++) cout << *z << (z == x.end()-1 ? "\n" : y)
#define nextpow2(x) __builtin_popcount(x) == 1 ? x : (1 << (32-__builtin_clz(x)))
#define read(x, y) for (int i = 0; i < y; i++) cin >> x[i]
#define mkunique(x) x.resize(unique(all(x))-x.begin())
#define debug(x) cerr << #x << " : " << x << endl
#define print(x) cout << x << endl
#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()

template<int MOD>
class modint {
    int value;
public:
    modint() : value(0) {}
    modint(int value) {
        if (value <= -MOD || value >= MOD) value %= MOD;
        if (value < 0) value += MOD;
        this->value = value;
    }
    explicit operator int() const { return value; }
    friend bool operator<(const modint& x, const modint& y) { return x.value < y.value; }
    friend bool operator<=(const modint& x, const modint& y) { return x.value <= y.value; }
    friend bool operator>(const modint& x, const modint& y) { return x.value > y.value; }
    friend bool operator>=(const modint& x, const modint& y) { return x.value >= y.value; }
    friend bool operator==(const modint& x, const modint& y) { return x.value == y.value; }
    friend bool operator!=(const modint& x, const modint& y) { return !(x == y); }
    modint& operator+=(const modint& x) {
        value += x.value;
        if (value >= MOD) value -= MOD;
        return *this;
    }
    modint& operator-=(const modint& x) {
        value -= x.value;
        if (value < 0) value += MOD;
        return *this;
    }
    modint& operator*=(const modint& x) {
        value = ((int64_t)value*x.value)%MOD;
        return *this;
    }
    modint& operator/=(const modint& x) { return *this *= inv(x); }
    modint pow(modint x, int y) {
        assert(y >= 0);
        modint ans = 1;
        while (y >= 1) {
            if (y%2) ans *= x;
            y /= 2, x *= x;
        }
        return ans;
    }
    modint inv(const modint& x) {
        assert(x.value != 0);
        return pow(x, MOD-2);
    }
    modint operator-() const { return modint(-value); }
    modint& operator++() { return *this += 1; }
    modint& operator--() { return *this -= 1; }
    friend modint operator+(modint x, const modint& y) { return x += y; }
    friend modint operator-(modint x, const modint& y) { return x -= y; }
    friend modint operator*(modint x, const modint& y) { return x *= y; }
    friend modint operator/(modint x, const modint& y) { return x /= y; }
};
typedef modint<998244353> mint;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> A(n);
    for (int i = 0; i < n; i++) {
        int m; cin >> m;
        A[i].resize(m);
        for (int j = 0; j < m; j++) {
            cin >> A[i][j];
        }
    }
    map<int, int> count;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < len(A[i]); j++) {
            count[A[i][j]]++;
        }
    }
    mint p = 0;
    for (int i = 0; i < n; i++) {
        mint k = len(A[i]);
        mint sum = 0;
        for (int j = 0; j < len(A[i]); j++) {
            sum += mint(count[A[i][j]])/k;
        }
        sum /= n;
        p += sum;
    }
    p /= n;
    print(int(p));

	return 0;
}
