#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;

num win(coord a, coord b, coord prize) {
    num mod1 = (prize.first * b.second - b.first * prize.second) % (a.first * b.second - b.first * a.second);
    num mod2 = (prize.second * a.first - a.second * prize.first) % (b.second * a.first - a.second * b.first);
    if (mod1 != 0 || mod2 != 0) return 0;
    num x = (prize.first * b.second - b.first * prize.second) / (a.first * b.second - b.first * a.second);
    num y = (prize.second * a.first - a.second * prize.first) / (b.second * a.first - a.second * b.first);
    return 3 * x + y;
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    while (getline(cin, line)) {
        string i = line, j, k;
        getline(cin, j);
        getline(cin, k);
        getline(cin, line);
        coord a, b, prize;
        sscanf(i.c_str(), "Button A: X+%lld, Y+%lld", &a.first, &a.second);
        sscanf(j.c_str(), "Button B: X+%lld, Y+%lld", &b.first, &b.second);
        sscanf(k.c_str(), "Prize: X=%lld, Y=%lld", &prize.first, &prize.second);
        part1 += win(a, b, prize);
        part2 += win(a, b, {prize.first + 10000000000000, prize.second + 10000000000000});
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
