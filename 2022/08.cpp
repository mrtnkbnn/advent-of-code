#include <bits/stdc++.h>
using namespace std;

struct tree {
    bool visible;
    int score;

    tree(bool v, int s) {
        visible = v;
        score = s;
    }
};

tree* measure(vector<vector<int>> trees, int x, int y, int X, int Y) {
    bool leftVisible, rightVisible, upVisible, downVisible;
    int leftDist = 0, rightDist = 0, upDist = 0, downDist = 0;
    if (x == 0) {
        leftDist = 0;
        leftVisible = true;
    } else if (x == X - 1) {
        rightDist = 0;
        rightVisible = true;
    } else if (y == 0) {
        upDist = 0;
        upVisible = true;
    } else if (y == Y - 1) {
        downDist = 0;
        downVisible = true;
    }

    int h = trees[y][x];
    for (int i = x - 1; i >= 0; --i) {
        int cur = trees[y][i];
        ++leftDist;
        if (cur >= h) {
            leftVisible = false;
            break;
        }
    }
    for (int i = x + 1; i < X; ++i) {
        ++rightDist;
        int cur = trees[y][i];
        if (cur >= h) {
            rightVisible = false;
            break;
        }
    }

    for (int i = y - 1; i >= 0; --i) {
        ++upDist;
        int cur = trees[i][x];
        if (cur >= h) {
            upVisible = false;
            break;
        }
    }
    for (int i = y + 1; i < Y; ++i) {
        ++downDist;
        int cur = trees[i][x];
        if (cur >= h) {
            downVisible = false;
            break;
        }
    }
    return new tree(leftVisible || rightVisible || upVisible || downVisible, leftDist * rightDist * upDist * downDist);
}

int main() {
    string line;
    vector<vector<int>> trees;
    int X, Y;
    while (getline(cin, line)) {
        X = line.length();
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        trees.push_back(row);
    }
    Y = trees.size();

    int part1 = 0;
    int part2 = INT_MIN;
    for (int y = 0; y < Y; ++y) {
        for (int x = 0; x < X; ++x) {
            tree* tree = measure(trees, x, y, X, Y);
            if (tree->visible) {
                ++part1;
            }
            part2 = max(part2, tree->score);
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
