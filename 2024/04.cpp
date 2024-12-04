#include <bits/stdc++.h>
using namespace std;
using num = long long;

num xmas(vector<vector<char>> &search, num row, num col, num rows, num cols) {
    if (search[row][col] != 'X') return 0;
    num result = 0;
    for (num rowD = -1; rowD < 2; ++rowD) {
        for (num colD = -1; colD < 2; ++colD) {
            if (rowD == 0 && colD == 0 || rowD == -1 && row < 3 || rowD == 1 && row > rows - 4 || colD == -1 && col < 3 || colD == 1 && col > cols - 4) continue;
            else {
                bool xmas = true;
                for (num c = 1; c < 4; ++c) {
                    if (search[row + c * rowD][col + c * colD] != "XMAS"[c]) {
                        xmas = false;
                        break;
                    }
                }
                if (xmas) ++result;
            }
        }
    }
    return result;
}

num mas(vector<vector<char>> &search, num row, num col, num rows, num cols) {
    if (search[row][col] != 'A' || row < 1 || col < 1 || row > rows - 2 || col > cols - 2) return 0;
    bool l = false, r = false;
    if (search[row - 1][col - 1] == 'M' && search[row + 1][col + 1] == 'S' || search[row - 1][col - 1] == 'S' && search[row + 1][col + 1] == 'M') l = true;
    if (search[row - 1][col + 1] == 'M' && search[row + 1][col - 1] == 'S' || search[row - 1][col + 1] == 'S' && search[row + 1][col - 1] == 'M') r = true;
    return l == true && r == true ? 1 : 0;
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    vector<vector<char>> search;
    while (getline(cin, line)) {
        search.push_back(vector<char>(line.begin(), line.end()));
    }
    num rows = search.size();
    num cols = search[0].size();
    for (num row = 0; row < rows; ++row) {
        for (num col = 0; col < cols; ++col) {
            part1 += xmas(search, row, col, rows, cols);
            part2 += mas(search, row, col, rows, cols);
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
