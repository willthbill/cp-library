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
