// this never got two work
#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll gcd(ll a, ll b) { return (a % b == 0) ? b : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }

pair<ll,ll> egcd(ll a, ll b){ // returns pair {x,y} such that a * x + b * y = gcd(a,b)
	if(b == 0) return {1, 0};
	auto t = egcd(b, a % b);
	return {
		t.second,
		t.first - a / b * t.second
	};
}
vector<pair<ll,ll>> frogs;
ll eval(vector<int>& indices){
	ll pos1 = frogs[indices[0]].first;
	ll speed1 = frogs[indices[0]].second;
	for(int i = 1; i < indices.size(); i++){
		ll pos2 = frogs[indices[i]].first;
		ll speed2 = frogs[indices[i]].second;
		auto p = egcd(speed1, speed2);
		cout << pos1 << " " << pos2 << endl;
		cout << speed1 << " " << speed2 << endl;
		cout << p.first << " " << p.second << endl;
		if(p.first < 0) swap(p.first, p.second), swap(pos1, pos2), swap(speed1, speed2);
		p.first *= (pos2 - pos1) / gcd(speed1, speed2);
		pos1 += p.first * speed1;
		speed1 = lcm(speed1, speed2);
	}
	return pos1;
}
int main(){
	int n; cin >> n;
	vector<vector<int>> adj (n);
	frogs = vector<pair<ll,ll>> (n);
	for(int i = 0; i < n; i++){
		int x,d; cin >> x >> d; frogs[i] = {x,d};
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			ll diff = frogs[i].first - frogs[j].first;
			if(diff % gcd(frogs[i].second, frogs[j].second) == 0){
				adj[i].push_back(j);
			}
		}
	}
	int mxi = 0;
	ll best = LLONG_MAX;
	for(int i = 0; i < n; i++){
		auto e = eval(adj[i]);
		if(adj[i].size() == adj[mxi].size() && e < best) mxi = i, best = e;
		else if(adj[i].size() > adj[mxi].size()) mxi = i, best = e;
	}
	cout << best << " " << adj[mxi].size() << endl;
}
