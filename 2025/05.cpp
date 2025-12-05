#include <bits/stdc++.h>
using namespace std;
using num = long long;
using range = pair<num, num>;

bool fresh(num ing, vector<range> &ranges) {
    for (range r : ranges) {
        if (ing >= r.first && ing <= r.second) return true;
    }
    return false;
}

void merge(vector<range> &ranges) {
    sort(ranges.begin(), ranges.end());
    vector<range> uq;
    num start = ranges[0].first, end = ranges[0].second;
    for (num i = 1; i < ranges.size(); ++i) {
        if (ranges[i].first <= end) {
            if (ranges[i].second >= end) end = ranges[i].second;
        } else {
            uq.push_back({start, end});
            start = ranges[i].first;
            end = ranges[i].second;
        }
    }
    uq.push_back({start, end});
    ranges = uq;
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    vector<range> ranges;
    while (getline(cin, line) && line != "") {
        auto split = line.find("-");
        ranges.push_back({stoll(line.substr(0, split)), stoll(line.substr(split + 1))});
    }
    merge(ranges);
    while (getline(cin, line)) {
        num ing = stoll(line);
        if (fresh(ing, ranges)) ++part1;
    }
    for (range r : ranges) {
        part2 += r.second - r.first + 1;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
