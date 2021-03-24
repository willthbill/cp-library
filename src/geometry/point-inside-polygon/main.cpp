template<class T>
class LineUtill {
public:
    pair<double, double> line_from_points(pair<T, T> p1, pair<T, T> p2) {
        double a = ((double)p1.second-p2.second)/((double)p1.first-p2.first);
        double b = p1.second-a*p1.first;
        pair<double, double> line = {a, b};
        return line;
    }

    bool intersection_exists(pair<T, T> a, pair<T, T> b) {
        return (a.first != b.first) ? true : false;
    }

    pair<double, double> intersection(pair<T, T> a, pair<T, T> b) {
        double x = (double)(b.second-a.second)/(a.first-b.first);
        pair<double, double> p = {x, a.first*x+a.second};
        return p;
    }
};

template<class T>
bool point_inside_polygon(vector<pair<pair<T, T>, pair<T, T>>>& sides, pair<T, T> point) {
    int cnt = 0;
    LineUtill<double> lu;
    for (int i = 0; i < sides.size(); i++) {
        pair<T, T> p1 = sides[i].first;
        pair<T, T> p2 = sides[i].second;
        pair<double, double> l1 = lu.line_from_points(point, {point.first+1, point.second});

        if (point.first >= min(p1.first, p2.first) && point.first <= max(p1.first, p2.first)) {
            pair<double, double> l2 = lu.line_from_points(sides[i].first, sides[i].second);
            if (!lu.intersection_exists(l1, l2)) {
                continue;
            }
            pair<double, double> intersection_point = lu.intersection(l1, l2);
            if (p1.first == p2.first || point.first <= intersection_point.first) {
                if (intersection_point.first == point.first && intersection_point.second == point.second) {
                    return true;
                }
                cnt++;
            }
        } else if (point.first < p1.first) {
            if (point.second <= max(p1.second, p2.second) && point.second >= min(p1.second, p2.second)) {
                cnt++;
            }
        }
    }

    return (cnt%2 != 0) ? true : false;
}