#include <bits/stdc++.h>
using namespace std;
using num = long long;

num predict(vector<num> &history, bool backwards) {
    vector<num> next;
    bool allZeros = true;
    for (num i = 0; i < history.size() - 1; ++i) {
        num n = history[i + 1] - history[i];
        if (n != 0) allZeros = false;
        next.push_back(n);
    }
    if (allZeros) return history[history.size() - 1];
    else if (backwards) return history[0] - predict(next, backwards);
    else return predict(next, backwards) + history[history.size() - 1];
}

int main() {
    string line;
    num n, part1 = 0, part2 = 0;
    while (getline(cin, line)) {
        stringstream ss(line);
        vector<num> history;
        while (ss >> n) history.push_back(n);
        part1 += predict(history, false);
        part2 += predict(history, true);
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
