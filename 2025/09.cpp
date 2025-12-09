#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;
vector<coord> dirs = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

pair<vector<num>, map<num, num>> compress(vector<num> input) {
    set<num> uq = {0, LONG_LONG_MAX};
    for (num i : input) uq.insert(i);
    num p = 0;
    vector<num> original;
    map<num, num> compressed;
    for (num i : uq) {
        original.push_back(i);
        compressed[i] = p;
        ++p;
    }
    return {original, compressed};
}

bool hits(coord tile, vector<coord> tiles) {
    for (num i = 0; i < tiles.size(); ++i) {
        num j = i == tiles.size() - 1 ? 0 : i + 1;
        coord left = tiles[i], right = tiles[j];
        if (left.first == right.first && right.first == tile.first) {
            if (tile.second >= min(left.second, right.second) && tile.second <= max(left.second, right.second)) return true;
        } else if (left.second == right.second && right.second == tile.second) {
            if (tile.first >= min(left.first, right.first) && tile.first <= max(left.first, right.first)) return true;
        }
    }
    return false;
}

bool allin(coord c1, coord c2, vector<vector<bool>> &outside) {
    for (num y = min(c1.second, c2.second); y <= max(c1.second, c2.second); ++y) {
        for (num x = min(c1.first, c2.first); x <= max(c1.first, c2.first); ++x) {
            if (outside[y][x]) return false;
        }
    }
    return true;
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    vector<coord> tiles, compressedTiles;
    vector<num> allX, allY;
    while (getline(cin, line)) {
        num x = stoll(line.substr(0, line.find(',')));
        num y = stoll(line.substr(line.find(',') + 1));
        tiles.push_back({x, y});
        allX.push_back(x);
        allY.push_back(y);
    }
    auto xcompress = compress(allX);
    auto ycompress = compress(allY);
    for (coord tile : tiles) compressedTiles.push_back({xcompress.second[tile.first], ycompress.second[tile.second]});
    vector<vector<bool>> outside(ycompress.first.size(), vector<bool>(xcompress.first.size(), false));
    vector<vector<bool>> visited(ycompress.first.size(), vector<bool>(xcompress.first.size(), false));
    queue<coord> q;
    q.push({0, 0});
    outside[0][0] = true;
    visited[0][0] = true;
    while (!q.empty()) {
        coord cur = q.front();
        q.pop();
        for (coord dir : dirs) {
            coord next = {cur.first + dir.first, cur.second + dir.second};
            if (next.first < 0 || next.first >= ycompress.first.size() || next.second < 0 || next.second >= xcompress.first.size()) continue;
            if (visited[next.second][next.first]) continue;
            if (hits(next, compressedTiles)) continue;
            outside[next.second][next.first] = true;
            visited[next.second][next.first] = true;
            q.push(next);
        }
    }
    for (num i = 0; i < compressedTiles.size(); ++i) {
        for (num j = i + 1; j < compressedTiles.size(); ++j) {
            coord c1 = compressedTiles[i], c2 = compressedTiles[j];
            num x1 = xcompress.first[c1.first];
            num y1 = ycompress.first[c1.second];
            num x2 = xcompress.first[c2.first];
            num y2 = ycompress.first[c2.second];
            num area = (abs(x1 - x2) + 1) * (abs(y1 - y2) + 1);
            part1 = max(part1, area);
            if (area > part2 && allin(c1, c2, outside)) part2 = area;
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
