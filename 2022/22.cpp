#include <bits/stdc++.h>
using namespace std;

struct instruction {
    char rotation = ' ';
    int steps = 0;

    instruction(char r) {
        rotation = r;
    }

    instruction(int s) {
        steps = s;
    }
};

int main() {
    string line;
    vector<string> lines;
    int ROWS = 0, COLS = 0;
    while (getline(cin, line)) {
        if (line.empty()) {
            break;
        }
        lines.push_back(line);
        int length = line.length();
        COLS = max(COLS, length);
    }
    ROWS = lines.size();
    vector<vector<char>> board(ROWS, vector<char>(COLS, ' '));
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (col < lines[row].length()) {
                board[row][col] = lines[row][col];
            }
        }
    }
    string instructionsString;
    getline(cin, instructionsString);
    vector<instruction> instructions;
    while (true) {
        int l = instructionsString.find('L');
        int r = instructionsString.find('R');
        if (l == r) {
            instructions.push_back(stoi(instructionsString.substr(0)));
            break;
        } else if (l < r || r == -1) {
            instructions.push_back(stoi(instructionsString.substr(0, l)));
            instructions.push_back('L');
            instructionsString = instructionsString.substr(l + 1);
        } else if (r < l || l == -1) {
            instructions.push_back(stoi(instructionsString.substr(0, r)));
            instructions.push_back('R');
            instructionsString = instructionsString.substr(r + 1);
        }
    }
    int currentRow = 0;
    int currentCol = 0;
    for (currentCol = 0; currentCol < COLS; ++currentCol) {
        if (board[0][currentCol] == '.') {
            break;
        }
    }
    int direction = 0;
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (instruction inst : instructions) {
        if (inst.rotation == 'L') {
            --direction;
            if (direction < 0) {
                direction = 3;
            }
            continue;
        } else if (inst.rotation == 'R') {
            ++direction;
            if (direction > 3) {
                direction = 0;
            }
            continue;
        }
        pair<int, int> dir = directions[direction];
        for (int step = 0; step < inst.steps; ++step) {
            int initialRow = currentRow;
            int initialCol = currentCol;
            char previous = board[currentRow][currentCol];
            while (true) {
                int row = currentRow + dir.first;
                int col = currentCol + dir.second;
                if (row < 0) {
                    row = ROWS - 1;
                }
                if (row > ROWS - 1) {
                    row = 0;
                }
                if (col < 0) {
                    col = COLS - 1;
                }
                if (col > COLS - 1) {
                    col = 0;
                }
                if (board[row][col] == '#') {
                    if (previous == ' ') {
                        currentRow = initialRow;
                        currentCol = initialCol;
                    }
                    break;
                } else if (board[row][col] == '.') {
                    previous = '.';
                    currentRow = row;
                    currentCol = col;
                    break;
                } else {
                    previous = ' ';
                    currentRow = row;
                    currentCol = col;
                }
            }
        }
    }
    int part1 = 1000 * (currentRow + 1) + 4 * (currentCol + 1) + direction;
    cout << "Part 1: " << part1 << endl;

    int N = 50;
    vector<vector<vector<char>>> cube;
    for (int row = 0; row < ROWS; row += N) {
        for (int col = 0; col < COLS; col += N) {
            if (board[row][col] != ' ') {
                vector<vector<char>> face;
                for (int i = row; i < row + N; ++i) {
                    vector<char> roww;
                    for (int j = col; j < col + N; ++j) {
                        roww.push_back(board[i][j]);
                    }
                    face.push_back(roww);
                }
                cube.push_back(face);
            }
        }
    }

    int face = 0;
    currentRow = 0, currentCol = 0, direction = 0;
    for (instruction inst : instructions) {
        if (inst.rotation == 'L') {
            --direction;
            if (direction < 0) {
                direction = 3;
            }
            continue;
        } else if (inst.rotation == 'R') {
            ++direction;
            if (direction > 3) {
                direction = 0;
            }
            continue;
        }
        for (int step = 0; step < inst.steps; ++step) {
            pair<int, int> dir = directions[direction];
            int initialRow = currentRow;
            int initialCol = currentCol;
            int initialFace = face;
            int initialDirection = direction;
            int row = currentRow + dir.first;
            int col = currentCol + dir.second;
            if (row < 0) {
                if (face == 0) {
                    face = 5;
                    direction = 0;
                    currentRow = col;
                    currentCol = 0;
                } else if (face == 1) {
                    face = 5;
                    direction = 3;
                    currentRow = N - 1;
                    currentCol = col;
                } else if (face == 2) {
                    face = 0;
                    direction = 3;
                    currentRow = N - 1;
                    currentCol = col;
                } else if (face == 3) {
                    face = 2;
                    direction = 0;
                    currentRow = col;
                    currentCol = 0;
                } else if (face == 4) {
                    face = 2;
                    direction = 3;
                    currentRow = N - 1;
                    currentCol = col;
                } else {
                    face = 3;
                    direction = 3;
                    currentRow = N - 1;
                    currentCol = col;
                }
            } else if (row > N - 1) {
                if (face == 0) {
                    face = 2;
                    direction = 1;
                    currentRow = 0;
                    currentCol = col;
                } else if (face == 1) {
                    face = 2;
                    direction = 2;
                    currentRow = col;
                    currentCol = N - 1;
                } else if (face == 2) {
                    face = 4;
                    direction = 1;
                    currentRow = 0;
                    currentCol = col;
                } else if (face == 3) {
                    face = 5;
                    direction = 1;
                    currentRow = 0;
                    currentCol = col;
                } else if (face == 4) {
                    face = 5;
                    direction = 2;
                    currentRow = col;
                    currentCol = N - 1;
                } else {
                    face = 1;
                    direction = 1;
                    currentRow = 0;
                    currentCol = col;
                }
            } else if (col < 0) {
                if (face == 0) {
                    face = 3;
                    direction = 0;
                    currentRow = N - row - 1;
                    currentCol = 0;
                } else if (face == 1) {
                    face = 0;
                    direction = 2;
                    currentRow = row;
                    currentCol = N - 1;
                } else if (face == 2) {
                    face = 3;
                    direction = 1;
                    currentRow = 0;
                    currentCol = row;
                } else if (face == 3) {
                    face = 0;
                    direction = 0;
                    currentRow = N - row - 1;
                    currentCol = 0;
                } else if (face == 4) {
                    face = 3;
                    direction = 2;
                    currentRow = row;
                    currentCol = N - 1;
                } else {
                    face = 0;
                    direction = 1;
                    currentRow = 0;
                    currentCol = row;
                }
            } else if (col > N - 1) {
                if (face == 0) {
                    face = 1;
                    direction = 0;
                    currentRow = row;
                    currentCol = 0;
                } else if (face == 1) {
                    face = 4;
                    direction = 2;
                    currentRow = N - row - 1;
                    currentCol = N - 1;
                } else if (face == 2) {
                    face = 1;
                    direction = 3;
                    currentRow = N - 1;
                    currentCol = row;
                } else if (face == 3) {
                    face = 4;
                    direction = 0;
                    currentRow = row;
                    currentCol = 0;
                } else if (face == 4) {
                    face = 1;
                    direction = 2;
                    currentRow = N - row - 1;
                    currentCol = N - 1;
                } else {
                    face = 4;
                    direction = 3;
                    currentRow = N - 1;
                    currentCol = row;
                }
            } else {
                currentRow = row;
                currentCol = col;
            }
            if (cube[face][currentRow][currentCol] == '#') {
                currentRow = initialRow;
                currentCol = initialCol;
                face = initialFace;
                direction = initialDirection;
                break;
            }
        }
    }
    if (face == 0) {
        currentCol += N;
    } else if (face == 1) {
        currentCol += N * 2;
    } else if (face == 2) {
        currentRow += N;
        currentCol += N;
    } else if (face == 3) {
        currentRow += N * 2;
        currentCol += N;
    } else if (face == 4) {
        currentRow += N * 2;
    } else if (face == 5) {
        currentRow += N * 3;
    }
    int part2 = 1000 * (currentRow + 1) + 4 * (currentCol + 1) + direction;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
