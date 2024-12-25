#include <bits/stdc++.h>
using namespace std;
using num = long long;
const map<pair<char, char>, vector<string>> robot = {
    {{'A', 'A'}, {"A"}},
    {{'A', '^'}, {"<A"}},
    {{'A', '>'}, {"vA"}},
    {{'A', 'v'}, {"v<A", "<vA"}},
    {{'A', '<'}, {"v<<A", "<v<A"}},

    {{'^', 'A'}, {">A"}},
    {{'^', '^'}, {"A"}},
    {{'^', '>'}, {"v>A", ">vA"}},
    {{'^', 'v'}, {"vA"}},
    {{'^', '<'}, {"v<A"}},

    {{'>', 'A'}, {"^A"}},
    {{'>', '^'}, {"^<A", "<^A"}},
    {{'>', '>'}, {"A"}},
    {{'>', 'v'}, {"<A"}},
    {{'>', '<'}, {"<<A"}},

    {{'v', 'A'}, {"^>A", ">^A"}},
    {{'v', '^'}, {"^A"}},
    {{'v', '>'}, {">A"}},
    {{'v', 'v'}, {"A"}},
    {{'v', '<'}, {"<A"}},

    {{'<', 'A'}, {">>^A", ">^>A"}},
    {{'<', '^'}, {">^A"}},
    {{'<', '>'}, {">>A"}},
    {{'<', 'v'}, {">A"}},
    {{'<', '<'}, {"A"}}
};

const map<pair<char, char>, vector<string>> door = {
    {{'A', 'A'}, {"A"}},
    {{'A', '0'}, {"<A"}},
    {{'A', '1'}, {"^<<A", "<^<A"}},
    {{'A', '2'}, {"^<A", "<^A"}},
    {{'A', '3'}, {"^A"}},
    {{'A', '4'}, {"^^<<A", "^<^<A", "^<<^A", "<^^<A", "<^<^A"}},
    {{'A', '5'}, {"^^<A", "<^^A", "^<^A"}},
    {{'A', '6'}, {"^^A"}},
    {{'A', '7'}, {"^^^<<A", "^^<^<A", "^^<<^A", "^<^^<A", "^<^<^A", "^<<^^A", "<^^^<A", "<^^<^A", "<^<^^A"}},
    {{'A', '8'}, {"^^^<A", "^^<^A", "^<^^A", "<^^^A"}},
    {{'A', '9'}, {"^^^A"}},

    {{'0', 'A'}, {">A"}},
    {{'0', '0'}, {"A"}},
    {{'0', '1'}, {"^<A"}},
    {{'0', '2'}, {"^A"}},
    {{'0', '3'}, {"^>A", ">^A"}},
    {{'0', '4'}, {"^^<A", "^<^A"}},
    {{'0', '5'}, {"^^A"}},
    {{'0', '6'}, {"^^>A", "^>^A", ">^^A"}},
    {{'0', '7'}, {"^^^<A", "^^<^A", "^<^^A"}},
    {{'0', '8'}, {"^^^A"}},
    {{'0', '9'}, {"^^^>A", "^^>^A", "^>^^A", ">^^^A"}},

    {{'1', 'A'}, {">>vA", ">v>A"}},
    {{'1', '0'}, {">vA"}},
    {{'1', '1'}, {"A"}},
    {{'1', '2'}, {">A"}},
    {{'1', '3'}, {">>A"}},
    {{'1', '4'}, {"^A"}},
    {{'1', '5'}, {"^>A", ">^A"}},
    {{'1', '6'}, {"^>>A", ">^>A", ">>^A"}},
    {{'1', '7'}, {"^^A"}},
    {{'1', '8'}, {"^^>A", "^>^A", ">^^A"}},
    {{'1', '9'}, {"^^>>A", "^>^>A", "^>>^A", ">^^>A", ">^>^A", ">>^^A"}},

    {{'2', 'A'}, {"v>A", ">vA"}},
    {{'2', '0'}, {"vA"}},
    {{'2', '1'}, {"<A"}},
    {{'2', '2'}, {"A"}},
    {{'2', '3'}, {">A"}},
    {{'2', '4'}, {"^<A", "<^A"}},
    {{'2', '5'}, {"^A"}},
    {{'2', '6'}, {"^>A", ">^A"}},
    {{'2', '7'}, {"^^<A", "^<^A", "<^^A"}},
    {{'2', '8'}, {"^^A"}},
    {{'2', '9'}, {"^^>A", "^>^A", ">^^A"}},

    {{'3', 'A'}, {"vA"}},
    {{'3', '0'}, {"v<A", "<vA"}},
    {{'3', '1'}, {"<<A"}},
    {{'3', '2'}, {"<A"}},
    {{'3', '3'}, {"A"}},
    {{'3', '4'}, {"^<<A", "<^<A", "<<^A"}},
    {{'3', '5'}, {"^<A", "<^A"}},
    {{'3', '6'}, {"^A"}},
    {{'3', '7'}, {"^^<<A", "^<^<A", "^<<^A", "<^^<A", "<^<^A", "<<^^A"}},
    {{'3', '8'}, {"^^<A", "^<^A", "<^^A"}},
    {{'3', '9'}, {"^^A"}},

    {{'4', 'A'}, {">>vvA", ">v>vA", ">vv>A", "v>>vA", "v>v>A"}},
    {{'4', '0'}, {">vvA", "v>vA"}},
    {{'4', '1'}, {"vA"}},
    {{'4', '2'}, {"v>A", ">vA"}},
    {{'4', '3'}, {">>vA", ">v>A", "v>>A"}},
    {{'4', '4'}, {"A"}},
    {{'4', '5'}, {">A"}},
    {{'4', '6'}, {">>A"}},
    {{'4', '7'}, {"^A"}},
    {{'4', '8'}, {"^>A", ">^A"}},
    {{'4', '9'}, {"^>>A", ">^>A", ">>^A"}},

    {{'5', 'A'}, {"vv>A", "v>vA", ">vvA"}},
    {{'5', '0'}, {"vvA"}},
    {{'5', '1'}, {"v<A", "<vA"}},
    {{'5', '2'}, {"vA"}},
    {{'5', '3'}, {"v>A", ">vA"}},
    {{'5', '4'}, {"<A"}},
    {{'5', '5'}, {"A"}},
    {{'5', '6'}, {">A"}},
    {{'5', '7'}, {"^<A", "<^A"}},
    {{'5', '8'}, {"^A"}},
    {{'5', '9'}, {"^>A", ">^A"}},

    {{'6', 'A'}, {"vvA"}},
    {{'6', '0'}, {"vv<A", "v<vA", "<vvA"}},
    {{'6', '1'}, {"v<<A", "<v<A", "<<vA"}},
    {{'6', '2'}, {"v<A", "<vA"}},
    {{'6', '3'}, {"vA"}},
    {{'6', '4'}, {"<<A"}},
    {{'6', '5'}, {"<A"}},
    {{'6', '6'}, {"A"}},
    {{'6', '7'}, {"^<<A", "<^<A", "<<^A"}},
    {{'6', '8'}, {"^<A", "<^A"}},
    {{'6', '9'}, {"^A"}},

    {{'7', 'A'}, {">>vvvA", ">v>vvA", ">vv>vA", ">vvv>A", "v>>vvA", "v>v>vA", "v>vv>A", "vv>>vA", "vv>v>A"}},
    {{'7', '0'}, {">vvvA", "v>vvA", "vv>vA"}},
    {{'7', '1'}, {"vvA"}},
    {{'7', '2'}, {"vv>A", "v>vA", ">vvA"}},
    {{'7', '3'}, {"vv>>A", "v>v>A", "v>>vA", ">vv>A", ">v>vA", ">>vvA"}},
    {{'7', '4'}, {"vA"}},
    {{'7', '5'}, {"v>A", ">vA"}},
    {{'7', '6'}, {"v>>A", ">v>A", ">>vA"}},
    {{'7', '7'}, {"A"}},
    {{'7', '8'}, {">A"}},
    {{'7', '9'}, {">>A"}},

    {{'8', 'A'}, {"vvv>A", "vv>vA", "v>vvA", ">vvvA"}},
    {{'8', '0'}, {"vvvA"}},
    {{'8', '1'}, {"vv<A", "v<vA", "<vvA"}},
    {{'8', '2'}, {"vvA"}},
    {{'8', '3'}, {"vv>A", "v>vA", ">vvA"}},
    {{'8', '4'}, {"v<A", "<vA"}},
    {{'8', '5'}, {"vA"}},
    {{'8', '6'}, {"v>A", ">vA"}},
    {{'8', '7'}, {"<A"}},
    {{'8', '8'}, {"A"}},
    {{'8', '9'}, {">A"}},

    {{'9', 'A'}, {"vvvA"}},
    {{'9', '0'}, {"vvv<A", "vv<vA", "v<vvA", "<vvvA"}},
    {{'9', '1'}, {"vv<<A", "v<v<A", "v<<vA", "<vv<A", "<v<vA", "<<vvA"}},
    {{'9', '2'}, {"vv<A", "v<vA", "<vvA"}},
    {{'9', '3'}, {"vvA"}},
    {{'9', '4'}, {"v<<A", "<v<A", "<<vA"}},
    {{'9', '5'}, {"v<A", "<vA"}},
    {{'9', '6'}, {"vA"}},
    {{'9', '7'}, {"<<A"}},
    {{'9', '8'}, {"<A"}},
    {{'9', '9'}, {"A"}}
};


num solve(string input, num robots, map<pair<string, num>, num> &dp) {
    if (robots == 0) return input.length();
    if (dp.find({input, robots}) != dp.end()) return dp[{input, robots}];
    num ans = 0;
    for (num i = 0; i < input.length(); ++i) {
        char prev = i == 0 ? 'A' : input[i - 1];
        char cur = input[i];
        num best = LONG_LONG_MAX;
        for (string s : robot.at({prev, cur})) {
            best = min(best, solve(s, robots - 1, dp));
        }
        ans += best;
    }
    dp[{input, robots}] = ans;
    return ans;
}

vector<string> compose(string input) {
    vector<string> results;
    for (num i = 0; i < input.length(); ++i) {
        char prev = i == 0 ? 'A' : input[i - 1];
        char cur = input[i];
        vector<string> paths = door.at({prev, cur});
        if (results.empty()) {
            for (string path : paths) results.push_back(path);
        } else {
            vector<string> newResults;
            for (auto result : results) {
                for (string path : paths) newResults.push_back(result + path);
            }
            results = newResults;
        }
    }
    return results;
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    map<pair<string, num>, num> dp;
    while (getline(cin, line)) {
        num numeric = stoll(line.substr(0, line.length() - 1));
        num best1 = LONG_LONG_MAX, best2 = LONG_LONG_MAX;
        for (auto path : compose(line)) {
            best1 = min(best1, solve(path, 2, dp));
            best2 = min(best2, solve(path, 25, dp));
        }
        part1 += best1 * numeric;
        part2 += best2 * numeric;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}