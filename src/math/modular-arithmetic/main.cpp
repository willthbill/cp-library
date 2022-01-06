/*
    inspired by Benq's
    https://github.com/bqi343/USACO/blob/master/Implementations/content/number-theory%20(11.1)/Modular%20Arithmetic/ModInt.h
    
    typedef at the bottom
    remember to cast to int before output
    mint x = 1;
    cout << int(x) << endl;
*/
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
typedef modint<1000000007> mint;
