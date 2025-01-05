#include <bits/stdc++.h>
using namespace std;
using num = long long;

num part1(vector<pair<num, num>> &shuffles) {
    vector<num> deck;
    for (num i = 0; i < 10007; ++i) deck.push_back(i);
    for (auto s : shuffles) {
        if (s.first == 0) {
            reverse(deck.begin(), deck.end());
        } else if (s.first == 1) {
            if (s.second > 0) rotate(deck.begin(), deck.begin() + s.second, deck.end());
            else rotate(deck.begin(), deck.end() + s.second, deck.end());
        } else {
            vector<num> table(deck.size());
            num card = 0;
            num pointer = 0;
            while (true) {
                table[pointer] = deck[card];
                ++card;
                pointer = (pointer + s.second) % deck.size();
                if (card == deck.size()) break;
            }
            deck = table;
        }
    }
    return find(deck.begin(), deck.end(), 2019) - deck.begin();
}

int main() {
    string line;
    vector<pair<num, num>> shuffles;
    while (getline(cin, line)) {
        if (line == "deal into new stack") shuffles.push_back({0, 0});
        else {
            num n = stoll(line.substr(line.find_last_of(" ") + 1));
            if (line[0] == 'c') shuffles.push_back({1, n});
            else shuffles.push_back({2, n});
        }
    }
    cout << "Part 1: " << part1(shuffles) << endl;
    return 0;
}
