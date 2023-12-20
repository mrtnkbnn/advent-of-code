#include <bits/stdc++.h>
using namespace std;
using num = long long;
using Pulse = pair<pair<string, string>, bool>;

struct Module {
    string name;
    string type;
    vector<string> destinations;
    bool state = false;
    map<string, bool> memory;

    Module(string input) {
        string nameWithPrefix = input.substr(0, input.find(" -> "));
        name = nameWithPrefix;
        if (nameWithPrefix[0] == '%') {
            type = "%";
            name = nameWithPrefix.substr(1);
        } else if (nameWithPrefix[0] == '&') {
            type = "&";
            name = nameWithPrefix.substr(1);
        } else {
            type = "b";
        }
        string destinationsString = input.substr(input.find(" -> ") +4);
        while (destinationsString.find(", ") != -1) {
            string destination = destinationsString.substr(0, destinationsString.find(", "));
            destinations.push_back(destination);
            destinationsString = destinationsString.substr(destinationsString.find(", ") + 2);
        }
        destinations.push_back(destinationsString);
    }

    vector<Pulse> handle(Pulse pulse) {
        vector<Pulse> result;
        if (type == "b") {
            for (string destination : destinations) result.push_back({{name, destination}, pulse.second});
        } else if (type == "%") {
            if (!pulse.second) {
                state = !state;
                for (string destination : destinations) result.push_back({{name, destination}, state});
            }
        } else if (type == "&") {
            memory[pulse.first.first] = pulse.second;
            bool output = false;
            for (auto &it : memory) {
                if (!it.second) {
                    output = true;
                    break;
                }
            }
            for (string destination : destinations) result.push_back({{name, destination}, output});
        }
        return result;
    }

    void reset() {
        state = false;
        for (auto &it : memory) it.second = false;
    }
};

int main() {
    string line;
    map<string, Module*> modules;
    map<string, vector<string>> conjunctions;
    while (getline(cin, line)) {
        Module* module = new Module(line);
        modules[module->name] = module;
        if (module->type == "&") {
            conjunctions[module->name] = {};
        }
    }
    for (auto &it : modules) {
        for (string destination : it.second->destinations) {
            if (conjunctions.find(destination) != conjunctions.end()) {
                conjunctions[destination].push_back(it.first);
                break;
            }
        }
    }
    for (auto &it : conjunctions) {
        for (string destination : it.second) {
            modules[it.first]->memory[destination] = false;
        }
    }
    num lows = 0, highs = 0;
    for (num i = 0; i < 1000; ++i) {
        queue<Pulse> q;
        q.push({{"button", "broadcaster"}, false});
        while (!q.empty()) {
            Pulse pulse = q.front();
            q.pop();
            if (pulse.second) ++highs;
            else ++lows;
            if (modules.find(pulse.first.second) == modules.end()) continue;
            vector<Pulse> newPulses = modules[pulse.first.second]->handle(pulse);
            for (Pulse &p : newPulses) q.push(p);
        }
    }
    for (auto &it : modules) it.second->reset();
    num dc = LONG_LONG_MAX, rv = LONG_LONG_MAX, vp = LONG_LONG_MAX, cq = LONG_LONG_MAX;
    for (num i = 0; i < 10000; ++i) {
        queue<Pulse> q;
        q.push({{"button", "broadcaster"}, false});
        while (!q.empty()) {
            Pulse pulse = q.front();
            q.pop();
            if (pulse.first.first == "dc" && pulse.second) dc = min(dc, i + 1);
            if (pulse.first.first == "rv" && pulse.second) rv = min(rv, i + 1);
            if (pulse.first.first == "vp" && pulse.second) vp = min(vp, i + 1);
            if (pulse.first.first == "cq" && pulse.second) cq = min(cq, i + 1);
            if (modules.find(pulse.first.second) == modules.end()) continue;
            vector<Pulse> newPulses = modules[pulse.first.second]->handle(pulse);
            for (Pulse &p : newPulses) q.push(p);
        }
        if (dc != LONG_LONG_MAX && rv != LONG_LONG_MAX && vp != LONG_LONG_MAX && cq != LONG_LONG_MAX) break;
    }
    cout << "Part 1: " << lows * highs << endl;
    cout << "Part 2: " << lcm(1, lcm(dc, lcm(rv, lcm(vp, cq)))) << endl;
    return 0;
}
