#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream input("inputs/01.in");
    string line;
    set<int> calories;
    int cur = 0;
    while (getline(input, line)) {
        if (line.empty()) {
            calories.insert(cur);
            cur = 0;
        } else {
            cur += stoi(line);
        }
    }
    calories.insert(cur);
    auto it = --calories.end();
    cout << "Part 1: " << *it << endl;
    int total = *it;
    total += *(--it);
    total += *(--it);
    cout << "Part 2: " << total << endl;
    return 0;
}
