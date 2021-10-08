// change MX to change for which n you want to calculate all primes p such that p <= n
// this version is optimized for memory, using bitsets, which are great
const int MX = 1e8;
bitset<MX> + 1> cnt;
vector<int> sieve(int n) {
    for (int i = 2; i <= n; i++) {
        if (cnt[i])
            continue;
        for (int j = i*i; j <= n; j += i)
            cnt[j] = 1;
    }
    vector<int> primes;
    for (int i = 2; i <= n; i++)
        if(!cnt[i]) primes.pb(i);
    return primes;
}