// https://practice.geeksforgeeks.org/problems/kth-smallest-factor2345/1
#define ll long long
vector<ll> find_divisors(ll n){ // finds unique divisors, a divisor occurs only once in the result
	vector<ll> res;
	for(ll i = 1; i * i <= n; i++){
		if(n % i == 0){
			res.push_back(i);
			if(i * i != n) res.push_back(n / i);
		}
	}
	sort(res.begin(), res.end());
	return res;
}
class Solution {
  public:
    int kThSmallestFactor(int N , int K) {
		K--;
		auto t = find_divisors(N);
		if(t.size() > K) return t[K];
		return -1;
    }
};
