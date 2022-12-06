#include <bits/stdc++.h>
using namespace std;

int find(string input, int len) {
    for (int i = 0; i < input.length() - len; ++i) {
        string sub = input.substr(i, len);
        set<char> chars(sub.begin(), sub.end());
        if (chars.size() == len) {
            return i + len;
        }
    }
    throw invalid_argument("Start-of-packet marker not found");
}

int main() {
    string input;
    getline(cin, input);
    cout << "Part 1: " << find(input, 4) << endl;
    cout << "Part 2: " << find(input, 14) << endl;
    return 0;
}
