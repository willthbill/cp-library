ll fib(ll n, ll m, map<ll,ll>& mem)
{
	if(n <= 1) return n;
	if(mem.count(n)) return mem[n];
	ll ans;
	if(n & 1)
	{
		ll f = fib(n / 2 + 1, m, mem);
		ll s = fib(n / 2, m, mem);
		ans = mem[n] = (f*f + s*s) % m;
	}else
	{
		ll f = fib(n / 2, m, mem);
		ll s = fib(n / 2 - 1, m, mem);
		ans = mem[n] = f*(2*s + f) % m;
	}
	return ans;
}
