#include <bits/stdc++.h>
using namespace std;
using num = long long;

struct robot {
    num px, py, vx, vy;
};

int main() {
    num wide = 101, tall = 103, q1 = 0, q2 = 0, q3 = 0, q4 = 0, xmas = 0;
    string line;
    vector<robot> robots;
    while (getline(cin, line)) {
        num px, py, vx, vy;
        sscanf(line.c_str(), "p=%lld,%lld v=%lld,%lld", &px, &py, &vx, &vy);
        robots.push_back({px, py, vx, vy});
        num x = (px + vx * 100) % wide;
        num y = (py + vy * 100) % tall;
        if (x < 0) x += wide;
        if (y < 0) y += tall;
        if (x < wide / 2 && y < tall / 2) ++q1;
        else if (x > wide / 2 && y < tall / 2) ++q2;
        else if (x < wide / 2 && y > tall / 2) ++q3;
        else if (x > wide / 2 && y > tall / 2) ++q4;
    }
    cout << "Part 1: " << q1 * q2 * q3 * q4 << endl;
    while (++xmas) {
        vector<vector<char>> pic(tall, vector<char>(wide, '.'));
        bool overlaps = false;
        for (auto &r : robots) {
            num x = (r.px + r.vx * xmas) % wide;
            num y = (r.py + r.vy * xmas) % tall;
            if (x < 0) x += wide;
            if (y < 0) y += tall;
            if (pic[y][x] == 'X') overlaps = true;
            pic[y][x] = 'X';
        }
        if (!overlaps) {
            cout << "Part 2: " << xmas << endl;
            for (num y = 0; y < tall; ++y) {
                for (num x = 0; x < wide; ++x) {
                    cout << pic[y][x];
                }
                cout << endl;
            }
            break;
        }
    }
    return 0;
}
