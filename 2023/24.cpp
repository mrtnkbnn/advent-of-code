#include <bits/stdc++.h>
using namespace std;
using num = long long;

struct Hailstone {
    num x, y, z, xd, yd, zd;

    Hailstone(num _x, num _y, num _z, num _xd, num _yd, num _zd) {
        x = _x; y = _y; z = _z; xd = _xd; yd = _yd; zd = _zd;
    }
};

bool intersect(Hailstone &hailstone1, Hailstone &hailstone2) {
    num x1 = hailstone1.x, y1 = hailstone1.y, x2 = hailstone1.x + hailstone1.xd, y2 = hailstone1.y + hailstone1.yd;
    num x3 = hailstone2.x, y3 = hailstone2.y, x4 = hailstone2.x + hailstone2.xd, y4 = hailstone2.y + hailstone2.yd;
    num denominator = ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    if (denominator == 0) return false;
	num ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denominator;
	num ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denominator;
    num x = x1 + ua * (x2 - x1);
	num y = y1 + ua * (y2 - y1);
    if (x < 200000000000000 || x > 400000000000000 || y < 200000000000000 || y > 400000000000000) return false;
    if (hailstone1.xd < 0 && x > x1) return false;
    if (hailstone1.xd > 0 && x < x1) return false;
    if (hailstone2.xd < 0 && x > x3) return false;
    if (hailstone2.xd > 0 && x < x3) return false;
    if (hailstone1.yd < 0 && y > y1) return false;
    if (hailstone1.yd > 0 && y < y1) return false;
    if (hailstone2.yd < 0 && y > y3) return false;
    if (hailstone2.yd > 0 && y < y3) return false;
    return true;
}

int main() {
    num x, y, z, xd, yd, zd, part1 = 0;
    vector<Hailstone> hailstones;
    while (scanf("%lld, %lld, %lld @ %lld, %lld, %lld\n", &x, &y, &z, &xd, &yd, &zd) != EOF) hailstones.push_back(Hailstone(x, y, z, xd, yd, zd));
    for (num i = 0; i < hailstones.size(); ++i) {
        for (num j = i + 1; j < hailstones.size(); ++j) if (intersect(hailstones[i], hailstones[j])) ++part1;
    }
    cout << "Part 1: " << part1 << endl;
    return 0;
}
