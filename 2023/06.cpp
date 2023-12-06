#include <bits/stdc++.h>
using namespace std;

using num = long long;

int main() {
    string line;
    num n, part1 = 0, part2 = 0;
    vector<num> times, distances;
    getline(cin, line);
    string timesString = line.substr(5);
    stringstream timesStream(timesString);
    while (timesStream >> n) times.push_back(n);
    getline(cin, line);
    string distancesString = line.substr(9);
    stringstream distancesStream(distancesString);
    while (distancesStream >> n) distances.push_back(n);
    for (num i = 0; i < times.size(); ++i) {
        num wins = 0;
        for (num j = 0; j <= times[i]; ++j) {
            num score = (times[i] - j) * j;
            if (score > distances[i]) ++wins;
        }
        if (part1 == 0) part1 = wins;
        else part1 *= wins;
    }
    timesString.erase(remove(timesString.begin(), timesString.end(), ' '), timesString.end());
    distancesString.erase(remove(distancesString.begin(), distancesString.end(), ' '), distancesString.end());
    num time = stoll(timesString);
    num distance = stoll(distancesString);
    for (num i = 0; i <= time; ++i) {
        num score = (time - i) * i;
        if (score > distance) ++part2;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
