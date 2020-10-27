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