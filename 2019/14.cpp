#include <bits/stdc++.h>
using namespace std;
using num = long long;

pair<string, num> parse(string input) {
    num quantity = stoll(input.substr(0, input.find(" ")));
    string chemical = input.substr(input.find(" ") + 1);
    return {chemical, quantity};
}

num calc(num fuel, map<string, vector<pair<string, num>>> &factory, map<string, num> &quantity, map<string, num> used) {
    map<string, num> needed;
    needed["FUEL"] = fuel;
    while (true) {
        if (needed.size() == 1 && needed.find("ORE") != needed.end()) break;
        vector<string> toErase;
        for (auto [key, val] : needed) {
            if (key == "ORE") continue;
            if (used[key] == 0) {
                num need = val;
                num produces = quantity[key];
                num mul = (need / produces) + (need % produces == 0 ? 0 : 1);
                for (auto p : factory[key]) {
                    needed[p.first] += p.second * mul;
                    --used[p.first];
                }
                toErase.push_back(key);
            }
        }
        for (auto s : toErase) needed.erase(s);
    }
    return needed["ORE"];
}

num trillion(map<string, vector<pair<string, num>>> &factory, map<string, num> &quantity, map<string, num> used) {
    num limit = 1000000000000;
    num lower = limit / calc(1, factory, quantity, used), upper = (limit / calc(1, factory, quantity, used)) * 2;
    while (true) {
        num fuel = (lower + upper) / 2;
        num ore = calc(fuel, factory, quantity, used);
        if (ore == limit) return fuel;
        if (ore > limit) {
            upper = fuel;
        } else {
            lower = fuel;
        }
        if (lower == upper || lower + 1 == upper) return ore > limit ? fuel - 1 : fuel;
    }
    return 0;
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    map<string, vector<pair<string, num>>> factory;
    map<string, num> quantity, used, needed;
    while (getline(cin, line)) {
        string left = line.substr(0, line.find("=>") - 1);
        string right = line.substr(line.find("=>") + 3);
        vector<pair<string, num>> inputs;
        while (left.find(", ") != string::npos) {
            inputs.push_back(parse(left.substr(0, left.find(", "))));
            left.erase(0, left.find(", ") + 2);
        }
        inputs.push_back(parse(left));
        pair<string, num> output = parse(right);
        quantity[output.first] = output.second;
        factory[output.first] = inputs;
        for (auto p : inputs) ++used[p.first];
    }
    cout << "Part 1: " << calc(1, factory, quantity, used) << endl;
    cout << "Part 2: " << trillion(factory, quantity, used) << endl;
    return 0;
}
