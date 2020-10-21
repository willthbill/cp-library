// https://open.kattis.com/problems/modulararithmetic
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll gcd(ll a, ll b) { return (a % b == 0) ? b : gcd(b, a % b); }
pair<ll,ll> egcd(ll a, ll b){
	if(b == 0) return {1, 0};
	auto t = egcd(b, a % b);
	return {
		t.second,
		t.first - a / b * t.second
	};
}
ll mpow(ll a, ll b, ll m){ // a^b % m
	ll res = 1;
	while(b){
		if(b & 1) res = res * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return res;
}
ll mdiv(ll a, ll b, ll m, bool isPrime){ // a / b % m where isPrime tells whether m is prime. Note: isPrime may be false even though m is prime. b and m must be coprime.
	if(isPrime) return a * mpow(b, m - 2, m) % m;
	return ((a * egcd(b, m).first % m) + m) % m;
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
int main(){
	ll n, t;
	while(1){
		cin >> n >> t;
		if(n == 0 && t == 0) break;
		for(int i = 0; i < t; i++){
			ll a,b; char op; cin >> a >> op >> b;
			if(op == '/'){
				if(b == 0 || gcd(b, n) != 1) cout << -1 << endl;
				else cout << mdiv(a,b,n,false) << endl;
			}else if(op == '+'){
				cout << madd(a,b,n) << endl;
			}else if(op == '-'){
				cout << msub(a,b,n) << endl;
			}else{
				cout << mmul(a,b,n) << endl;
			}
		}
	}
}
