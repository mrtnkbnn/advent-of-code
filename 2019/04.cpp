#include <bits/stdc++.h>
using namespace std;
using num = long long;

int main() {
    num part1 = 0, part2 = 0;
    string line;
    getline(cin, line);
    num start = stoll(line.substr(0, line.find("-")));
    num end = stoll(line.substr(line.find("-") + 1));
    for (num i = start; i <= end; ++i) {
        vector<num> digits;
        num j = i;
        while (j > 0) {
            digits.insert(digits.begin(), j % 10);
            j /= 10;
        }
        bool adjacent = false;
        bool ascending = true;
        for (num k = 1; k < digits.size(); ++k) {
            num diff = digits[k] - digits[k - 1];
            if (diff == 0) adjacent = true;
            else if (diff < 0) {
                ascending = false;
                break;
            }
        }
        if (adjacent && ascending) ++part1;
        if (ascending) {
            adjacent = false;
            for (num k = 1; k < digits.size(); ++k) {
                num diff = digits[k] - digits[k - 1];
                if (diff == 0) {
                    bool group = false;
                    if (k - 2 >= 0) {
                        if (digits[k - 2] == digits[k]) group = true;
                    }
                    if (k + 1 < digits.size()) {
                        if (digits[k + 1] == digits[k]) group = true;
                    }
                    if (!group) adjacent = true;
                }
            }
            if (adjacent) ++part2;
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
