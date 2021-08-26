/*
https://cses.fi/problemset/task/2195
*/

#include <bits/stdc++.h>
using namespace std;
typedef int64_t C;
typedef complex<C> P;
#define X real()
#define Y imag()
#define ll long long
#define print(x) cout << x << endl
#define debug(x) cerr << #x << " : " << x << endl
#define len(x) (int)x.size()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    vector<P> H;
    vector<P> A(n);

    for (int i = 0; i < n; i++) {
        C x, y; cin >> x >> y;
        A[i] = {x, y};
    }

    sort(A.begin(), A.end(), [&] (const P a, const P b) {
        return a.X == b.X ? a.Y < b.Y : a.X < b.X;
    });
    for (int i = 0; i < n; i++) {
        if (len(H) < 2) {
            H.push_back(A[i]);
            continue;
        }
        P a = *(++H.rbegin()), b = *H.rbegin(), c = A[i];
        while ((conj(b-a)*(c-b)).Y > 0) {
            H.pop_back();
            if (len(H) < 2) break;
            a = *(++H.rbegin());
            b = *H.rbegin();
        }
        H.push_back(c);
    }

    sort(A.begin(), A.end(), [&] (const P a, const P b) {
        return a.X == b.X ? a.Y > b.Y : a.X > b.X;
    });
    H.push_back(A[1]);
    for (int i = 2; i < n; i++) {
        P a = *(++H.rbegin()), b = *H.rbegin(), c = A[i];
        while ((conj(b-a)*(c-b)).Y > 0) {
            H.pop_back();
            a = *(++H.rbegin());
            b = *H.rbegin();
        }
        if (i+1 != n) H.push_back(c);
    }

    print(len(H));
    for (int i = 0; i < len(H); i++) {
        print(H[i].X << " " << H[i].Y);
    }

	return 0;
}
