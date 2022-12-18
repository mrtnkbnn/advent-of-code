#include <bits/stdc++.h>
using namespace std;

int findPaths(string valve, int timeLeft, int currentScore, map<string, int>& flowRates, vector<string>& valvesWithPressure, map<pair<string, string>, int>& distances, vector<string> path, map<vector<string>, int>& paths) {
    if (timeLeft < 2) {
        return 0;
    }
    if (valve != "AA") {
        path.push_back(valve);
        --timeLeft;
    }
    int result = timeLeft * flowRates[valve];
    if (valve != "AA") {
        currentScore += result;
        paths[path] = currentScore;
    }
    vector<int> results;
    for (string neighbor : valvesWithPressure) {
        if (find(path.begin(), path.end(), neighbor) == path.end()) {
            int calculated = findPaths(neighbor, timeLeft - distances[{valve, neighbor}], currentScore, flowRates, valvesWithPressure, distances, path, paths);

            results.push_back(calculated);
        }
    }
    int maxPath = 0;
    for (int r : results) {
        maxPath = max(r, maxPath);
    }
    return maxPath + result;
}

bool overlap(vector<string>& path1, vector<string>& path2) {
    for (string s : path1) {
        if (find(path2.begin(), path2.end(), s) != path2.end()) {
            return true;
        }
    }
    return false;
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

    vector<string> path1;
    map<vector<string>, int> paths1;
    cout << "Part 1: " << findPaths("AA", 30, 0, flowRates, valvesWithPressure, distances, path1, paths1) << endl;
    vector<string> path2;
    map<vector<string>, int> paths2;
    findPaths("AA", 26, 0, flowRates, valvesWithPressure, distances, path2, paths2);
    int part2 = 0;
    for (auto &it1 : paths2) {
        vector<string> first = it1.first;
        for (auto &it2 : paths2) {
            vector<string> second = it2.first;
            if (!overlap(first, second)) {
                part2 = max(part2, it1.second + it2.second);
            }
        }
    }
    cout << "Part 2: " << part2 << endl;
    return 0;
}
