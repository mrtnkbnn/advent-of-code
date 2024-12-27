#include <bits/stdc++.h>
using namespace std;
using num = long long;

int main() {
    num part1 = 0, part2 = 0;
    string line;
    getline(cin, line);
    num pointer = 0;
    vector<vector<vector<char>>> layers;
    vector<vector<num>> counts;
    while (pointer < line.size()) {
        vector<vector<char>> layer;
        vector<num> digits(3, 0);
        for (num row = 0; row < 6; ++row) {
            vector<char> r;
            for (num col = 0; col < 25; ++col) {
                r.push_back(line[pointer]);
                ++digits[line[pointer] - '0'];
                ++pointer;
            }
            layer.push_back(r);
        }
        layers.push_back(layer);
        counts.push_back(digits);
    }
    num fewest = LONG_LONG_MAX;
    for (auto digits : counts) {
        if (digits[0] < fewest) {
            fewest = digits[0];
            part1 = digits[1] * digits[2];
        }
    }
    cout << "Part 1: " << part1 << endl;
    vector<vector<char>> image(6, vector<char>(25, ' '));
    for (num row = 0; row < 6; ++row) {
        for (num col = 0; col < 25; ++col) {
            for (auto layer : layers) {
                if (layer[row][col] != '2') {
                    image[row][col] = layer[row][col];
                    break;
                }
            }
        }
    }
    cout << "Part 2:" << endl;
    for (num row = 0; row < 6; ++row) {
        for (num col = 0; col < 25; ++col) {
            cout << (image[row][col] == '0' ? ' ' : '#');
        }
        cout << endl;
    }
    return 0;
}
