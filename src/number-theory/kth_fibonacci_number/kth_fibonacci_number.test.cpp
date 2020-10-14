#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct kth_fib
{
	ll m;
	map<ll,ll> mem;
	kth_fib(ll _m) : m(_m) { } // m is modulo
	ll fib(ll n)
	{
		if(n <= 1) return n;
		if(mem.count(n)) return mem[n];
		ll ans;
		if(n & 1)
		{
			ll f = fib(n / 2 + 1);
			ll s = fib(n / 2);
			ans = mem[n] = (f*f + s*s) % m;
		}else
		{
			ll f = fib(n / 2);
			ll s = fib(n / 2 - 1);
			ans = mem[n] = f*(2*s + f) % m;
		}
		return ans;
	}
};

int main()
{
	ll n;
	cin >> n;
	kth_fib f(1000000007);
	cout << f.fib(n) << endl;
}
