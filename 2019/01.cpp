#include <bits/stdc++.h>
using namespace std;
using num = long long;

int main() {
    num part1 = 0, part2 = 0, n;
    while (cin >> n) {
        part1 += n / 3 - 2;
        while (true) {
            n = n / 3 - 2;
            if (n <= 0) break;
            part2 += n;
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
