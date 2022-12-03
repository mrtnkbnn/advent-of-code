#include <bits/stdc++.h>
using namespace std;

int main() {
    map<char, int> priorities;
    int priority = 1;
    for (char c = 'a'; c <= 'z'; ++c) {
        priorities[c] = priority;
        priorities[toupper(c)] = priority + 26;
        ++priority;
    }
    vector<string> lines;
    ifstream input("inputs/03.in");
    string line;
    int part1 = 0, part2 = 0;
    while (getline(input, line)) {
        lines.push_back(line);
        string compartment1 = line.substr(0, line.length()/2);
        string compartment2 = line.substr(line.length()/2);
        for (char c : compartment2) {
            if (compartment1.find(c) != string::npos) {
                part1 += priorities[c];
                break;
            }
        }
    }
    cout << "Part 1: " << part1 << endl;
    for (int i = 0; i < lines.size(); ++i) {
        string group1 = lines[i];
        string group2 = lines[++i];
        string group3 = lines[++i];
        for (char c : group3) {
            if (group1.find(c) != string::npos && group2.find(c) != string::npos) {
                part2 += priorities[c];
                break;
            }
        }
    }
    cout << "Part 2: " << part2 << endl;
    return 0;
}
