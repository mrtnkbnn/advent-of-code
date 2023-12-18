#include <bits/stdc++.h>
using namespace std;
using num = long long;

num hex(string input) {
    num result;
    stringstream ss;
    ss << std::hex << input;
    ss >> result;
    return result;
}

num interiour(vector<pair<num, num>> &corners) {
    num a = 0, b = 0;
    for (num i = 0; i < corners.size(); ++i) {
        a += (corners[i].first * corners[i + 1].second);
        b += (corners[i + 1].first * corners[i].second);
    }
    return abs(a - b) / 2;
}

int main() {
    string line;
    num edges = 0, actualEdges = 0;
    vector<pair<num, num>> corners = {{0, 0}};
    vector<pair<num, num>> actualCorners = {{0, 0}};
    map<char, pair<num, num>> directions = {{'U', {-1, 0}}, {'D', {1, 0}}, {'L', {0, -1}}, {'R', {0, 1}}};
    while (getline(cin, line)) {
        char dir = line[0];
        num steps = stoll(line.substr(2, line.find(" (")));
        pair<num, num> direction = directions[dir];
        pair<num, num> lastCorner = corners[corners.size() - 1];
        pair<num, num> nextCorner = {lastCorner.first + (steps * direction.first), lastCorner.second + (steps * direction.second)};
        corners.push_back(nextCorner);
        edges += steps;
        string color = line.substr(line.find(" (") + 3, 6);
        num actualSteps = hex(color.substr(0, 5));
        char lastDigit = color.substr(5, 1)[0];
        char actualDir = 'R';
        if (lastDigit == '1') actualDir = 'D';
        else if (lastDigit == '2') actualDir = 'L';
        else if (lastDigit == '3') actualDir = 'U';
        direction = directions[actualDir];
        pair<num, num> lastActualCorner = actualCorners[actualCorners.size() - 1];
        pair<num, num> nextActualCorner = {lastActualCorner.first + (actualSteps * direction.first), lastActualCorner.second + (actualSteps * direction.second)};
        actualCorners.push_back(nextActualCorner);
        actualEdges += actualSteps;
    }
    cout << "Part 1: " << interiour(corners) + edges / 2 + 1 << endl;
    cout << "Part 2: " << interiour(actualCorners) + actualEdges / 2 + 1 << endl;
    return 0;
}
