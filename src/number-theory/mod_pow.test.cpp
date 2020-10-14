#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MOD 1000000007

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

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		ll a, b;
		cin >> a >> b;
		cout << mod_pow(a, b, MOD) << endl;
	}
}
