/*
https://cses.fi/problemset/task/2192/
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

struct Line {
    P a, b;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;

    const C INF = 1e9+1;

    vector<Line> B(n);
    vector<P> A(n);

    function<int(P, bool&)> intersections = [&] (P p, bool& boundary) {
        int cnt = 0;
        boundary = false;
        for (int i = 0; i < n; i++) {
            P a = B[i].a, b = B[i].b, c = p, d = {INF, p.Y};

            function<int64_t(P, P)> cp = [&] (P p1, P p2) {
                return (conj(p1)*p2).Y;
            };

            if (cp(b-a, c-b) == 0) {
                vector<P> A = {a, b, c};
                sort(A.begin(), A.end(), [&] (const P a, const P b) {
                    return a.X == b.X ? a.Y < b.Y : a.X < b.X;
                });
                if ((A[0] != c && A[2] != c) || a == c || b == c) {
                    boundary = true;
                }
            }
    
            if (a == c || a == d || b == c || b == d) {
                cnt++;
                continue;
            }
    
            if (cp(a-b, b-c) == 0 && cp(b-c, c-d) == 0) {
                vector<P> A = {a, b, c, d};
                sort(A.begin(), A.end(), [&] (const P a, const P b) {
                    return a.X == b.X ? a.Y < b.Y : a.X < b.X;
                });
                if (((A[0] == a || A[0] == b) && (A[1] != a && A[1] != b)) || 
                    ((A[0] == c || A[0] == d) && (A[1] != c && A[1] != d))
                ) {
                    cnt++;
                    continue;
                }
                continue;
            }
    
            if ((((cp(a-b, c-a) <= 0) != (cp(a-b, d-a) < 0)) && ((cp(c-d, a-c) <= 0) != (cp(c-d, b-c) < 0))) ||
                (((cp(a-b, c-a) < 0) != (cp(a-b, d-a) <= 0)) && ((cp(c-d, a-c) < 0) != (cp(c-d, b-c) <= 0)))
            ) {
                if (cp(c-d, b-c) == 0) {
                    // if b intersects c->INF
                    // there are 4 cases
                    // |, L , _| and v
                    // we do nothing if case v
                    if ((cp(b-c, a-b) < 0) != (cp(b-c, B[(i+1)%n].b-b) < 0)) {
                        if (cp(b-c, a-b) != 0 && cp(b-c, B[(i+1)%n].b-b) != 0) { 
                            cnt++; // case: |
                        } else {
                            cnt += cp(b-c, a-b) != 0; // case: L or _|
                        }
                    }
                }
                cnt++;
                continue;
            }
        }
        return cnt;
    };

    for (int i = 0; i < n; i++) {
        C x, y; cin >> x >> y;
        A[i] = {x, y};
    }

    A.push_back(*A.begin());

    for (int i = 0; i < n; i++) {
        B[i].a = A[i];
        B[i].b = A[i+1];
    }

    for (int i = 0; i < q; i++) {
        C x, y; cin >> x >> y;
        bool boundary;
        int cnt = intersections({x, y}, boundary);
        if (boundary) {
            print("BOUNDARY");
        } else if (cnt%2) {
            print("INSIDE");
        } else {
            print("OUTSIDE");
        }
    }

	return 0;
}
