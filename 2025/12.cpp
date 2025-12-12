#include <bits/stdc++.h>
using namespace std;
using num = long long;
using block = vector<vector<bool>>;

block rotate(block &b) {
    block rotated(3, vector<bool>(3, false));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) rotated[i][j] = b[3 - j - 1][i];
    }
    return rotated;
}

bool dfs(vector<vector<block>> &blocks, num rows, num cols, vector<vector<bool>> grid, vector<num> quantity) {
    for (num i = 0; i < 6; ++i) {
        num q = quantity[i];
        if (q == 0) continue;
        vector<num> nquantity = quantity;
        --nquantity[i];
        vector<block> bs = blocks[i];
        for (block b : bs) {
            for (num row = 0; row < rows - 2; ++row) {
                for (num col = 0; col < cols - 2; ++col) {
                    bool fits = true;
                    vector<vector<bool>> ngrid = grid;
                    for (num rowa = 0; rowa < 3; ++rowa) {
                        if (!fits) break;
                        for (num cola = 0; cola < 3; ++cola) {
                            if (b[rowa][cola]) {
                                if (grid[row + rowa][col + cola]) {
                                    fits = false;
                                    break;
                                } else {
                                    ngrid[row + rowa][col + cola] = true;
                                }
                            }
                        }
                    }
                    if (fits) {
                        bool success = dfs(blocks, rows, cols, ngrid, nquantity);
                        if (success) return true;
                    }
                }
            }
        }
        return false;
    }
    return true;
}

int main() {
    num part1 = 0;
    string line;
    vector<vector<block>> blocks;
    for (num i = 0; i < 6; ++i) {
        getline(cin, line);
        block b;
        for (num j = 0; j < 3; ++j) {
            getline(cin, line);
            vector<bool> row;
            for (char c : line) {
                if (c == '#') row.push_back(true);
                else row.push_back(false);
            }
            b.push_back(row);
        }
        getline(cin, line);
        block b2 = rotate(b);
        block b3 = rotate(b2);
        block b4 = rotate(b3);
        blocks.push_back({b, b2, b3, b4});
    }
    vector<num> totals;
    for (num i = 0; i < 6; ++i) {
        block b = blocks[i][0];
        num total = 0;
        for (num row = 0; row < 3; ++row) {
            for (num col = 0; col < 3; ++col) {
                 if (b[row][col]) ++total;
            }
        }
        totals.push_back(total);
    }
    while (getline(cin, line)) {
        num cols = stoll(line.substr(0, line.find('x')));
        num rows = stoll(line.substr(line.find('x') + 1, line.find(':')));
        stringstream ss(line.substr(line.find(':') + 2));
        num k;
        vector<num> quantity;
        while (ss >> k) quantity.push_back(k);
        num area = cols * rows;
        num needs = 0;
        for (num i = 0; i < quantity.size(); ++i) needs += quantity[i] * totals[i];
        if (needs <= area) {
            vector<vector<bool>> grid(rows, vector<bool>(cols, false));
            if (dfs(blocks, rows, cols, grid, quantity)) ++part1;
        }
    }
    cout << "Part 1: " << part1 << endl;
    return 0;
}
