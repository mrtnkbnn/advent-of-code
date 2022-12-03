#include <bits/stdc++.h>
using namespace std;

int main() {
    string line;
    vector<int> calories;
    int cur = 0;
    while (getline(cin, line)) {
        if (line.empty()) {
            calories.push_back(cur);
            cur = 0;
        } else {
            cur += stoi(line);
        }
    }
    calories.push_back(cur);
    sort(calories.begin(), calories.end(), greater());
    cout << "Part 1: " << calories[0] << endl;
    cout << "Part 2: " << calories[0] + calories[1] + calories[2] << endl;
    return 0;
}
