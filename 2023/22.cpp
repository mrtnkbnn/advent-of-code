#include <bits/stdc++.h>
using namespace std;
using num = long long;

struct Brick {
    num name;
    pair<num, num> x;
    pair<num, num> y;
    pair<num, num> z;
    vector<num> restsOn;

    Brick(num n, num x1, num y1, num z1, num x2, num y2, num z2) {
        name = n;
        x = {min(x1, x2), max(x1, x2)};
        y = {min(y1, y2), max(y1, y2)};
        z = {min(z1, z2), max(z1, z2)};
    }
};

bool byHeight(Brick &brick1, Brick &brick2) {
    if (brick1.z.first != brick2.z.first) {
        return brick1.z.first < brick2.z.first;
    } else {
        if (brick1.z.second != brick2.z.second) {
            return brick1.z.second < brick2.z.second;
        } else {
            if (brick1.y.first != brick2.y.first) {
                return brick1.y.first < brick2.y.first;
            } else {
                return brick1.x.first < brick2.x.first;
            }
        }
    }
}

bool overlap(pair<num, num> &coord1, pair<num, num> &coord2) {
    if (coord2.first > coord1.second) return false;
    else if (coord1.first > coord2.second) return false;
    return true;
}

num fall(num brickName, vector<Brick> bricks) {
    num result = 0;
    for (num i = 0; i < bricks.size(); ++i) {
        if (bricks[i].name == brickName) {
            bricks.erase(bricks.begin() + i);
            break;
        }
    }
    for (num i = 0; i < bricks.size(); ++i) {
        if (bricks[i].z.first == 1) continue;
        num z = 0;
        vector<num> restsOn;
        for (num j = i - 1; j >= 0; --j) {
            if (overlap(bricks[i].x, bricks[j].x) && overlap(bricks[i].y, bricks[j].y)) {
                if (bricks[j].z.second > z) {
                    z = bricks[j].z.second;
                    restsOn = {bricks[j].name};
                } else if (bricks[j].z.second == z) {
                    restsOn.push_back(bricks[j].name);
                }
            }
        }
        ++z;
        num delta = abs(z - bricks[i].z.first);
        if (delta > 0) ++result;
        bricks[i].z.first -= delta;
        bricks[i].z.second -= delta;
        bricks[i].restsOn = restsOn;
    }
    return result;
}

int main() {
    num x1, y1, z1, x2, y2, z2, names = 0, part2 = 0;
    vector<Brick> bricks;
    while (scanf("%lld,%lld,%lld~%lld,%lld,%lld\n", &x1, &y1, &z1, &x2, &y2, &z2) != EOF) {
        bricks.push_back(Brick(names, x1, y1, z1, x2, y2, z2));
        ++names;
    }
    sort(bricks.begin(), bricks.end(), byHeight);
    for (num i = 0; i < bricks.size(); ++i) {
        if (bricks[i].z.first == 1) continue;
        num z = 0;
        vector<num> restsOn;
        for (num j = i - 1; j >= 0; --j) {
            if (overlap(bricks[i].x, bricks[j].x) && overlap(bricks[i].y, bricks[j].y)) {
                if (bricks[j].z.second > z) {
                    z = bricks[j].z.second;
                    restsOn = {bricks[j].name};
                } else if (bricks[j].z.second == z) {
                    restsOn.push_back(bricks[j].name);
                }
            }
        }
        ++z;
        num delta = abs(z - bricks[i].z.first);
        bricks[i].z.first -= delta;
        bricks[i].z.second -= delta;
        bricks[i].restsOn = restsOn;
    }
    set<num> cannot;
    for (num i = 0; i < bricks.size(); ++i) {
        if (bricks[i].restsOn.size() == 1) cannot.insert(bricks[i].restsOn[0]);
    }
    for (num n : cannot) part2 += fall(n, bricks);
    cout << "Part 1: " << bricks.size() - cannot.size() << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
