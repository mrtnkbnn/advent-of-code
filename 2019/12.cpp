#include <bits/stdc++.h>
using namespace std;
using num = long long;

struct coord {
    num x = 0, y = 0, z = 0;
};

vector<vector<num>> state(vector<coord> &moons, vector<coord> &velocities) {
    vector<num> x, y, z;
    for (num i = 0; i < moons.size(); ++i) {
        x.push_back(moons[i].x);
        x.push_back(velocities[i].x);
        y.push_back(moons[i].y);
        y.push_back(velocities[i].y);
        z.push_back(moons[i].z);
        z.push_back(velocities[i].z);
    }
    return {x, y, z};
}

int main() {
    num part1 = 0, xcycle = -1, ycycle = -1, zcycle = -1, step = 0;
    string line;
    vector<coord> moons;
    while (getline(cin, line)) {
        num x, y, z;
        sscanf(line.c_str(), "<x=%lld, y=%lld, z=%lld>", &x, &y, &z);
        moons.push_back({x, y, z});
    }
    vector<coord> velocities(moons.size(), {0, 0, 0});
    auto initial = state(moons, velocities);
    while (true) {
        for (num i = 0; i < moons.size(); ++i) {
            for (num j = i + 1; j < moons.size(); ++j) {
                if (moons[i].x < moons[j].x) {
                    ++velocities[i].x;
                    --velocities[j].x;
                } else if (moons[i].x > moons[j].x) {
                    --velocities[i].x;
                    ++velocities[j].x;
                }

                if (moons[i].y < moons[j].y) {
                    ++velocities[i].y;
                    --velocities[j].y;
                } else if (moons[i].y > moons[j].y) {
                    --velocities[i].y;
                    ++velocities[j].y;
                }

                if (moons[i].z < moons[j].z) {
                    ++velocities[i].z;
                    --velocities[j].z;
                } else if (moons[i].z > moons[j].z) {
                    --velocities[i].z;
                    ++velocities[j].z;
                }
            }
        }
        for (num i = 0; i < moons.size(); ++i) {
            moons[i].x += velocities[i].x;
            moons[i].y += velocities[i].y;
            moons[i].z += velocities[i].z;
        }
        if (step == 999) {
            for (num i = 0; i < moons.size(); ++i) {
                part1 += (abs(moons[i].x) + abs(moons[i].y) + abs(moons[i].z)) * (abs(velocities[i].x) + abs(velocities[i].y) + abs(velocities[i].z));
            }
        }
        auto current = state(moons, velocities);
        if (xcycle == -1 && initial[0] == current[0]) xcycle = step + 1;
        if (ycycle == -1 && initial[1] == current[1]) ycycle = step + 1;
        if (zcycle == -1 && initial[2] == current[2]) zcycle = step + 1;
        if (xcycle != -1 && ycycle != -1 && zcycle != -1) break;
        ++step;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << lcm(xcycle, lcm(ycycle, zcycle)) << endl;
    return 0;
}
