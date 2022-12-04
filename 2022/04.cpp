#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c, d, part1 = 0, part2 = 0;
    while (scanf("%d-%d,%d-%d", &a, &b, &c, &d) != EOF) {
        if ((a >= c && b <= d) || (c >= a && d <= b)) {
            ++part1;
        }
        if ((b >= c && a <= d) || (d >= a && c <= b)) {
            ++part2;
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
