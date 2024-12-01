#include <bits/stdc++.h>
using namespace std;
using num = long long;

int main() {
    num a, b, part1 = 0, part2 = 0;
    vector<num> left, right;
    map<num, num> count;
    while (cin >> a >> b) {
        left.push_back(a);
        right.push_back(b);
        ++count[b];
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    for (num i = 0; i < left.size(); ++i) {
        part1 += abs(left[i] - right[i]);
        part2 += left[i] * count[left[i]];
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
