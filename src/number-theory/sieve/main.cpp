vector<int> sieve(int n) {
	vector<int> cnt(n + 1, 0);
	for(int i = 2; i <= n; i++)
		for(int j = i; j <= n; j += i)
			cnt[j]++;
	vector<int> ans;
	for(int i = 2; i <= n; i++)
		if(cnt[i] == 1)
			ans.pb(i);
	return ans;
}
