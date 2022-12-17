#include <bits/stdc++.h>
using namespace std;

enum block { falling, stopped, air };

int findHighest(vector<vector<block>>& chamber) {
    for (int y = chamber.size() - 1; y >= 0; --y) {
        for (int x = 0; x < 7; ++x) {
            if (chamber[y][x] != air) {
                return y;
            }
        }
    }
    return -1;
}

bool canMoveSideways(int currentRockHighest, int currentRockRows, bool left, vector<vector<block>>& chamber) {
    if (left) {
        for (int y = currentRockHighest; y > currentRockHighest - currentRockRows; --y) {
            for (int x = 0; x < 7; ++x) {
                if (chamber[y][x] == falling && (x == 0 || chamber[y][x - 1] == stopped)) {
                    return false;
                }
            }
        }
        return true;
    } else {
        for (int y = currentRockHighest; y > currentRockHighest - currentRockRows; --y) {
            for (int x = 0; x < 7; ++x) {
                if (chamber[y][x] == falling && (x == 6 || chamber[y][x + 1] == stopped)) {
                    return false;
                }
            }
        }
        return true;
    }
}

void moveSideways(int currentRockHighest, int currentRockRows, bool left, vector<vector<block>>& chamber) {
    if (left) {
        for (int y = currentRockHighest; y > currentRockHighest - currentRockRows; --y) {
            for (int x = 0; x < 6; ++x) {
                if (chamber[y][x + 1] == falling) {
                    chamber[y][x] = falling;
                    chamber[y][x + 1] = air;
                }
            }
        }
    } else {
        for (int y = currentRockHighest; y > currentRockHighest - currentRockRows; --y) {
            for (int x = 6; x > 0; --x) {
                if (chamber[y][x - 1] == falling) {
                    chamber[y][x] = falling;
                    chamber[y][x - 1] = air;
                }
            }
        }
    }
}

bool canMoveDown(int currentRockHighest, int currentRockRows, vector<vector<block>>& chamber) {
    for (int y = currentRockHighest; y > currentRockHighest - currentRockRows; --y) {
        if (y == 0) {
            return false;
        }
        for (int x = 0; x < 7; ++x) {
            if (chamber[y][x] == falling && chamber[y - 1][x] == stopped) {
                return false;
            }
        }
    }
    return true;
}

void moveDown(int currentRockHighest, int currentRockRows, vector<vector<block>>& chamber) {
    for (int y = currentRockHighest - currentRockRows - 1; y < currentRockHighest; ++y) {
        for (int x = 0; x < 7; ++x) {
            if (chamber[y + 1][x] == falling) {
                chamber[y][x] = falling;
                chamber[y + 1][x] = air;
            }
        }
    }
}

void markToRest(int currentRockHighest, int currentRockRows, vector<vector<block>>& chamber) {
    for (int y = currentRockHighest; y > currentRockHighest - currentRockRows; --y) {
        for (int x = 0; x < 7; ++x) {
            if (chamber[y][x] == falling) {
                chamber[y][x] = stopped;
            }
        }
    }
}

bool isEmptyRow(int row, vector<vector<block>>& chamber) {
    for (int x = 0; x < 7; ++x) {
        if (chamber[row][x] != air) {
            return false;
        }
    }
    return true;
}

void print(vector<vector<block>>& chamber) {
    for (int y = chamber.size() - 1; y >= 0; --y) {
        for (int x = 0; x < 7; ++x) {
            char c = '.';
            if (chamber[y][x] == falling) {
                c = '@';
            } else if (chamber[y][x] == stopped) {
                c = '#';
            }
            cout << c;
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    string pattern;
    getline(cin, pattern);
    vector<vector<block>> chamber(3, vector<block>(7, air));

    vector<vector<block>> shape0;
    vector<block> shape0Row1 = {air, air, falling, falling, falling, falling, air};
    shape0.push_back(shape0Row1);

    vector<vector<block>> shape1;
    vector<block> shape1Row3 = {air, air, air, falling, air, air, air};
    vector<block> shape1Row2 = {air, air, falling, falling, falling, air, air};
    vector<block> shape1Row1 = {air, air, air, falling, air, air, air};
    shape1.push_back(shape1Row1);
    shape1.push_back(shape1Row2);
    shape1.push_back(shape1Row3);

    vector<vector<block>> shape2;
    vector<block> shape2Row3 = {air, air, air, air, falling, air, air};
    vector<block> shape2Row2 = {air, air, air, air, falling, air, air};
    vector<block> shape2Row1 = {air, air, falling, falling, falling, air, air};
    shape2.push_back(shape2Row1);
    shape2.push_back(shape2Row2);
    shape2.push_back(shape2Row3);

    vector<vector<block>> shape3;
    vector<block> shape3Row4 = {air, air, falling, air, air, air, air};
    vector<block> shape3Row3 = {air, air, falling, air, air, air, air};
    vector<block> shape3Row2 = {air, air, falling, air, air, air, air};
    vector<block> shape3Row1 = {air, air, falling, air, air, air, air};
    shape3.push_back(shape3Row1);
    shape3.push_back(shape3Row2);
    shape3.push_back(shape3Row3);
    shape3.push_back(shape3Row4);

    vector<vector<block>> shape4;
    vector<block> shape4Row2 = {air, air, falling, falling, air, air, air};
    vector<block> shape4Row1 = {air, air, falling, falling, air, air, air};
    shape4.push_back(shape4Row1);
    shape4.push_back(shape4Row2);

    int direction = 0;
    vector<vector<vector<block>>> shapes = {shape0, shape1, shape2, shape3, shape4};
    map<tuple<int, int, vector<vector<block>>>, pair<int, int>> MEM;
    int rock = 0, moreRocksUntilDone = -1, prevHeight;
    long long autoHeight;
    while (true) {
        if (moreRocksUntilDone == 0) {
            break;
        }
        int numberOfEmptyRows = 0;
        for (int y = chamber.size() - 1; y >= 0; --y) {
            if (isEmptyRow(y, chamber)) {
                ++numberOfEmptyRows;
            }
        }
        for (int i = 0; i < numberOfEmptyRows - 3; ++i) {
            chamber.pop_back();
        }

        vector<vector<block>> currentRock = shapes[rock % 5];
        for (vector<block> shapeRow : currentRock) {
            chamber.push_back(shapeRow);
        }

        int currentRockHighest = chamber.size() - 1;
        int currentRockRows = currentRock.size();
        while (true) {
            bool left = pattern[direction] == '<' ? true : false;
            direction = (direction + 1) % pattern.length();
            if (canMoveSideways(currentRockHighest, currentRockRows, left, chamber)) {
                moveSideways(currentRockHighest, currentRockRows, left, chamber);
            }
            if (canMoveDown(currentRockHighest, currentRockRows, chamber)) {
                moveDown(currentRockHighest, currentRockRows, chamber);
                --currentRockHighest;
            } else {
                markToRest(currentRockHighest, currentRockRows, chamber);
                break;
            }
        }

        if (rock == 2021) {
            cout << "Part 1: " << findHighest(chamber) + 1 << endl;
        }

        if (rock > 2021) {
            vector<vector<block>> last10Rows;
            for (int i = chamber.size() - 1; i > chamber.size() - 30; --i) {
                last10Rows.push_back(chamber[i]);
            }
            tuple<int, int, vector<vector<block>>> t = make_tuple(direction, rock % 5, last10Rows);

            if(moreRocksUntilDone == -1 && MEM.find(t) != MEM.end()) {
                pair<int, int> prev = MEM[t];
                long long cycleLength = (long long) rock - (long long) prev.first;
                long long cycleHeight = (long long) findHighest(chamber) - (long long) prev.second;
                long long rocksToDrop = 1000000000000LL - ((long long) rock + 1LL);
                long long autoCycleCount = rocksToDrop / (long long) cycleLength;
                long long autoCycleHeight = autoCycleCount * (long long) cycleHeight;
                long long rocksDropped = (long long) rock + 1LL + ((long long) autoCycleCount * (long long) cycleLength);
                autoHeight = autoCycleHeight + (long long) findHighest(chamber);
                moreRocksUntilDone = 1000000000000LL - rocksDropped + 1LL;
                prevHeight = findHighest(chamber);
            } else {
                MEM[t] = make_pair(rock, findHighest(chamber));
            }
        }
        ++rock;
        if (moreRocksUntilDone != -1) {
            --moreRocksUntilDone;
        }
    }

    long long heightToAdd = (long long) findHighest(chamber) - (long long) prevHeight + 1LL;
    cout << "Part 2: " << autoHeight + heightToAdd << endl;
    return 0;
}
