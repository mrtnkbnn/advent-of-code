#include <bits/stdc++.h>
using namespace std;
using num = long long;

struct machine {
    vector<bool> lights;
    vector<vector<num>> buttons;
    vector<num> joltage;
    num best = LONG_LONG_MAX;
};

vector<bool> toggle(vector<bool> lights, vector<num> &button) {
    for (num i : button) lights[i] = !lights[i];
    return lights;
}

num solve1(machine &m) {
    vector<bool> lights(m.lights.size(), false);
    map<vector<bool>, bool> seen;
    queue<pair<vector<bool>, num>> q;
    q.push({lights, 0});
    seen[lights] = true;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (auto button : m.buttons) {
            auto newl = toggle(cur.first, button);
            if (seen[newl]) continue;
            if (newl == m.lights) return cur.second + 1;
            q.push({newl, cur.second + 1});
            seen[newl] = true;
        }
    }
    return -1;
}

void dfs(machine &m, map<num, vector<num>> &bmap, num sum, vector<num> joltage, vector<bool> bav) {
    if (sum >= m.best) return;
    vector<tuple<num, num, num>> order;
    for (num i = 0; i < joltage.size(); ++i) {
        num jleft = m.joltage[i] - joltage[i];
        if (jleft == 0) continue;
        num useable = 0;
        for (num b : bmap[i]) {
            if (bav[b]) ++useable;
        }
        if (useable == 0) return;
        order.push_back({useable, jleft, i});
    }
    sort(order.begin(), order.end());
    if (order.empty()) {
        m.best = min(m.best, sum);
        return;
    }
    num pos = get<2>(order[0]);
    num jleft = m.joltage[pos] - joltage[pos];
    vector<bool> nbav = bav;
    vector<num> buttons;
    for (num b : bmap[pos]) {
        if (bav[b]) {
            buttons.push_back(b);
            nbav[b] = false;
        }
    }
    num vars = buttons.size();
    num summ = jleft;
    vector<num> cur(vars, 0);
    cur[vars - 1] = summ;
    while (true) {
        vector<num> newj = joltage;
        bool valid = true;
        for (num i = 0; i < cur.size(); ++i) {
            num presses = cur[i];
            if (presses == 0) continue;
            vector<num> button = m.buttons[buttons[i]];
            for (num j : button) {
                newj[j] += presses;
                if (newj[j] > m.joltage[j]) valid = false;
            }
        }
        if (valid) dfs(m, bmap, sum + jleft, newj, nbav);
        num i = vars - 2;
        while (i >= 0 && cur[i] == summ) --i;
        if (i < 0) break;
        ++cur[i];
        num used = 0;
        for (num k = 0; k <= i; ++k) used += cur[k];
        num remaining = summ - used;
        for (num k = i + 1; k < vars; ++k) cur[k] = 0;
        cur[vars - 1] = remaining;
    }
    return;
}

num solve2(machine &m) {
    vector<num> joltage(m.joltage.size(), 0);
    vector<bool> bav(m.buttons.size(), true);
    map<num, vector<num>> bmap;
    for (num i = 0; i < m.joltage.size(); ++i) {
        vector<num> b;
        for (num j = 0; j < m.buttons.size(); ++j) {
            auto button = m.buttons[j];
            if (find(button.begin(), button.end(), i) != button.end()) b.push_back(j);
        }
        bmap[i] = b;
    }
    dfs(m, bmap, 0, joltage, bav);
    return m.best;
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    vector<machine> machines;
    while (getline(cin, line)) {
        string lightss = line.substr(1, line.find(']') - 1);
        string buttonss = line.substr(line.find(']') + 2);
        buttonss = buttonss.substr(0, buttonss.find('{') - 1);
        string joltages = line.substr(line.find('{') + 1);
        joltages = joltages.substr(0, joltages.find('}'));
        vector<bool> lights;
        for (char c : lightss) {
            if (c == '#') lights.push_back(true);
            else lights.push_back(false);
        }
        vector<vector<num>> buttons;
        stringstream ss(buttonss);
        string g;
        while (getline(ss, g, ' ')) {
            g = g.substr(1, g.size() - 2);
            stringstream gg(g);
            string b;
            vector<num> buttong;
            while (getline(gg, b, ',')) buttong.push_back(stoll(b));
            buttons.push_back(buttong);
        }
        vector<num> joltage;
        ss = stringstream(joltages);
        while (getline(ss, g, ',')) joltage.push_back(stoll(g));
        machine m;
        m.lights = lights;
        m.buttons = buttons;
        m.joltage = joltage;
        machines.push_back(m);
    }
    for (machine &m : machines) {
        part1 += solve1(m);
        part2 += solve2(m);
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
