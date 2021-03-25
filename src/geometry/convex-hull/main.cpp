template<class T>
class ConvexHull {
    class ConvexHullUtill {
        pair<T, T> p0;
    public:
        ConvexHullUtill(pair<T, T> _p0) {
            p0 = _p0;
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
                return (distPow2(p0, p2) > distPow2(p0, p1)) ? true : false;
            return (o == 2) ? true : false;
        }
    };
    static pair<T, T> below_top(stack<pair<T, T>>& S) {
        pair<T, T> p = S.top();
        S.pop();
        pair<T, T> res = S.top();
        S.push(p);
        return res;
    }
public:
    static void convex_hull(stack<pair<T,T>>& S, vector<pair<T,T>> points) {
        int n = (int)points.size();
        if(n == 0) return;
        set<pair<int,int>> _s;
        for(int i = 0; i < n; i++) _s.insert(points[i]);
        points.resize(_s.size());
        int idx = 0;
        for(auto& e : _s) {
          points[idx++] = e;
        }
        n = (int)points.size();
        int ymn = points[0].second, mn = 0;
        for (int i = 1; i < n; i++) {
            T y = points[i].second;
            if ((y < ymn) || (ymn == y && points[i].first < points[mn].first))
                ymn = points[i].second, mn = i;
        }
        swap(points[0], points[mn]);
        pair<T, T> p0 = points[0];
        ConvexHullUtill util(p0);
        sort(points.begin()+1, points.end(), util);
        int m = 1;
        for (int i = 1; i < n; i++) {
            while (i < n-1 && util.orientation(p0, points[i], points[i+1]) == 0)
                i++;
            points[m] = points[i];
            m++;
        }
        if (m < 3) {
            for(int i = 0; i < m; i++) S.push(points[i]);
            return;
        }
        S.push(points[0]);
        S.push(points[1]);
        S.push(points[2]);
        for (int i = 3; i < m; i++) {
            while (util.orientation(below_top(S), S.top(), points[i]) != 2)
                S.pop();
            S.push(points[i]);
        }
    }
    static vector<pair<T,T>> convex_hull(vector<pair<T, T>>& points) {
        stack<pair<T,T>> s;
        convex_hull(s, points);
        vector<pair<T,T>> res (s.size());
        int idx = (int)s.size();
        while(!s.empty()){
          res[--idx] = s.top();
          s.pop();
        }
        return res;
    }
};
