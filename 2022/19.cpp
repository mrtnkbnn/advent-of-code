#include <bits/stdc++.h>
using namespace std;

struct blueprint {
    int oreRobotCost, clayRobotCost, obsidianRobotCostOre, obsidianRobotCostClay, geodeRobotCostOre, geodeRobotCostObsidian;

    blueprint(int _oreRobotCost, int _clayRobotCost, int _obsidianRobotCostOre, int _obsidianRobotCostClay, int _geodeRobotCostOre, int _geodeRobotCostObsidian) {
        oreRobotCost = _oreRobotCost;
        clayRobotCost = _clayRobotCost;
        obsidianRobotCostOre = _obsidianRobotCostOre;
        obsidianRobotCostClay = _obsidianRobotCostClay;
        geodeRobotCostOre = _geodeRobotCostOre;
        geodeRobotCostObsidian = _geodeRobotCostObsidian;
    }
};

struct state {
    int ore, clay, obsidian, geode, oreRobot = 1, clayRobot, obsidianRobot, geodeRobot;

    state collect() {
        state newState = state();
        newState.ore = ore;
        newState.clay = clay;
        newState.obsidian = obsidian;
        newState.geode = geode;
        newState.oreRobot = oreRobot;
        newState.clayRobot = clayRobot;
        newState.obsidianRobot = obsidianRobot;
        newState.geodeRobot = geodeRobot;
        newState.ore += oreRobot;
        newState.clay += clayRobot;
        newState.obsidian += obsidianRobot;
        newState.geode += geodeRobot;
        return newState;
    }
};

int calculateKey(blueprint& bp, state& s, int minute) {
   return s.ore + 10 * s.clay + 100 * s.obsidian + 1000 * s.geode + 10000 * s.oreRobot + 100000 * s.clayRobot + 1000000 * s.obsidianRobot + 10000000 * s.geodeRobot + 100000000 * minute;
}

int possibleBest(int minute, int timeLimit, int geode, int geodeRobot) {
    int result = geode;
    int step = geodeRobot;
    for (int i = 0; i < timeLimit - minute + 1; ++i) {
        result += step;
        ++step;
    }
    return result;
}

int bestKnown;

int calculate(map<int, int>& MEM, blueprint& bp, state s, int minute, int timeLimit) {
    if (minute > timeLimit) {
        bestKnown = max(bestKnown, s.geode);
        return s.geode;
    }
    if (possibleBest(minute, timeLimit, s.geode, s.geodeRobot) < bestKnown) {
        return 0;
    }
    int key = calculateKey(bp, s, minute);
    int value = MEM[key];
    if (value != 0) {
        return value;
    }
    vector<int> results;
    if (s.ore >= bp.geodeRobotCostOre && s.obsidian >= bp.geodeRobotCostObsidian) {
        state newState = s.collect();
        ++newState.geodeRobot;
        newState.ore -= bp.geodeRobotCostOre;
        newState.obsidian -= bp.geodeRobotCostObsidian;
        results.push_back(calculate(MEM, bp, newState, minute + 1, timeLimit));
    } else {
        if (s.ore >= bp.obsidianRobotCostOre && s.clay >= bp.obsidianRobotCostClay && s.obsidianRobot < bp.geodeRobotCostObsidian) {
            state newState = s.collect();
            ++newState.obsidianRobot;
            newState.ore -= bp.obsidianRobotCostOre;
            newState.clay -= bp.obsidianRobotCostClay;
            results.push_back(calculate(MEM, bp, newState, minute + 1, timeLimit));
        }
        if (s.ore >= bp.clayRobotCost && s.clayRobot < bp.obsidianRobotCostClay) {
            state newState = s.collect();
            ++newState.clayRobot;
            newState.ore -= bp.clayRobotCost;
            results.push_back(calculate(MEM, bp, newState, minute + 1, timeLimit));
        }
        int maxOre = max(bp.oreRobotCost, max(bp.clayRobotCost, max(bp.obsidianRobotCostOre, bp.geodeRobotCostOre)));
        if (s.ore >= bp.oreRobotCost && s.oreRobot < maxOre) {
            state newState = s.collect();
            ++newState.oreRobot;
            newState.ore -= bp.oreRobotCost;
            results.push_back(calculate(MEM, bp, newState, minute + 1, timeLimit));
        }
        results.push_back(calculate(MEM, bp, s.collect(), minute + 1, timeLimit));
    }
    int result = INT_MIN;
    for (int r : results) {
        result = max(result, r);
    }
    MEM[key] = result;
    return result;
}

int main() {
    vector<blueprint> blueprints;
    int blueprintNr, oreRobotCost, clayRobotCost, obsidianRobotCostOre, obsidianRobotCostClay, geodeRobotCostOre, geodeRobotCostObsidian;
    while (scanf("Blueprint %d: Each ore robot costs %d ore. Each clay robot costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot costs %d ore and %d obsidian.\n", &blueprintNr, &oreRobotCost, &clayRobotCost, &obsidianRobotCostOre, &obsidianRobotCostClay, &geodeRobotCostOre, &geodeRobotCostObsidian) != EOF) {
        blueprints.push_back(blueprint(oreRobotCost, clayRobotCost, obsidianRobotCostOre, obsidianRobotCostClay, geodeRobotCostOre, geodeRobotCostObsidian));
    }
    int part1 = 0;
    for (int i = 0; i < blueprints.size(); ++i) {
        map<int, int> MEM;
        bestKnown = 0;
        part1 += (i + 1) * calculate(MEM, blueprints[i], state(), 1, 24);
    }
    cout << "Part 1: " << part1 << endl;
    int part2 = 1;
    for (int i = 0; i < min(3, (int) blueprints.size()); ++i) {
        map<int, int> MEM;
        bestKnown = 0;
        part2 *= calculate(MEM, blueprints[i], state(), 1, 32);
    }
    cout << "Part 2: " << part2 << endl;
    return 0;
}
