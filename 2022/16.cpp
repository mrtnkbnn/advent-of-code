#include <bits/stdc++.h>
using namespace std;

int calculateMaxPressure(string valve, int timeLeft, map<string, int>& flowRates, vector<string>& valvesWithPressure, map<pair<string, string>, int>& distances, set<string> alreadyOpen) {
    if (timeLeft < 2) {
        return 0;
    }
    if (valve != "AA") {
        alreadyOpen.insert(valve);
        --timeLeft;
    }
    int result = timeLeft * flowRates[valve];
    vector<int> results;
    for (string neighbor : valvesWithPressure) {
        if (find(alreadyOpen.begin(), alreadyOpen.end(), neighbor) == alreadyOpen.end()) {
            results.push_back(calculateMaxPressure(neighbor, timeLeft - distances[{valve, neighbor}], flowRates, valvesWithPressure, distances, alreadyOpen));
        }
    }
    int maxPath = 0;
    for (int r : results) {
        maxPath = max(r, maxPath);
    }
    return maxPath + result;
}

int main() {
    string line;
    vector<string> valves;
    map<string, int> flowRates;
    vector<string> valvesWithPressure;
    map<pair<string, string>, int> distances;
    int N = 0;
    while (getline(cin, line)) {
        string valve = line.substr(6, 2);
        valves.push_back(valve);
        int flowRate = stoi(line.substr(line.find('=') + 1, line.find(';') - line.find('=') - 1));
        flowRates.insert(make_pair(valve, flowRate));
        if (flowRate > 0) {
            valvesWithPressure.push_back(valve);
        }
        replace(line.begin(), line.end(), ',', ' ');
        stringstream ss;
        ss << line.substr(line.find(';') + 2);
        string tunnel;
        for (int i = 0; i < 4; ++i) {
            ss >> tunnel;
        }
        while (ss >> tunnel) {
            distances[{valve, tunnel}] = 1;
        }
        ++N;
    }
    for (string v1 : valves) {
        for (string v2: valves) {
            if (distances[{v1, v2}] == 0) {
                distances[{v1, v2}] = N * N;
            }
        }
    }

    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (distances[{valves[i], valves[j]}] > distances[{valves[i], valves[k]}] + distances[{valves[k], valves[j]}]) {
                    distances[{valves[i], valves[j]}] = distances[{valves[i], valves[k]}] + distances[{valves[k], valves[j]}];
                }
            }
        }
    }

    set<string> alreadyOpen;
    cout << "Part 1: " << calculateMaxPressure("AA", 30, flowRates, valvesWithPressure, distances, alreadyOpen) << endl;
    return 0;
}
