#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define print(x) cout << x << endl
#define debug(x) cerr << #x << " : " << x << endl

template<class T>
class VectorUtil {
    double pi = 3.1415926535;

public:
    VectorUtil() {}

    VectorUtil(double pi) {
        this->pi = pi;
    }

    T det(pair<T, T> a, pair<T, T> b) {
        return a.first*b.second-a.second*b.first;
    }

    T dot_product(pair<T, T> a, pair<T, T> b) {
        return a.first*b.first+a.second*b.second;
    }

    double length(pair<T, T> a) {
        return sqrt(a.first*a.first+a.second*a.second);
    }

    double vector_angle(pair<T, T> a) {
        return acos(a.first/length(a))*180/pi;
    }

    double angle(pair<T, T> a, pair<T, T> b) {
        return acos(dot_product(a, b)/(length(a)*length(b)))*180/pi;
    }

    pair<double, double> rotated_vector(pair<T, T> a, double v) {
        pair<double, double> p = {cos(v*pi/180)*a.first-sin(v*pi/180)*a.second, sin(v*pi/180)*a.first+cos(v*pi/180)*a.second};
        return p;
    }

    bool orthogonal(pair<T, T> a, pair<T, T> b) {
        if (a.first == 0 || b.first == 0) {
            return ((a.first == 0 && b.second == 0) || (b.first == 0 && a.second == 0)) ? true : false;
        }
        return (((double)a.second/a.first)*((double)b.second/b.first) == -1) ? true : false;
    }

    bool parallel(pair<T, T> a, pair<T, T> b) {
        if (a.first == 0 || b.first == 0) {
            return (a.first == 0 && b.first == 0) ? true : false;
        }
        return ((double)a.second/a.first) == ((double)b.second/b.first);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // no tests here. used it for testing, but deleted it again

	return 0;
}