template<class T>
class ConvexHullUtill {
    pair<T, T> p0;

public:
    ConvexHullUtill(pair<T, T> p0) {
        this->p0 = p0;
    }

    int distPow2(pair<T, T> p1, pair<T, T> p2) {
        return (p1.first-p2.first)*(p1.first-p2.first)+(p1.second-p2.second)*(p1.second-p2.second);
    }

    int orientation(pair<T, T> p, pair<T, T> q, pair<T, T> r) {
        int val = (q.second-p.second)*(r.first-q.first)-(q.first-p.first)*(r.second-q.second);
        if (val == 0)
            return 0;
        return (val > 0) ? 1 : 2;
    }

    bool operator()(const pair<T, T>& p1, const pair<T, T>& p2) {
        int o = orientation(p0, p1, p2);
        if (o == 0)
            return (distPow2(p0, p2) >= distPow2(p0, p1)) ? true : false;
        return (o == 2) ? true : false;
    }
};

template<class T>
class ConvexHull {
    pair<T, T> below_top(stack<pair<T, T>>& S) {
        pair<T, T> p = S.top();
        S.pop();
        pair<T, T> res = S.top();
        S.push(p);
        return res;
    }

    int swap(pair<T, T>& p1, pair<T, T>& p2) {
        pair<T, T> temp = p1;
        p1 = p2;
        p2 = temp;
    }

public:
    void convex_hull(stack<pair<T, T>>& S, vector<pair<T, T>>& points, int n) {
        int ymn = points[0].second, mn = 0;
        for (int i = 1; i < n; i++) {
            T y = points[i].second;
            if ((y < ymn) || (ymn == y && points[i].first < points[mn].first))
                ymn = points[i].second, mn = i;
        }
        swap(points[0], points[mn]);
        pair<T, T> p0 = points[0];
        ConvexHullUtill<long long> util(p0);
        sort(points.begin()+1, points.end(), util);
        int m = 1;
        for (int i = 1; i < n; i++) {
            while (i < n-1 && util.orientation(p0, points[i], points[i+1]) == 0)
                i++;
            points[m] = points[i];
            m++;
        }
        if (m < 3)
            return;
        S.push(points[0]);
        S.push(points[1]);
        S.push(points[2]);
        for (int i = 3; i < m; i++) {
            while (util.orientation(below_top(S), S.top(), points[i]) != 2)
                S.pop();
            S.push(points[i]);
        }
    }
};