#include <bits/stdc++.h>
using namespace std;

int main() {
    map<string, int> outcome_scores = {
        {"A X", 3},
        {"A Y", 6},
        {"A Z", 0},
        {"B X", 0},
        {"B Y", 3},
        {"B Z", 6},
        {"C X", 6},
        {"C Y", 0},
        {"C Z", 3},
    };
    map<char, int> shape_scores = {
        {'X', 1},
        {'Y', 2},
        {'Z', 3}
    };
    map<string, char> choose_shape {
        {"A X", 'Z'},
        {"A Y", 'X'},
        {"A Z", 'Y'},
        {"B X", 'X'},
        {"B Y", 'Y'},
        {"B Z", 'Z'},
        {"C X", 'Y'},
        {"C Y", 'Z'},
        {"C Z", 'X'}
    };
    ifstream input("inputs/02.in");
    string line;
    int part1 = 0, part2 = 0;
    while (getline(input, line)) {
        part1 += outcome_scores[line] + shape_scores[line[2]];
        char chosen_shape = choose_shape[line];
        line[2] = chosen_shape;
        part2 += outcome_scores[line] + shape_scores[chosen_shape];
    }
    cout << "Part 1: " <<  part1 << endl;
    cout << "Part 2: " <<  part2 << endl;
    return 0;
}
