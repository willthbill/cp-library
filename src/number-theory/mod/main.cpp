ll mpow(ll a, ll b, ll m){ // a^b % m
	ll res = 1;
	while(b){
		if(b & 1) res = res * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return res;
}
ll mdiv(ll a, ll b, ll m){ // a / b % m where m is prime
	return a * mpow(b, m - 2, m) % m;
}
ll mmul(ll a, ll b, ll m){
	return a * b % m;
}
ll madd(ll a, ll b, ll m){
	return (((a + b) % m) + m) % m;
}
ll msub(ll a, ll b, ll m){ // (a-b)%m
	return (((a - b) % m) + m) % m;
}
