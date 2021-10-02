#include <bits/stdc++.h>
using namespace std;
#define printl(x, y) for (auto z = x.begin(); z != x.end(); z++) cout << *z << (z == x.end()-1 ? "\n" : y)
#define nextpow2(x) __builtin_popcount(x) == 1 ? x : (1 << (32-__builtin_clz(x)))
#define read(x, y) for (int i = 0; i < y; i++) cin >> x[i]
#define debug(x) cerr << #x << " : " << x << endl
#define print(x) cout << x << endl
#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()

typedef vector<vector<int64_t>> Matrix;
typedef vector<vector<long double>> RealMatrix;
typedef vector<int> Big;

bool geq(Big& a, Big& b) {
    /*
        a >= b
        digits in vectors
        Time: n, where n is # of digits
    */
    if (len(a) != len(b)) return len(a) > len(b);
    for (int i = len(a)-1; i >= 0; i--) {
        if (a[i] != b[i]) return a[i] > b[i];
    }
    return true;
}

bool le(Big& a, Big& b) {
    /*
        a < b
        digits in vectors
        Time: n, where n is # of digits
    */
    if (len(a) != len(b)) return len(a) < len(b);
    for (int i = len(a)-1; i >= 0; i--) {
        if (a[i] != b[i]) return a[i] < b[i];
    }
    return false;
}

Big add(Big a, Big b) {
    /*
        addition of large numbers
        digits in vectors
        Time: n, where n is # of digits
    */
    int carry = 0;
    Big result;
    if (len(b) < len(a)) swap(a, b);
    while (len(a) < len(b)) a.push_back(0);
    for (int i = 0; i < len(a); i++) {
        int x = a[i]+b[i]+carry;
        result.push_back(x%10);
        x /= 10;
        carry = x;
    }
    if (carry) result.push_back(carry);
    return result;
}

Big sub(Big a, Big b) {
    /*
        subtraction of large numbers
        digits in vectors
        Time: n, where n is # of digits
    */
    if (le(a, b)) {
        print("subtraction result in negative");
        exit(0);
    }
    int carry = 0;
    Big result;
    while (len(b) < len(a)) b.push_back(0);
    for (int i = 0; i < len(a); i++) {
        int x = a[i]-b[i]-carry;
        if (x < 0) carry = 1, x += 10;
        else carry = 0;
        result.push_back(x%10);
        x /= 10;
    }
    if (carry) result.push_back(carry);
    while (*result.rbegin() == 0 && len(result) > 1) result.pop_back();
    return result;
}

Big mult(Big a, Big b) {
    /*
        multiplication of large numbers
        digits in vectors
        Time: n^2, where n is # of digits
    */
    Big v(len(a)+len(b), 0);
    int l = 0, r = 0;
    if (len(b) < len(a)) swap(a, b);
    for (int i = 0; i < len(a); i++) {
        int carry = 0, d1 = a[i];
        r = 0;
        for (int j = 0; j < len(b); j++) {
            int d2 = b[j];
            int sum = d1*d2+v[i+j]+carry;
            carry = sum/10;
            v[i+j] = sum%10;
            r++;
        }
        if (carry) v[i+len(b)] += carry;
        l++;
    }
    while (*v.rbegin() == 0 && len(v) > 1) v.pop_back();
    return v;
}

Big modulo(Big a, Big b) {
    /*
        a%b
        digits in vectors
        Time: n^3, where n is # of digits
    */
    if (len(b) == 1 && !b[0]) {
        print("division with 0");
        exit(0);
    }
    if (geq(b, a)) {
        if (le(a, b)) return a;
        return {0};
    }
    int i = len(a)-1;
    Big R = {a[i--]};
    while(true){
        Big A = R;
        while(le(A, b) && i >= 0) A = add(mult(A, {0, 1}), {a[i--]});
        while(geq(A, b)) A = sub(A, b);
        R = A;
        if(i < 0) break;
    }
    return R;
}

Big int64_to_big(int64_t x) {
    /*
        Converts an int64_t to a vector containing digits
        Time: log(x)
    */
    if (x == 0) return {0};
    if (x < 0) {
        print("can not convert negative number");
        exit(0);
    }
    Big big;
    while (x) {
        big.push_back(x%10);
        x /= 10;
    }
    return big;
}

int64_t big_to_int64(Big v) {
    /*
        Converts a vector of digits to an int64_t
        Time: n, where n is # of digits
    */
   int64_t ans = 0, x = 1;
   for (int i = 0; i < len(v); i++) {
       ans += x*v[i];
       x *= 10;
   }
   return ans;
}

int64_t josephus(int64_t n, int64_t k) {
    /*
        Circle of n, every 2nd is removed
        return index of kth to be removed
        Time: log(n)
    */
    if (n == 1) return 1;
    if (k <= (n+1)/2) return k*2 > n ? (k*2)%n : k*2;
    if (n%2 == 0) return josephus(n/2, k-(n+1)/2)*2-1;
    else return josephus(n/2, k-(n+1)/2)*2+1;
}

int64_t lcm(int64_t a, int64_t b) { /* LCM(a, b) | Time: log(max(a, b)) */ return a*b/__gcd(a, b); }

tuple<int64_t, int64_t> extended_gcd(int64_t a, int64_t b) {
    /*
        Solution to ax + by = c, where gcd(a, b) | c
        Time: log(a+b)
    */
    if (b == 0) return {1, 0};
    tuple<int64_t, int64_t> t = extended_gcd(b, a%b);
    return {get<1>(t), get<0>(t)-a/b*get<1>(t)};
}

uint64_t fast_exp(uint64_t a, uint64_t b, uint64_t m) {
    /*
        Computes pow(a, b)%m
        Time: log(b)
    */
    uint64_t ans = 1;
    while (b >= 1) {
        if (b%2) ans = ans*a%m;
        b /= 2;
        a = a*a%m;
    }
    return ans;
}

int64_t inv(int64_t x, int64_t m) { /* Inverse of x mod m | Time: log(m) */ return fast_exp(x, m-2, m); }

int64_t chinese_remainder_theorem(vector<int64_t>& A, vector<int64_t>& M) {
    /*
        Solves for x in the system of congruence
        x = A[0]   (mod M[0])
        ...
        x = A[n-1] (mod M[n-1])
        if x is solution
        then x+M[0]*M[1]...M[n-1] is a solution
        Time: n*log(m), where m is the maximum mod
    */
    int n = len(A);
    int64_t mod = 1, solution = 0;
    for (int i = 0; i < n; i++) mod *= M[i];
    for (int i = 0; i < n; i++) {
        int64_t x = mod/M[i];
        int64_t inverse = get<0>(extended_gcd(x%M[i], M[i]));
        solution += (A[i]*x%mod)*(inverse+mod)%mod;
        solution %= mod;
    }
    return solution;
}

int64_t big_crt(vector<int64_t>& A, vector<int64_t>& M) {
    /*
        crt for input >= 1e9
        Time: Time: n*(time for Big)
    */
    int n = len(A);
    int64_t mod = 1, solution = 0;
    for (int i = 0; i < n; i++) mod *= M[i];
    for (int i = 0; i < n; i++) {
        int64_t x = mod/M[i];
        int64_t inverse = get<0>(extended_gcd(x%M[i], M[i]));
        Big big = modulo(mult(int64_to_big(A[i]), int64_to_big(x)), int64_to_big(mod));
        big = modulo(mult(big, int64_to_big(inverse+mod)), int64_to_big(mod));
        solution += big_to_int64(big);
        solution %= mod;
    }
    return solution;
}

int64_t generel_crt(int64_t a, int64_t b, int64_t n, int64_t m) {
    /*
        Gives solution for a system of 2 congruences
        returns -1 if no solution
        Time: log(n+m)
    */
    if ((a-b)%__gcd(n, m) != 0) return -1;
    int64_t x = get<0>(extended_gcd(n, m));
    int64_t ans = ((b-a)/__gcd(n, m)+n*m)*(x+n*m)*n+a;
    return ans%lcm(n, m);
}

int64_t generel_crt(vector<int64_t>& A, vector<int64_t>& M) {
    /*
        Generel crt, non-relatively prime moduli
        returns -1 if no solution
        Time: n*log(m), where m is the maximum mod
    */
    int n = len(A);
    int64_t mod = M[0], ans = A[0];
    for (int i = 1; i < n; i++) {
        ans = generel_crt(ans, A[i], mod, M[i]);
        if (ans == -1) return ans;
        mod = lcm(mod, M[i]);
    }
    return ans;
}

int64_t big_generel_crt(int64_t a, int64_t b, int64_t n, int64_t m) {
    /*
        values >= 1e9
        Gives solution for a system of 2 congruences
        returns -1 if no solution
        Time: log(n+m)
    */
    if ((a-b)%__gcd(n, m) != 0) return -1;
    int64_t x = get<0>(extended_gcd(n, m));
    Big big = add(mult(mult(int64_to_big((b-a)/__gcd(n, m)+n*m), int64_to_big(x+n*m)), int64_to_big(n)), int64_to_big(a));
    big = modulo(big, int64_to_big(lcm(n, m)));
    int64_t ans = big_to_int64(big);
    return ans;
}

int64_t big_generel_crt(vector<int64_t>& A, vector<int64_t>& M) {
    /*
        values >= 1e9
        Generel crt, non-relatively prime moduli
        returns -1 if no solution
        Time: n*log(m), where m is the maximum mod
    */
    int n = len(A);
    int64_t mod = M[0], ans = A[0];
    for (int i = 1; i < n; i++) {
        ans = big_generel_crt(ans, A[i], mod, M[i]);
        if (ans == -1) return ans;
        mod = lcm(mod, M[i]);
    }
    return ans;
}

int64_t nck(int64_t a, int64_t b, int64_t m, vector<int64_t>& fact) {
    /*
        Computes the binomial coefficient a choose b mod m
        Note: n choose k with duplicates is n+k-1 choose k
        Time: log(m)
    */
    return fact[a]*inv(fact[b]*fact[a-b]%m, m)%m;
}

int64_t npk(int64_t a, int64_t b, int64_t m, vector<int64_t>& fact) {
    /*
        Compute a permutes b
        Time: log(m)
    */
    return fact[a]*inv(fact[a-b], m)%m;
}

int64_t derangements(int n, int64_t m) {
    /*
        Computes the number of derangements mod m
        Permutations where a[i] != i
        Time: n
    */
    int64_t ans = 1;
    for (int i = 1; i <= n; i++) {
        ans = ans*i%n+(i%2 ? -1 : 1);
    }
    return ans;
}

int64_t catalan(int n, int64_t m, vector<int64_t>& fact) {
    /*
        Computes the nth catalan number
        Time: log(m)
    */
    return nck(2*n, n, m, fact)*inv(n+1, m)%m;
}

int64_t grid_path_cnt(int n, int x, int y, int64_t m, vector<int64_t>& fact) {
    /*
        Computes the number of paths from (x, y) to (n, n)
        without crossing the diagonal (0, 0) -> (n, n)
        Time: log(m)
    */
    int64_t ans = nck(2*n-(x+y), n-x, m, fact);
    ans -= nck(2*n-(x+y), n-x-1, m, fact);
    ans = (ans+m)%m;
    return ans;
}

int64_t burnside_necklace(int n, int k, int64_t m) {
    /*
        n pearls and k colors
        necklace are the same if rotation makes them similar
        Time: n*log(n)
    */
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans+(fast_exp(k, __gcd(i, n), m))*inv(n, m)%m)%m;
    }
    return ans;
}

int64_t burnside_grid(int n, int64_t m) {
    /*
        n by n grid and 2 colors
        grids are the same if rotation makes them similar
        Time: log(m)
    */
    int64_t ans = 0;
    if (n < 3) return n == 1 ? 2 : 6;
    int64_t N = n/2;
    int64_t chain_cnt = (n%2 ? N*(N+1) : N*N)%(m-1);
    for (int i = 0; i < 4; i++) {
        int64_t ck = fast_exp(fast_exp(2, __gcd(i, 4), m), chain_cnt, m);
        ck = ck*(n%2 ? 2 : 1)%m;
        ans = (ans+ck*inv(4, m)%m)%m;
    }
    return ans;
}

vector<int64_t> fact_table(int n, int64_t m) {
    /*
        Computes a factorial table where fact[n] = n! mod m
        Time: n
    */
    vector<int64_t> fact(n+1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i-1]*i%m;
    return fact;
}

map<int, int> factorize(int n) {
    /*
        Factorizes n into its prime divisors
        Time: sqrt(n)
    */
    map<int, int> mp;
    vector<int> factors;
    for (int x = 2; x*x <= n; x++) {
        while (n%x == 0) {
            factors.push_back(x);
            n /= x;
        }
    }
    if (n > 1) factors.push_back(n);
    for (auto x : factors) mp[x]++;
    return mp;
}

int64_t divisor_cnt(int n) {
    /*
        Computes the number of divisors of n
        Time: m, where m is the number of unique prime factors
    */
    int cnt = 1;
    map<int, int> factors = factorize(n);
    for (auto p : factors) cnt *= p.second+1;
    return cnt;
}

vector<int> compute_divisors(int n) {
    /*
        Computes the divisors of n
        Time: sqrt(n)
    */
    vector<int> A;
    for (int i = 1; i*i <= n; i++) {
        if (n%i == 0) {
            if (i*i != n) A.push_back(n/i);
            A.push_back(i);
        }
    }
    return A;
}

int divisor_sum(int n) {
    /*
        Computes the sum of divisors of n
        Time: sqrt(n)
    */
    int sum = 0;
    for (int i = 1; i*i <= n; i++) {
        sum += n%i ? 0 : i*i == n ? i : i+n/i;
    }
    return sum;
}

int64_t divisor_product(int n, int64_t m) {
    /*
        Computes the product of divisors of n mod m
        Time: sqrt(n)
    */
    int64_t sum = 1;
    for (int i = 1; i*i <= n; i++) {
        if (n%i == 0) {
            if (i*i != n) sum *= n/i, sum %= m;
            sum *= i;
            sum %= m;
        }
    }
    return sum;
}

tuple<int64_t, int64_t, int64_t> divisor_cnt_sum_product(map<int64_t, int64_t> factors, int64_t m) {
    /*
        Given prime factorization compute the number, sum and product of divisors
        Time: k*log(m), where k is the number of unique prime factors
    */
    int64_t different_mod = 1, factor_cnt = 1, sum = 1, product = 1;
    for (auto p : factors) {
        factor_cnt = factor_cnt*(p.second+1)%m;
        product = fast_exp(product, p.second+1, m)*fast_exp(fast_exp(p.first, (p.second*(p.second+1)/2), m), different_mod, m)%m;
        different_mod = different_mod*(p.second+1)%(m-1);
    }
    for (auto p : factors) sum = sum*(fast_exp(p.first, p.second+1, m)-1)*inv(p.first-1, m)%m;
    return {factor_cnt, sum, product};
}

vector<int> compute_sieve(int n) {
    /*
        Sieve algorithm
        Time: n*log(log(n))
    */
    vector<int> sieve(n, 0);
    for (int x = 2; x <= n; x++) {
        if (sieve[x]) continue;
        for (int i = x*2; i <= n; i += x) {
            sieve[i] = x;
        }
    }
    return sieve;
}

int mobius(int n) {
    /*
        mobius(1) = 1
        mobius(n) = 0 if p^2 | n for some prime p
        mobius(n) = (-1)^r if n = p1p2...pr and all pi are distinct primes
        Time: sqrt(n)
    */
    if (n == 1) return 1;
    int cnt = 0;
    for (int x = 2; x*x <= n; x++) {
        if (n%x == 0) {
            cnt++;
            n /= x;
            if (n%x == 0) return 0;
        }
    }
    return cnt%2 ? 1 : -1;
}

int euler_phi(int n) {
    /*
        Computes euler phi for a single number
        phi(n) = n*(product for all p divides n(1-1/p))
        time: sqrt(n)
    */
    int cnt = n;
    for (int x = 2; x*x <= n; x++) {
        if (n%x == 0) {
            while (n%x == 0) n /= x;
            cnt -= cnt/x;
        }
    }
    if (n > 1) cnt -= cnt/n;
    return cnt;
}

vector<int> euler_phi_table(int n) {
    /*
        Computes euler phi for all numbers 1 to n
        Time: n*log(log(n))
    */
    vector<int> phi(n+1, 0);
    phi[1] = 1;
    for (int i = 2; i <= n; i++) phi[i] = i;
    for (int x = 2; x <= n; x++) {
        if (phi[x] != x) continue;
        for (int i = x; i <= n; i += x) {
            phi[i] -= phi[i]/x;
        }
    }
    return phi;
}

bool real_compare(long double a, long double b) {
    /*
        a == b
        Time: 1
    */
    long double epsilon = 0.0000000001;
    return abs(a-b) < epsilon;
}

Matrix mult(Matrix a, Matrix b, int64_t m) {
    /*
        Computes a*b%m
        Time: n^3
    */
    Matrix A = Matrix(len(a), vector<int64_t>(len(b[0])));
    for (int i = 0; i < len(a); i++) {
        for (int j = 0; j < len(b[0]); j++) {
            for (int k = 0; k < len(b); k++) {
                A[i][j] += a[i][k]*b[k][j]%m;
                A[i][j] %= m;
            }
        }
    }
    return A;
}

Matrix fast_exp(Matrix a, int64_t b, int64_t m, map<int64_t, Matrix>& dp) {
    /*
        Computes a^b%m
        Time: log(b)
    */
    if (dp.count(b)) return dp[b];
    if (b == 1) return a;
    if (b%2) return dp[b] = mult(mult(fast_exp(a, b/2, m, dp), fast_exp(a, b/2, m, dp), m), a, m);
    return dp[b] = mult(fast_exp(a, b/2, m, dp), fast_exp(a, b/2, m, dp), m);
}

Matrix min_path_step(Matrix a, Matrix b) {
    /*
        Utility for min_path_length_k
        Time: n^3
    */
    Matrix A = Matrix(len(a), vector<int64_t>(len(b[0])));
    for (int i = 0; i < len(a); i++) {
        for (int j = 0; j < len(b[0]); j++) {
            for (int k = 0; k < len(b); k++) {
                A[i][j] = min(A[i][j], a[i][k]+b[k][j]);
            }
        }
    }
    return A;
}

Matrix min_path_length_k(Matrix a, int64_t k, map<int64_t, Matrix>& dp) {
    /*
        Computes shortest weighted path of length k
        Time: log(k)*n^3
    */
    if (dp.count(k)) return dp[k];
    if (k == 1) return a;
    if (k%2) return dp[k] = min_path_step(min_path_step(min_path_length_k(a, k/2, dp), min_path_length_k(a, k/2, dp)), a);
    return dp[k] = min_path_step(min_path_length_k(a, k/2, dp), min_path_length_k(a, k/2, dp));
}

void row_add(RealMatrix& A, int a, int b, long double x) {
    /*
        add row b*x to row a
        Time: n
    */
    for (int i = 0; i < len(A[0]); i++) {
        A[a][i] += A[b][i]*x;
    }
}

void row_mult(RealMatrix& A, int row, long double x) {
    /*
        multiply x to row
        Time: n
    */
    for (int i = 0; i < len(A[row]); i++) {
        A[row][i] *= x;
    }
}

void row_swap(RealMatrix& A, int a, int b) { /* swap row a with row b | Time: 1 */ swap(A[a], A[b]); }

RealMatrix reduced_row_echelon_form(RealMatrix M) {
    /*
        Computes the reduced row echelon form of M
        Time: n^2
    */
    RealMatrix A = M;
    int mn_col = 0, n = len(A), m = len(A[0])-1;
    for (int mn_row = 0; mn_row < n; mn_row++) {
        tuple<int, int> found = {-1, -1};
        for (int col = mn_col; col < m && get<0>(found) == -1; col++) {
            for (int row = mn_row; row < n && get<0>(found) == -1; row++) {
                if (!real_compare(A[row][col], 0)) {
                    found = {row, col};
                }
            }
        }
        mn_col = get<1>(found);
        if (mn_col == -1) break;
        row_swap(A, mn_row, get<0>(found));
        row_mult(A, mn_row, 1/A[mn_row][mn_col]);
        for (int row = mn_row+1; row < n; row++) {
            row_add(A, row, mn_row, -A[row][mn_col]);
        }
        mn_col++;
    }
    for (int col = m-1; col >= 0; col--) {
        int found = -1;
        for (int row = n-1; row >= 0; row--) {
            if (found != -1) {
                row_add(A, row, found, -A[row][col]);
            } else if (real_compare(A[row][col], 1)) {
                found = row;
            }
        }
    }
    return A;
}

long double probability_max(int64_t x, int64_t n, int64_t k) {
    /*
        Probability of x being max value
        if n values are randomly given from 1 to k
        Time: log(n) if C++ loves you
    */
    return powl(x/(long double)k, n)-powl((x-1)/(long double)k, n);
}

long double bionomial_distribution(int64_t n, long double p, int64_t x, vector<int64_t>& fact) {
    /*
        n attempt are made
        probability of a single attempt succeeding is p
        computes the probability that x attempts succeeds
        BEWARE if nck(n, x) >= 1e9+7
        Time: log(m) if C++ loves you
    */
    const int64_t m = 1e9+7;
    return powl(p, x)*powl(1-p, n-x)*nck(n, x, m, fact);
}

long double geometric_distribution(long double p, int64_t x) {
    /*
        The probability of an attemp succeeding is p
        Computes the probability that the first successful attempt
        is the xth attempt
        Time: log(x) if C++ loves you
    */
   return powl(1-p, x-1)*p;
}

bool miller_rabin(uint64_t n) {
    /*
        Test if n is prime
        works for n < 4.759.123.141
        Time: less than log(n)^4
    */
    if (n < 2) return false;
    for (uint64_t x : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}) {
        if (n%x == 0) return n == x;
    }
    int r = __builtin_ctz(n-1);
    uint64_t d = (n-1) >> r;
    // for 2^64 -> {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}
    for (uint64_t a : {2, 7, 61}) {
        uint64_t x = fast_exp(a%n, d, n);
        if (x <= 1 || x == n-1) continue;
        for (int i = 0; i < r-1 && x != n-1; i++) x = x*x%n;
        if (x != n-1) return false;
    }
    return true;
}

uint64_t next_prime(uint64_t n) {
    /*
        Finds the next prime or n if n is prime
        Time: ~2.3*log10(n)*(time for miller_rabin(n))
    */
    while (!miller_rabin(n)) n++;
    return n;
}

long double harmonic_number(int64_t n) {
    /*
        Approximates the nth harmonic number
        to at least 6 decimals
        Time:
            n < 1e7 - log(n) if C++ loves you
            n >= 1e7 - n
    */
    if (n <= 1e7) {
        long double ans = 0;
        for (int i = 1; i <= n; i++) ans += (long double)1/i;
        return ans;
    }
    const long double y = 0.577215664901532860606512090082;
    long double ans = log(n)+y+1/(2*n)-1/(12*n*n)+1/(120*n*n*n*n);
    return ans;
}

int64_t div(int64_t a, int64_t b, int64_t m) { /* Modulo division | Time: log(m) */ return a*inv(b, m)%m; }

int64_t mult(int64_t a, int64_t b, int64_t m) { /* Modulo multiplication | Time: 1 */ return a*b%m; }

int64_t add(int64_t a, int64_t b, int64_t m) { /* Modulo addition | Time: 1 */ return (a+b)%m; }

int64_t sub(int64_t a, int64_t b, int64_t m) {
    /* Modulo subtraction | Time: 1 */
    a -= b;
    if (a < 0) a += m;
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /*
        Random shuffle
        Time: n
    */
    mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    vector<int> A(20);
    iota(all(A), 1);
    shuffle(all(A), mt);
    printl(A, " ");

    /*
        Reduced row echelon form example
    */
    RealMatrix M = {
        {3.0, 2.0, 2.0, 1.0},
        {4.0, 1.0, 3.0, 1.0},
        {6.0, 0.0, 1.0, 1.0}
    };
    M = reduced_row_echelon_form(M);
    cout.precision(9);
    cout << fixed;
    for (auto v : M) printl(v, " ");

    /*
        Chinese remainder theorem with big numbers example
        there are no big numbers in the example test
        but the method uses my Big operations
        x = 151 (mod 783)
        x = 57 (mod 278)
    */
    vector<int64_t> crt_A = {151, 57};
    vector<int64_t> crt_M = {783, 278};
    print(big_crt(crt_A, crt_M));

	return 0;
}
