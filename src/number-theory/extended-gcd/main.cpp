pair<ll,ll> egcd(ll a, ll b){ // returns pair {x,y} such that a * x + b * y = gcd(a,b)
	if(b == 0) return {1, 0};
	auto t = egcd(b, a % b);
	return {
		t.second,
		t.first - a / b * t.second
	};
}
