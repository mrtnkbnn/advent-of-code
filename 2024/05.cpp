#include <bits/stdc++.h>
using namespace std;
using num = long long;

bool isInOrder(vector<num> &update, map<num, set<num>> &rules) {
    set<num> seen;
    for (num cur : update) {
        if (seen.empty()) {
            seen.insert(cur);
            continue;
        }
        for (num rule : rules[cur]) {
            if (seen.find(rule) != seen.end()) return false;
        }
        seen.insert(cur);
    }
    return true;
}

vector<num> correct(vector<num> &update, map<num, set<num>> &rules) {
    vector<num> corrected;
    for (num cur : update) {
        if (corrected.empty()) {
            corrected.push_back(cur);
            continue;
        }
        num found = LONG_LONG_MAX;
        for (num rule : rules[cur]) {
            for (num i = 0; i < corrected.size(); ++i) {
                if (corrected[i] == rule) found = min(found, i);
            }
        }
        if (found == LONG_LONG_MAX) corrected.push_back(cur);
        else corrected.insert(corrected.begin() + found, cur);
    }
    return corrected;
}

int main() {
    num part1 = 0, part2 = 0, n;
    string line;
    map<num, set<num>> rules;
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
        if (isInOrder(update, rules)) part1 += update[update.size() / 2];
        else {
            vector<num> corrected = correct(update, rules);
            part2 += corrected[corrected.size() / 2];
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
