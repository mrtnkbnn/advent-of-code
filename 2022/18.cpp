#include <bits/stdc++.h>
using namespace std;

struct cube {
    int x, y, z;
    int freeSides = 6;

    cube(int _x, int _y, int _z) {
        x = _x;
        y = _y;
        z = _z;
    }
};

bool areAdjacent(cube& c1, cube& c2) {
    if (abs(c1.x - c2.x) > 1 || abs(c1.y - c2.y) > 1 || abs(c1.z - c2.z) > 1) {
        return false;
    }
    int equalCoords = 0;
    if (c1.x == c2.x) {
        ++equalCoords;
    }
    if (c1.y == c2.y) {
        ++equalCoords;
    }
    if (c1.z == c2.z) {
        ++equalCoords;
    }
    return equalCoords == 2;
}

bool isCube(vector<cube>& cubes, int x, int y, int z) {
    for (cube& c : cubes) {
        if (c.x == x && c.y == y && c.z == z) {
            return true;
        }
    }
    return false;
}

int countAdjacent(vector<cube>& cubes, cube& c1) {
    int result = 0;
    for (cube& c2 : cubes) {
        if (areAdjacent(c1, c2)) {
            ++result;
        }
    }
    return result;
}

int main() {
    int xx, yy, zz, minX = INT_MAX, minY = INT_MAX, minZ = INT_MAX, maxX = INT_MIN, maxY = INT_MIN, maxZ = INT_MIN;
    vector<cube> cubes;
    while (scanf("%d,%d,%d", &xx, &yy, &zz) != EOF) {
        cube current = cube(xx, yy, zz);
        minX = min(minX, xx);
        minY = min(minY, yy);
        minZ = min(minZ, zz);
        maxX = max(maxX, xx);
        maxY = max(maxY, yy);
        maxZ = max(maxZ, zz);
        for (cube& previous : cubes) {
            if (areAdjacent(previous, current)) {
                --previous.freeSides;
                --current.freeSides;
            }
        }
        cubes.push_back(current);
    }
    int part1 = 0;
    for (cube& c : cubes) {
        part1 += c.freeSides;
    }
    cout << "Part 1: " << part1 << endl;
    queue<cube> Q;
    --minX; --minY; --minZ; ++maxX; ++maxY; ++maxZ;
    Q.push(cube(minX, minY, minZ));
    vector<tuple<int, int, int>> visited;
    int part2 = 0;
    while (!Q.empty()) {
        cube current = Q.front();
        Q.pop();
        if (find(visited.begin(), visited.end(), make_tuple(current.x, current.y, current.z)) != visited.end()) {
            continue;
        }
        visited.push_back(make_tuple(current.x, current.y, current.z));
        if (current.x - 1 >= minX && find(visited.begin(), visited.end(), make_tuple(current.x - 1, current.y, current.z)) == visited.end() && !isCube(cubes, current.x - 1, current.y, current.z)) {
            Q.push(cube(current.x - 1, current.y, current.z));
        }
        if (current.x + 1 <= maxX && find(visited.begin(), visited.end(), make_tuple(current.x + 1, current.y, current.z)) == visited.end() && !isCube(cubes, current.x + 1, current.y, current.z)) {
            Q.push(cube(current.x + 1, current.y, current.z));
        }
        if (current.y - 1 >= minY && find(visited.begin(), visited.end(), make_tuple(current.x, current.y - 1, current.z)) == visited.end() && !isCube(cubes, current.x, current.y - 1, current.z)) {
            Q.push(cube(current.x, current.y - 1, current.z));
        }
        if (current.y + 1 <= maxY && find(visited.begin(), visited.end(), make_tuple(current.x, current.y + 1, current.z)) == visited.end() && !isCube(cubes, current.x, current.y + 1, current.z)) {
            Q.push(cube(current.x, current.y + 1, current.z));
        }
        if (current.z - 1 >= minZ && find(visited.begin(), visited.end(), make_tuple(current.x, current.y, current.z - 1)) == visited.end() && !isCube(cubes, current.x, current.y, current.z - 1)) {
            Q.push(cube(current.x, current.y, current.z - 1));
        }
        if (current.z + 1 <= maxZ && find(visited.begin(), visited.end(), make_tuple(current.x, current.y, current.z + 1)) == visited.end() && !isCube(cubes, current.x, current.y, current.z + 1)) {
            Q.push(cube(current.x, current.y, current.z + 1));
        }
        part2 += countAdjacent(cubes, current);
    }
    cout << "Part 2: " << part2 << endl;
    return 0;
}
