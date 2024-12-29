#include "intcode.hpp"
using coord = pair<num, num>;
const vector<coord> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const map<coord, num> commands = {{{-1, 0}, 1}, {{1, 0}, 2}, {{0, -1}, 3}, {{0, 1}, 4}};

pair<map<coord, num>, coord> explore(string line) {
    coord ox;
    map<coord, num> grid;
    grid[{0, 0}] = 1;
    queue<pair<coord, intcode>> q;
    q.push({{0, 0}, intcode(line)});
    while (!q.empty()) {
        auto front = q.front();
        q.pop();
        coord cur = front.first;
        for (auto dir : dirs) {
            coord next = {cur.first + dir.first, cur.second + dir.second};
            if (grid.find(next) != grid.end()) continue;
            intcode prog = front.second;
            num cmd = commands.at(dir);
            prog.run(cmd);
            num output = prog.output.back();
            grid[next] = output;
            if (output != 0) q.push({next, prog});
            if (output == 2) ox = next;
        }
    }
    return {grid, ox};
}

map<coord, num> bfs(coord start, map<coord, num> &grid) {
    map<coord, num> dist;
    queue<coord> q;
    q.push(start);
    dist[start] = 0;
    while (!q.empty()) {
        coord cur = q.front();
        q.pop();
        for (auto dir : dirs) {
            coord next = {cur.first + dir.first, cur.second + dir.second};
            if (grid.find(next) == grid.end()) continue;
            if (dist.find(next) != dist.end()) continue;
            if (grid[next] == 0) continue;
            q.push(next);
            dist[next] = dist[cur] + 1;
        }
    }
    return dist;
}

int main() {
    num part2 = LONG_LONG_MIN;
    string line;
    getline(cin, line);
    auto space = explore(line);
    auto grid = space.first;
    auto ox = space.second;
    auto dist = bfs({0, 0}, grid);
    for (auto [key, val] : bfs(ox, grid)) part2 = max(part2, val);
    cout << "Part 1: " << dist[ox] << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
