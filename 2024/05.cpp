#include <bits/stdc++.h>
using namespace std;
using num = long long;

map<num, set<num>> rules;

bool compare(num a, num b) {
    return rules[a].find(b) != rules[a].end();
}

int main() {
    num part1 = 0, part2 = 0, n;
    string line;
    while (getline(cin, line) && line != "") {
        num left, right;
        sscanf(line.c_str(), "%lld|%lld", &left, &right);
        rules[left].insert(right);
    }
    while (getline(cin, line)) {
        vector<num> update;
        stringstream ss(line);
        while (ss >> n) {
            update.push_back(n);
            ss.ignore();
        }
        if (is_sorted(update.begin(), update.end(), compare)) part1 += update[update.size() / 2];
        else {
            sort(update.begin(), update.end(), compare);
            part2 += update[update.size() / 2];
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
