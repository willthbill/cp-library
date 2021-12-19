// sqrt(n) complexity
// if calculating all phi for 1..n, then read about that on cp-algorithms
int phi(int n) { 
	int res = n;
	for(int p = 2; p * p <= n; p++) {
		if(n % p == 0) {
			while(n % p == 0) n /= p;
			res -= res / p;
		}
	}
	if(n > 1) res -= res / n;
	return res;
}