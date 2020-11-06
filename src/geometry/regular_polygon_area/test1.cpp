#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define print(x) cout << x << endl
#define debug(x) cerr << #x << " : " << x << endl

template<class T>
double regular_polygon_area(T n, T s, double pi) {
    return n*s/(4*tan(pi/n));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n = 5;
    long long s = 7;
    double pi = 3.14159;
    cout << "Area: " << regular_polygon_area<long long>(n, s, pi) << endl;

	return 0;
}