#include <bits/stdc++.h>
using namespace std;

struct Hand {
    int red = 0, green = 0, blue = 0;
};

int main() {
    string line;
    int part1 = 0, part2 = 0;
    while (getline(cin, line)) {
        int gameNumber = stoi((line.substr(0, line.find(":"))).substr(5));
        stringstream handsStringStream(line.substr(line.find(":") + 1));
        vector<Hand> hands;
        string handString;
        while (getline(handsStringStream, handString, ';')) {
            Hand hand;
            stringstream handStringStream(handString);
            string cubeCount;
            while (getline(handStringStream, cubeCount, ',')) {
                cubeCount = cubeCount.substr(1);
                int count = stoi(cubeCount.substr(0, cubeCount.find(" ")));
                string color = cubeCount.substr(cubeCount.find(" ") + 1);
                if (color == "red") {
                    hand.red = count;
                } else if (color == "green") {
                    hand.green = count;
                } else {
                    hand.blue = count;
                }
            }
            hands.push_back(hand);
        }
        bool isPossible = true;
        int red = 0, green = 0, blue = 0;
        for (Hand &hand : hands) {
            if (hand.red > 12 || hand.green > 13 || hand.blue > 14) isPossible = false;
            red = max(red, hand.red);
            green = max(green, hand.green);
            blue = max(blue, hand.blue);
        }
        if (isPossible) part1 += gameNumber;
        part2 += (red * green * blue);
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
