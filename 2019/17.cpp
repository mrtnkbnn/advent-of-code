#include "intcode.hpp"
using coord = pair<num, num>;
const vector<coord> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

num part1(string input) {
    num ans = 0;
    intcode prog(input);
    prog.run();
    vector<vector<num>> grid;
    vector<num> row;
    for (num i = 0; i < prog.output.size(); ++i) {
        if (prog.output[i] == 10) {
            if (!row.empty()) grid.push_back(row);
            row = {};
        } else {
            row.push_back(prog.output[i]);
        }
    }
    num rows = grid.size(), cols = grid[0].size();
    for (num row = 0; row < rows; ++row) {
        for (num col = 0; col < cols; ++col) {
            if (grid[row][col] != 35) continue;
            bool intersection = true;
            for (auto dir : dirs) {
                coord next = {row + dir.first, col + dir.second};
                if (next.first < 0 || next.first >= rows || next.first < 0 || next.second >= cols) {
                    intersection = false;
                    break;
                }
                if (grid[next.first][next.second] != 35) {
                    intersection = false;
                    break;
                }
            }
            if (intersection) ans += row * col;
        }
    }
    return ans;
}

num part2(string input) {
    intcode prog(input);
    prog.memory[0] = 2;
    string main = "A,B,A,C,B,A,C,B,A,C", a = "L,12,L,12,L,6,L,6", b = "R,8,R,4,L,12", c = "L,12,L,6,R,12,R,8";
    for (char cmd : main) prog.input.push_back((num)cmd);
    prog.input.push_back(10);
    for (char cmd : a) prog.input.push_back((num)cmd);
    prog.input.push_back(10);
    for (char cmd : b) prog.input.push_back((num)cmd);
    prog.input.push_back(10);
    for (char cmd : c) prog.input.push_back((num)cmd);
    prog.input.push_back(10);
    prog.input.push_back((num)'n');
    prog.input.push_back(10);
    prog.run();
    return prog.output.back();
}

int main() {
    string line;
    getline(cin, line);
    cout << "Part 1: " << part1(line) << endl;
    cout << "Part 2: " << part2(line) << endl;
    return 0;
}
