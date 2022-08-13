struct Circle { long double x; long double y; long double r; } a, b;
cin >> a.x >> a.y >> a.r;
cin >> b.x >> b.y >> b.r;
if (a.r < b.r) {
    swap(a, b);
}
auto area = [&] (Circle a, Circle b) -> long double {
    long double d = hypot(a.x-b.x, a.y-b.y);
    a.x = 0, a.y = 0, b.x = d, b.y = 0;
    if ((d < a.r+b.r) == false) {
        return 0;
    }
    if ((d > a.r-b.r) == false) {
        return acos(-1)*b.r*b.r;
    }
    long double d1 = (a.r*a.r-b.r*b.r+d*d)/(2*d);
    long double d2 = (b.r*b.r-a.r*a.r+d*d)/(2*d);
    assert(abs(d2-(d-d1)) < 0.000001);
    return a.r*a.r*(2*acos(d1/a.r)-sin(2*acos(d1/a.r)))/2+b.r*b.r*(2*acos(d2/b.r)-sin(2*acos(d2/b.r)))/2;
};
cout.precision(12);
cout << fixed;
print(area(a, b));
