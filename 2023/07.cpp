#include <bits/stdc++.h>
using namespace std;
using num = long long;

string CARDS = "23456789TJQKA";
string CARDS_JOKER = "J23456789TQKA";

num detectType(map<char, num> &groupByCard) {
    vector<num> counts;
    for (auto count : groupByCard) counts.push_back(count.second);
    num five = 0, four = 0, three = 0, two = 0;
    for (num n : counts) {
        if (n == 5) ++five;
        else if (n == 4) ++four;
        else if (n == 3) ++three;
        else if (n == 2) ++two;
    }
    if (five == 1) return 7;
    else if (four == 1) return 6;
    else if (three == 1 && two == 1) return 5;
    else if (three == 1) return 4;
    else if (two == 2) return 3;
    else if (two == 1) return 2;
    else return 1;
}

num detectBestType(map<char, num> &groupByCard) {
    num jokers = groupByCard['J'];
    if (jokers == 5) {
        return 7;
    }
    char bestChar;
    num bestCount = 0;
    for (auto count : groupByCard) {
        if (count.first != 'J' && count.second > bestCount) {
            bestChar = count.first;
            bestCount = count.second;
        }
    }
    groupByCard[bestChar] += jokers;
    groupByCard['J'] = 0;
    return detectType(groupByCard);
}

struct Hand {
    num bid;
    num type;
    num bestType;
    vector<num> cards;
    vector<num> cardsJoker;

    Hand(string s, num b) {
        bid = b;
        map<char, num> groupByCard;
        for (num i = 0; i < 5; ++i) {
            cards.push_back(CARDS.find(s[i]));
            cardsJoker.push_back(CARDS_JOKER.find(s[i]));
            ++groupByCard[s[i]];
        }
        type = detectType(groupByCard);
        bestType = detectBestType(groupByCard);
    }
};

bool compare(Hand &hand1, Hand &hand2) {
    if (hand1.type != hand2.type) return hand1.type < hand2.type;
    for (num i = 0; i < 5; ++i) {
        if (hand1.cards[i] != hand2.cards[i]) return hand1.cards[i] < hand2.cards[i];
    }
    return hand1.bid < hand2.bid;
}

bool compareJoker(Hand &hand1, Hand &hand2) {
    if (hand1.bestType != hand2.bestType) return hand1.bestType < hand2.bestType;
    for (num i = 0; i < 5; ++i) {
        if (hand1.cardsJoker[i] != hand2.cardsJoker[i]) return hand1.cardsJoker[i] < hand2.cardsJoker[i];
    }
    return hand1.bid < hand2.bid;
}

int main() {
    string s;
    num n, part1 = 0, part2 = 0;
    vector<Hand> hands;
    while (cin >> s >> n) hands.push_back(Hand(s, n));
    sort(hands.begin(), hands.end(), compare);
    for (num i = 0; i < hands.size(); ++i) {
        part1 += (i + 1) * hands[i].bid;
    }
    sort(hands.begin(), hands.end(), compareJoker);
    for (num i = 0; i < hands.size(); ++i) {
        part2 += (i + 1) * hands[i].bid;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
