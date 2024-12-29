#include <bits/stdc++.h>
using namespace std;
using num = long long;

void fft(vector<num> &signal, vector<vector<num>> &phases) {
    vector<num> phased;
    for (num i = 0; i < signal.size(); ++i) {
        vector<num> phase = phases[i + 1];
        num pos = 1;
        num result = 0;
        for (num j = 0; j < signal.size(); ++j) {
            result += signal[j] * phase[pos];
            pos = (pos + 1) % phase.size();
        }
        phased.push_back(abs(result) % 10);
    }
    signal = phased;
}

num part1(string line) {
    num ans = 0;
    vector<num> signal;
    for (char c : line) signal.push_back(c - '0');
    vector<vector<num>> phases(signal.size() + 1);
    for (num i = 1; i <= signal.size(); ++i) {
        vector<num> phase;
        for (num j = 0; j < i; ++j) phase.push_back(0);
        for (num j = 0; j < i; ++j) phase.push_back(1);
        for (num j = 0; j < i; ++j) phase.push_back(0);
        for (num j = 0; j < i; ++j) phase.push_back(-1);
        phases[i] = phase;
    }
    for (num i = 0; i < 100; ++i) fft(signal, phases);
    for (num i = 0; i < 8; ++i) ans += signal[i] * pow(10, 7 - i);
    return ans;
}

void fft(vector<num> &signal, vector<num> &sums) {
    vector<num> phased, phasedSums;
    for (num i = 0; i < signal.size(); ++i) {
        num result = sums.back() - (i == 0 ? 0 : sums[i - 1]);
        phased.push_back(abs(result) % 10);
    }
    for (num i : phased) {
        if (phasedSums.empty()) phasedSums.push_back(i);
        else phasedSums.push_back(phasedSums.back() + i);
    }
    signal = phased;
    sums = phasedSums;
}

num part2(string line) {
    num fullLength = line.length() * 10000;
    num offset = stoll(line.substr(0, 7));
    num cycleStart = (offset / line.length()) * line.length();
    num numberOfCycles = (fullLength - cycleStart) / line.length();
    vector<num> signal, sums;
    for (num i = 0; i < numberOfCycles; ++i) {
        for (char c : line) signal.push_back(c - '0');
    }
    for (num i : signal) {
        if (sums.empty()) sums.push_back(i);
        else sums.push_back(sums.back() + i);
    }
    for (num i = 0; i < 100; ++i) fft(signal, sums);
    num startPos = offset - (cycleStart + 1) + 1;
    num ans = 0, power = 7;
    for (num i = startPos; i < startPos + 8; ++i) {
        ans += signal[i] * pow(10, power);
        --power;
    }
    return ans;
}

int main() {
    string line;
    getline(cin, line);
    cout << "Part 1: " << part1(line) << endl;
    cout << "Part 2: " << part2(line) << endl;
    return 0;
}
