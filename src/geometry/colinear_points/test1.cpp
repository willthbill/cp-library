#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define print(x) cout << x << endl
#define debug(x) cerr << #x << " : " << x << endl

template<class T>
bool are_points_colinear(vector<pair<T, T>>& points) {
    if (points.size() <= 2)
        return true;
    if (points[0].first-points[1].first == 0) {
        for (int i = 2; i < points.size(); i++) {
            if (points[i-1].first != points[i].first)
                return false;
    	}
        return true;
    }
    double a = (points[0].second-points[1].second)/(points[0].first-points[1].first);
    double b = points[0].second-a*points[0].first;
    for (int i = 2; i < points.size(); i++) {
        if (points[i].second != a*points[i].first+b)
            return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<pair<int, int>> points1 = {{0, 0}, {-1, -1}, {2, 2}, {5, 5}};
    vector<pair<int, int>> points2 = {{1, 3}, {2, 6}, {3, 12}, {3, 9}};

    cout << "Colinear ponts1: " << are_points_colinear<int>(points1) << endl; // 1
    cout << "Colinear ponts2: " << are_points_colinear<int>(points2) << endl; // 0

	return 0;
}
