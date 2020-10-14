ll mod_pow(ll a, ll b, ll m) // a^b % m
{
	ll res = 1;
	while(b)
	{
		if(b & 1) res = res * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return res;
}
