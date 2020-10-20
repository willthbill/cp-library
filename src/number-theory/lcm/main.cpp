%include<number-theory/gcd>%

ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
