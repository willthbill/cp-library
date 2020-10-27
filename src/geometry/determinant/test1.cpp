#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define print(x) cout << x << endl
#define debug(x) cerr << #x << " : " << x << endl

template<class T>
T det(T ax, T ay, T bx, T by) {
    return ax*by-ay*bx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << det<int>(3, 2, 1, 5) << endl; // 13    

	return 0;
}