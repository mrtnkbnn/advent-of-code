#include <bits/stdc++.h>
using namespace std;
using num = long long;

num ascii(string input) {
    num result = 0;
    for (char c : input) {
        result += int(c);
        result *= 17;
        result %= 256;
    }
    return result;
}

int main() {
    num part1 = 0, part2 = 0;
    string input, step;
    getline(cin, input);
    stringstream ss(input);
    vector<vector<pair<string, num>>> boxes(256, vector<pair<string, num>>());
    while (getline(ss, step, ',')) {
        part1 += ascii(step);
        num index = step.find('=');
        if (index == -1) {
            string label = step.substr(0, step.find('-'));
            vector<pair<string, num>> &box = boxes[ascii(label)];
            for (num i = 0; i < box.size(); ++i) {
                if (box[i].first == label) {
                    box.erase(box.begin() + i);
                    break;
                }
            }
        } else {
            string label = step.substr(0, index);
            num focalLength = stoll(step.substr(index + 1));
            vector<pair<string, num>> &box = boxes[ascii(label)];
            bool replaced = false;
            for (num i = 0; i < box.size(); ++i) {
                if (box[i].first == label) {
                    box[i].second = focalLength;
                    replaced = true;
                    break;
                }
            }
            if (!replaced) box.push_back({label, focalLength});
        }
    }
    for (num i = 0; i < 256; ++i) {
        vector<pair<string, num>> box = boxes[i];
        for (int j = 0; j < box.size(); ++j) part2 += (i + 1) * (j + 1) * box[j].second;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
