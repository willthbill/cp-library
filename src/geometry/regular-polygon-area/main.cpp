template<class T>
double regular_polygon_area(T n, T s, double pi) {
    return n*s/(4*tan(pi/n));
}