#include <bits/stdc++.h>
using namespace std;

using num = long long;

struct Map {
    num destination, source, range;
};

struct Almanac {
    vector<Map> maps;

    num convert(num input) {
        for (auto &map : maps) {
            if (input >= map.source && input <= map.source + map.range - 1) {
                return map.destination + input - map.source;
            }
        }
        return input;
    }
};

int main() {
    string line;
    getline(cin, line);
    stringstream seedStream(line.substr(7));
    vector<num> seeds;
    num n, part1 = LONG_LONG_MAX, part2 = LONG_LONG_MAX;
    while (seedStream >> n) seeds.push_back(n);
    Almanac currentAlmanac;
    vector<Almanac> almanacs;
    while (getline(cin, line)) {
        if (line != "") {
            if (line.find(":") != -1) {
                if (currentAlmanac.maps.size() > 0) almanacs.push_back(currentAlmanac);
                currentAlmanac = Almanac();
                continue;
            }
            Map map = Map();
            stringstream lineStream(line);
            lineStream >> map.destination;
            lineStream >> map.source;
            lineStream >> map.range;
            currentAlmanac.maps.push_back(map);
        }
    }
    almanacs.push_back(currentAlmanac);
    for (num seed : seeds) {
        num result = seed;
        for (auto &almanac : almanacs) result = almanac.convert(result);
        part1 = min(part1, result);
    }
    for (int i = 0; i < seeds.size(); i += 2) {
        for (num j = seeds[i]; j <= seeds[i] + seeds[i + 1] - 1; ++j) {
            num result = j;
            for (auto &almanac : almanacs) result = almanac.convert(result);
            part2 = min(part2, result);
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
