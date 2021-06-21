// https://codeforces.com/contest/1539/problem/E
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define fs first
#define sc second
 
struct node {
	node* left = NULL;
	node* right = NULL;
	int mx, atr, atl;
	node(node* l, node* r, int v, int al, int ar) {
		left = l; right = r;
		mx = v;
		atl = al; atr = ar;
	}
	~node() {
		delete left;
		delete right;
	}
	void change(int at, int to) { // changes index of at into value of to
		if(at > atr || at < atl) return;
		if(at == atr && at == atl) {
			mx = to;
			return;
		}
		left->change(at,to);
		right->change(at,to);
		update();
	}
	void update() { // Changes everything when done
		mx = max(left->mx, right->mx);
	}
	int qmx(int l, int r) { // gets the max value from l to r
		if(l > atr || r < atl) return 0;
		if(l <= atl && atr <= r) return mx;
		return max(left->qmx(l,r), right->qmx(l,r));
	}
};
node* build(int l, int r) {
	if(l > r) return NULL;
	if(l == r) return new node(NULL,NULL,0,l,r);
	int m = (l+r)/2;
	node* left = build(l,m);
	node* right = build(m+1,r);
	node* cur = new node(left,right,0,l,r);
	return cur;
}
 
int hik(int n) {
    int k = 0;
    while(n >>= 1) k++;
    return k;
}
 
template<class T, T(*F)(T,T)>
struct RQA { // requires F(x, F(x, x)) = F(F(x, x), x) = x
    vector<vector<T>> M;
    int n;
    RQA(vector<T> A) {
        n = A.size();
        M = vector<vector<T>>(17,vector<T>(n));
        for(int i = 0; i < n; i++) {
            M[0][i] = A[i];
        }
        for(int k = 1; k < 17; k++) {
            for(int i = 0; i < n; i++) {
                int nxt = min(n - 1, i + (1 << (k - 1)));
                M[k][i] = F(M[k - 1][i], M[k - 1][nxt]);
            }
        }
    }
    T q(int l, int r) {
        int k = hik(r - l + 1);
        return F(M[k][l], M[k][r - (1 << k) + 1]);
    }
};
 
int maxF(int a, int b) {
	return max(a, b);
}
 
int minF(int a, int b) {
	return min(a, b);
}
 
int n, m; 
vector<int> K;
vector<vector<int>> A, B;
vector<RQA<int, minF>> SidesValid, BSides;
vector<RQA<int, maxF>> ASides;
vector<node*> Dps;
vector<vector<int>> dp;
vector<int> solution;
void trace(int i, bool side) { // O(n)
	if(i == n) {
		return;
	}
	int constantValue = (i == 0 ? 0 : K[i - 1]);
	for(int j = i; j < n; j++) {
		solution.pb(side);
		if(A[side][j] <= K[j] && K[j] <= B[side][j] && A[!side][j] <= constantValue && constantValue <= B[!side][j]) {
			if(dp[j + 1][!side])  {
				trace(j + 1, !side);
				return;
			}
		} else {
			break;
		}
	}
}
 
int main() {
    cin.sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m;
	K = vector<int>(n);
	A = B = vector<vector<int>>(2, vector<int>(n));
	for(int i = 0; i < n; i++) {
		cin >> K[i] >> A[0][i] >> B[0][i] >> A[1][i] >> B[1][i];
	}
	vector<vector<int>> sidesValid(2, vector<int>(n));
    for(int s = 0; s < 2; s++) {
		Dps.pb(build(0, n));
		for(int i = 0; i < n; i++) {
			sidesValid[s][i] = (A[s][i] <= K[i] && K[i] <= B[s][i]);
			Dps[s]->change(i, 0);
		}
		SidesValid.pb(RQA<int, minF>(sidesValid[s]));
        ASides.pb(RQA<int, maxF>(A[s]));
        BSides.pb(RQA<int, minF>(B[s]));
        Dps[s]->change(n, 1);
	}
    dp = vector<vector<int>>(n + 1, vector<int>(2));
	dp[n][0] = dp[n][1] = 1;
	for(int i = n - 1; i >= 0; i--) {
		for(int side = 0; side < 2; side++) {
			int constantValue = (i == 0 ? 0 : K[i - 1]);
			int lo = i, hi = n - 1, bst = -1;
            while(lo <= hi) {
				int j = (lo + hi) / 2;
				if(SidesValid[side].q(i, j) == 1 && ASides[!side].q(i, j) <= constantValue && constantValue <= BSides[!side].q(i, j)) {
					lo = j + 1;
					bst = j + 1;
				}else {
					hi = j - 1;
				}
			}
			if(bst != -1) {
				dp[i][side] = Dps[!side]->qmx(i + 1, bst);
				Dps[side]->change(i, dp[i][side]);
			}
		}
	}
	for(int start = 0; start < 2; start++) {
        if(dp[0][start]) {
            cout << "Yes" << endl;
            trace(0, start);
            for(int k : solution) {
                cout << k << ' ';
            }
            return 0;
        }
	}
	cout << "No" << endl;
}