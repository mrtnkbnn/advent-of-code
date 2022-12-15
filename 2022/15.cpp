#include <bits/stdc++.h>
using namespace std;

struct report {
    long long sensorX, sensorY, beaconX, beaconY, dist;

    report(long long x1, long long y1, long long x2, long long y2) {
        sensorX = x1;
        sensorY = y1;
        beaconX = x2;
        beaconY = y2;
        dist = abs(x1 - x2) + abs(y1 -y2);
    }
};

long long findRowScore(long long y, vector<report>& reports, long long limit) {
    long long result = 0;
    vector<pair<long long, long long>> found;
    for (report r : reports) {
        long long vertDist = abs(r.sensorY - y);
        if (vertDist < r.dist) {
            long long diff = r.dist - vertDist;
            long long startX = r.sensorX - diff;
            long long endX = r.sensorX + diff;
            found.push_back(make_pair(startX, endX));
        }
    }
    sort(found.begin(), found.end());
    int maxX = 0;
    for (int i = 0; i < found.size(); ++i) {
        pair<long, long> p1 = found[i];
        if (p1.first - 1 <= maxX && p1.second > maxX) {
            maxX = p1.second;
        }
    }
    if (maxX >= limit) {
        return -1;
    } else {
        return (maxX + 1LL) * 4000000LL + y;
    }
}

int main() {
    long long x1, y1, x2, y2;
    long long part1Y = 2000000LL;
    set<pair<long long, long long>> part1Points;
    set<pair<long long, long long>> beacons;
    vector<report> reports;
    while (scanf("Sensor at x=%lld, y=%lld: closest beacon is at x=%lld, y=%lld\n", &x1, &y1, &x2, &y2) != EOF) {
        reports.push_back(report(x1, y1, x2, y2));
        beacons.insert(make_pair(x2, y2));
    }
    for (report r : reports) {
        long long vertDist = abs(r.sensorY - part1Y);
        if (vertDist < r.dist) {
            long long diff = r.dist - vertDist;
            for (int x = r.sensorX - diff; x <= r.sensorX + diff; ++x) {
                if (beacons.find(make_pair(x, part1Y)) == beacons.end()) {
                    part1Points.insert(make_pair(x, part1Y));
                }
            }
        }
    }
    long long limit = 4000000LL, part2;
    for (long long y = 0; y <= limit; ++y) {
        long long result = findRowScore(y, reports, limit);
        if (result != -1) {
            part2 = result;
            break;
        }
    }
    cout << "Part 1: " << part1Points.size() << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
