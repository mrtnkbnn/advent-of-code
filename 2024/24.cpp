#include <bits/stdc++.h>
using namespace std;
using num = long long;

struct gate {
    string left, right, output, op;
};

pair<num, bool> run(map<string, bool> values, vector<gate> gates) {
    while (true) {
        bool allFinished = true, changed = false;
        for (gate g : gates) {
            if (values.find(g.output) == values.end()) {
                if (values.find(g.left) != values.end() && values.find(g.right) != values.end()) {
                    if (g.op == "AND") values[g.output] = values[g.left] && values[g.right];
                    else if (g.op == "OR") values[g.output] = values[g.left] || values[g.right];
                    else if (g.op == "XOR") values[g.output] = values[g.left] != values[g.right];
                    changed = true;
                } else {
                    allFinished = false;
                }
            }
        }
        if (allFinished || !changed) break;
    }
    num x = 0, y = 0, z = 0;
    num nx = 0, ny = 0, nz = 0;
    string xx = "", yy = "", zz = "";
    for (auto [key, val] : values) {
        if (key[0] == 'x') {
            if (val) x += 1LL << nx;
            ++nx;
            xx.insert(0, val ? "1" : "0");
        }
        if (key[0] == 'y') {
            if (val) y += 1LL << ny;
            ++ny;
            yy.insert(0, val ? "1" : "0");
        }
        if (key[0] == 'z') {
            if (val) z += 1LL << nz;
            ++nz;
            zz.insert(0, val ? "1" : "0");
        }
    }
    return {z, (x + y) == z};
}

vector<map<string, bool>> generate() {
    vector<map<string, bool>> results;
    for (num g = 0; g < 10; ++g) {
        map<string, bool> result;
        for (num i = 0; i < 45; ++i) {
            bool xBit = rand() > (RAND_MAX / 2);
            bool yBit = rand() > (RAND_MAX / 2);
            string numeric = to_string(i);
            if (i < 10) numeric.insert(0, "0");
            string xx = "x" + numeric, yy = "y" + numeric;
            result[xx] = xBit ? 1 : 0;
            result[yy] = yBit ? 1 : 0;
        }
        results.push_back(result);
    }
    return results;
}

string test(vector<pair<string, string>> sus, map<string, bool> values, vector<gate> gates) {
    for (gate &g : gates) {
        for (num i = 0; i < sus.size(); ++i) {
            if (g.output == sus[i].first) g.output = sus[i].second;
            else if (g.output == sus[i].second) g.output = sus[i].first;
        }
    }
    if (run(values, gates).second) {
        bool mathChecksOut = true;
        for (auto toTest : generate()) {
            if (!run(toTest, gates).second) {
                mathChecksOut = false;
                break;
            }
        }
        if (mathChecksOut) {
            set<string> anss; 
            for (auto p : sus) {
                anss.insert(p.first);
                anss.insert(p.second);
            }
            string ans = "";
            for (auto s : anss) ans += s + ",";
            return ans.substr(0, ans.length() - 1);
        }
    }
    return "";
}

int main() {
    string line, part2;
    map<string, bool> values;
    while (getline(cin, line) && line != "") {
        string wire = line.substr(0, line.find(":"));
        bool value = stoi(line.substr(line.find(": " + 1)));
        values[wire] = value;
    }
    vector<gate> gates;
    vector<string> outputs;
    while (getline(cin, line)) {
        string left, right, output, op, arrow;
        stringstream ss(line);
        ss >> left >> op >> right >> arrow >> output;
        gates.push_back({left, right, output, op});
        outputs.push_back(output);
    }
    cout << "Part 1: " << run(values, gates).first << endl;
    vector<string> sus = {"gmt", "z07", "dmn", "z18", "cfk", "z35"};
    vector<pair<string, string>> pairs;
    for (num i = 0; i < outputs.size(); ++i) {
        for (num j = i + 1; j < outputs.size(); ++j) {
            if (find(sus.begin(), sus.end(), outputs[i]) == sus.end() && find(sus.begin(), sus.end(), outputs[j]) == sus.end()) {
                string ans = test({{"gmt", "z07"}, {"dmn", "z18"}, {"cfk", "z35"}, {outputs[i], outputs[j]}}, values, gates);
                if (ans != "") {
                    part2 = ans;
                }
            }
        }
    }
    cout << "Part 2: " << part2 << endl;
    return 0;
}
