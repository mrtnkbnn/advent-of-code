#include <bits/stdc++.h>
using namespace std;
using num = long long;

vector<num> findGroups(string record) {
    vector<num> result;
    num current = 0;
    for (num i = 0; i < record.size(); ++i) {
        char c = record[i];
        if (c == '#') {
            ++current;
        } else {
            if (current > 0) result.push_back(current);
            current = 0;
        }
    }
    if (current > 0) result.push_back(current);
    return result;
}

vector<num> findGroupsSoFar(string record) {
    vector<num> result;
    num current = 0;
    for (num i = 0; i < record.size(); ++i) {
        char c = record[i];
        if (c == '#') {
            ++current;
        } else if (c == '?') {
            if (current > 0) result.push_back(current);
            return result;
        } else {
            if (current > 0) result.push_back(current);
            current = 0;
        }
    }
    if (current > 0) result.push_back(current);
    return result;
}

bool areEqual(vector<num> &group1, vector<num> &group2) {
    if (group1.size() != group2.size()) return false;
    for (num i = 0; i < group1.size(); ++i) {
        if (group1[i] != group2[i]) return false;
    }
    return true;
}

bool isPossible(string record, vector<num> &groups) {
    vector<num> groupsSoFar = findGroupsSoFar(record);
    if (groupsSoFar.size() > groups.size()) return false;

    if (groupsSoFar.size() == groups.size()) {
        if (groupsSoFar[groupsSoFar.size() - 1] > groups[groups.size() - 1]) return false;
        for (num i = 0; i < groups.size() - 1; ++i) {
            if (groupsSoFar[i] != groups[i]) return false;
        }
    }

    for (num i = 0; i < groupsSoFar.size(); ++i) {
        if (i != groupsSoFar.size() - 1) {
            if (groupsSoFar[i] != groups[i]) return false;
        } else {
            if (groupsSoFar[i] > groups[i]) return false;
        }
    }
    return true;
}

num count(string record, vector<num> &groups) {
    num result = 0;
    queue<string> q;
    q.push(record);
    while (!q.empty()) {
        string current = q.front();
        q.pop();
        num i = current.find_first_of('?');
        if (i == -1) {
            vector<num> currentGroups = findGroups(current);
            if (areEqual(groups, currentGroups)) ++result;
        } else {
            current[i] = '.';
            if (isPossible(current, groups)) q.push(current);
            current[i] = '#';
            if (isPossible(current, groups)) q.push(current);
        }
    }
    return result;
}

string unfold(string record, num times) {
    string unfolded = "";
    for (num i = 0; i < times; ++i) {
        if (i > 0) unfolded += '?';
        unfolded += record;
    }
    return unfolded;
}

vector<num> unfold(vector<num> &groups, num times) {
    vector<num> unfolded;
    for (num i = 0; i < times; ++i) {
        for (num n : groups) unfolded.push_back(n);
    }
    return unfolded;
}

int main() {
    num n, part1 = 0, part2 = 0;
    string record, springs;
    while (cin >> record >> springs) {
        replace(springs.begin(), springs.end(), ',', ' ');
        stringstream ss(springs);
        vector<num> groups;
        while (ss >> n) groups.push_back(n);
        string r5 = unfold(record, 5);
        vector<num> g5 = unfold(groups, 5);
        num folded = count(record, groups);
        num unfolded = count(r5, g5);
        part1 += folded;
        part2 += unfolded;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
