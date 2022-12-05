#include <bits/stdc++.h>
using namespace std;

int main() {
    string line;
    vector<string> lines;
    while (getline(cin, line)) {
        if (line.empty()) {
            break;
        }
        lines.push_back(line);
    }

    int N = (lines[lines.size() - 1].size() + 1) / 4;
    vector<stack<char>> stacks1(N);
    for (int i = lines.size() - 2; i >= 0; --i) {
        int s = 0;
        for (int j = 1; j < lines[i].length() - 1; j += 4) {
            char c = lines[i][j];
            if (c != ' ') {
                stacks1[s].push(c);
            }
            ++s;
        }
    }

    vector<stack<char>> stacks2 = stacks1;
    int count, from, to;
    while (getline(cin, line)) {
        sscanf(line.c_str(), "move %d from %d to %d", &count, &from, &to);
        for (int i = 0; i < count; ++i) {
            char c = stacks1[from - 1].top();
            stacks1[to - 1].push(c);
            stacks1[from - 1].pop();
        }

        stack<char> chars;
        for (int i = 0; i < count; ++i) {
            char c = stacks2[from - 1].top();
            chars.push(c);
            stacks2[from - 1].pop();
        }
        while (!chars.empty()) {
            stacks2[to - 1].push(chars.top());
            chars.pop();
        }
    }

    string part1;
    for (int i = 0; i < N; ++i) {
        part1 += stacks1[i].top();
    }
    string part2;
    for (int i = 0; i < N; ++i) {
        part2 += stacks2[i].top();
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
