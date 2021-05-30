%include<data-structures/bit>%

int invNumber(vector<int> A) { // elements of a are between 0 and A.size() - 1
	int n = A.size();
	BIT<int> ft(n);
	vector<int> tmp(n, 0);
	ft.setupsingle(tmp);
	int ans = 0;
	for(int i = n - 1; i >= 0; i--) {
		ans += A[i] > 0 ? ft.q(A[i] - 1) : 0;
		ft.add(A[i], 1);
	}
	return ans;
}