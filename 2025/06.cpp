#include <bits/stdc++.h>
using namespace std;
using num = long long;

int main() {
    num part1 = 0, part2 = 0, n, cols = 0, p = 0;
    string line;
    vector<string> input;
    while (getline(cin, line)) input.push_back(line);
    vector<num> numbers, vert;
    for (num i = 0; i < input.size() - 1; ++i) {
        stringstream ss(input[i]);
        while (ss >> n) numbers.push_back(n);
    }
    stringstream ss(input[input.size() - 1]);
    char op;
    vector<char> ops;
    while (ss >> op) ops.push_back(op);
    for (num i = 0; i < ops.size(); ++i) {
        num result = ops[i] == '+' ? 0 : 1;
        for (num j = 0; j < input.size() - 1; ++j) {
            num k = i + j * ops.size();
            if (ops[i] == '+') result += numbers[k];
            else result *= numbers[k];
        }
        part1 += result;
    }
    for (auto i : input) cols = max(cols, (num)i.length());
    for (num col = 0; col < cols + 1; ++col) {
        string s = "";
        for (num row = 0; row < input.size() - 1; ++row) {
            if (input[row][col] != '+' && input[row][col] != '*') s += input[row][col];
        }
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        if (s == "" || col == cols) {
            num result = ops[p] == '+' ? 0 : 1;
            for (num k : vert) {
                if (ops[p] == '+') result += k;
                else result *= k;
            }
            part2 += result;
            vert.clear();
            ++p;
        } else {
            vert.push_back(stoll(s));
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
