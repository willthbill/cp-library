template<class Int, class Auxiliary>
vector<pair<Int, Auxiliary>> counting_sort(vector<pair<Int, Auxiliary>> A, int max_val) {
	int n = A.size();
	vector<int> cnt(n + 1, 0);
	for (int i = 0; i < n; i++)
		cnt[A[i].fs + 1]++;
	for (int i = 1; i < n; i++)
		cnt[i] += cnt[i - 1];
	vector<pair<Int, Auxiliary>> res(n);
	for (int i = 0; i < n; i++)
		res[cnt[A[i].fs]++] = A[i];
	return res;
}
