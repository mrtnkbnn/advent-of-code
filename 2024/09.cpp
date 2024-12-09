#include <bits/stdc++.h>
using namespace std;
using num = long long;
using block = pair<num, num>;

int main() {
    num part1 = 0, part2 = 0;
    string line;
    getline(cin, line);
    num i = 0, j = line.length() - 1, idx = 0;
    num use = line[j] - '0', free = line[i + 1] - '0';
    while (true) {
        if (i % 2 == 0) {
            num cur = line[i] - '0';
            num id = i / 2;
            while (cur--) {
                part1 += (idx * id);
                ++idx;
            }
            ++i;
        } else {
            if (free < use) {
                num id = j / 2;
                while (free--) {
                    part1 += (idx * id);
                    --use;
                    ++idx;
                }
                ++i;
                free = line[i + 1] - '0';
                if (j == i) {
                    while (use--) {
                        part1 += idx * id;
                        ++idx;
                    }
                    break;
                }
            } else {
                num id = j / 2;
                while (use--) {
                    part1 += (idx * id);
                    ++idx;
                    --free;
                }
                j -= 2;
                use = line[j] - '0';
                if (j <= i) break;
            }
        }
    }
    vector<block> init;
    for (int i = 0; i < line.length(); ++i) {
        if (i % 2 == 0) init.push_back({i / 2, line[i] - '0'});
        else init.push_back({-1, line[i] - '0'});
    }
    vector<block> mem = init;
    for (int i = init.size() - 1; i >= 0; i -= 2) {
        block file = init[i];
        num fileIdx = find(mem.begin(), mem.end(), file) - mem.begin();
        for (num freeIdx = 0; freeIdx < fileIdx; ++freeIdx) {
            if (mem[freeIdx].first == -1 && mem[freeIdx].second >= file.second) {
                mem[fileIdx] = {-1, file.second};
                mem[freeIdx] = {-1, mem[freeIdx].second - file.second};
                mem.insert(mem.begin() + freeIdx, file);
                break;
            }
        }
    }
    idx = 0;
    for (auto b : mem) {
        if (b.second != 0) {
            while (b.second--) {
                if (b.first != -1) part2 += idx * b.first;
                ++idx;
            }
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
