#include <bits/stdc++.h>
using namespace std;

struct pos {
    int x, y;

    pos(int _x, int _y) {
        x = _x;
        y = _y;
    }

    bool operator <(const pos& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

int main() {
    vector<pos> knots;
    for (int i = 0; i < 10; ++i) {
        knots.push_back(pos(0, 0));
    }
    set<pos> secondKnotPositions;
    set<pos> tailPositions;
    char dir;
    int steps;
    while (cin >> dir >> steps) {
        for (int step = 0; step < steps; ++step) {
            if (dir == 'R') {
                knots[0] = pos(knots[0].x + 1, knots[0].y);
            } else if (dir == 'L') {
                knots[0] = pos(knots[0].x - 1, knots[0].y);
            } else if (dir == 'U') {
                knots[0] = pos(knots[0].x, knots[0].y + 1);
            } else {
                knots[0] = pos(knots[0].x, knots[0].y - 1);
            }
            for (int i = 1; i < 10; ++i) {
                pos head = knots[i - 1];
                pos tail = knots[i];
                if (abs(head.x - tail.x) > 1 || abs(head.y - tail.y) > 1) {
                    if (head.x > tail.x) {
                        ++tail.x;
                    } else if (head.x < tail.x) {
                        --tail.x;
                    }
                    if (head.y > tail.y) {
                        ++tail.y;
                    } else if (head.y < tail.y) {
                        --tail.y;
                    }
                    knots[i] = pos(tail.x, tail.y);
                }
            }
            secondKnotPositions.insert(knots[1]);
            tailPositions.insert(knots[9]);
        }
    }
    cout << "Part 1: " << secondKnotPositions.size() << endl;
    cout << "Part 2: " << tailPositions.size() << endl;
    return 0;
}
