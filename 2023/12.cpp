#include <bits/stdc++.h>
using namespace std;
using num = long long;

map<tuple<string, vector<num>, num>, num> MEM;

num count(string record, vector<num> groups, num currentBlock) {
    tuple<string, vector<num>, num> key = {record, groups, currentBlock};
    if (MEM.find(key) != MEM.end()) {
        return MEM[key];
    }
    if (record.length() == 0) {
        if (currentBlock == 0 && groups.empty()) return 1;
        else if (currentBlock > 0 && groups.size() == 1 && groups[0] == currentBlock) return 1;
        else return 0;
    }
    if (record[0] == '.' && currentBlock == 0) {
        return count(record.substr(1), groups, 0);
    } else if (record[0] == '.' && currentBlock > 0) {
        if (groups.size() == 0 || groups[0] != currentBlock) {
            return 0;
        } else {
            groups.erase(groups.begin());
            return count(record.substr(1), groups, 0);
        }
    } else if (record[0] == '#') {
        if (groups.empty()) {
            return 0;
        } else if (groups[0] == currentBlock + 1 && (record.length() > 1 && record[1] == '#')) {
            return 0;
        } else if (groups[0] == currentBlock + 1 && record.length() == 1) {
            if (groups.size() == 1) {
                return 1;
            } else {
                return 0;
            }
        } else if (groups[0] == currentBlock + 1 && record.length() > 1) {
            if (record[1] == '#') {
                return 0;
            } else if (record[1] == '.') {
                groups.erase(groups.begin());
                return count(record.substr(2), groups, 0);
            } else {
                groups.erase(groups.begin());
                return count(record.substr(2), groups, 0);
            }
        } else if (currentBlock + 1 > groups[0]) {
            return 0;
        } else {

            return count(record.substr(1), groups, currentBlock + 1);
        }
    } else {
        if (!groups.empty() && groups[0] == currentBlock && currentBlock > 0) {
            groups.erase(groups.begin());
            return count(record.substr(1), groups, 0);
        } else if (!groups.empty() && currentBlock > groups[0]) {
            return 0;
        } else if (groups.empty() && currentBlock > 0) {
            return 0;
        } else if (groups.empty()) {
            return count(record.substr(1), groups, 0);
        } else {
            num a = 0;
            if (currentBlock == 0) {
                a = count(record.substr(1), groups, 0);
                MEM[{record.substr(1), groups, 0}] = a;
            }
            num b = count(record.substr(1), groups, currentBlock + 1);
            MEM[{record.substr(1), groups, currentBlock + 1}] = b;
            return a + b;
        }
    }
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
        num folded = count(record, groups, 0);
        num unfolded = count(r5, g5, 0);
        part1 += folded;
        part2 += unfolded;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
