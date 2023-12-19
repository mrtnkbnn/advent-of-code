#include <bits/stdc++.h>
using namespace std;
using num = long long;

struct Rule {
    bool acceptAll = false;
    bool rejectAll = false;
    num applyOnIndex = -1;
    char condition = ' ';
    num limit = -1;
    string destination;

    Rule(string ruleString) {
        if (ruleString == "A") {
            acceptAll = true;
        } else if (ruleString == "R") {
            rejectAll = true;
        } else {
            if (ruleString.find(":") == -1) {
                destination = ruleString;
            } else {
                string xmas = "xmas";
                applyOnIndex = xmas.find(ruleString[0]);
                condition = ruleString[1];
                string rulePart = ruleString.substr(2);
                limit = stoll(rulePart.substr(0, rulePart.find(":")));
                destination = ruleString.substr(ruleString.find(":") + 1);
            }
        }
    }

    string apply(vector<num> part) {
        if (acceptAll) {
            return "A";
        } else if (rejectAll) {
            return "R";
        } else {
            num value = part[applyOnIndex];
            if (condition == '<') {
                if (value < limit) return destination;
                else return "N";
            } else if (condition == '>') {
                if (value > limit) return destination;
                else return "N";
            } else if (condition == ' ') {
                return destination;
            } else {
                return "N";
            }
        }
    }
};

num combinations(map<string, vector<Rule>> &workflows, string currentWorkflow, num ruleIndex, vector<pair<num, num>> ranges) {
    if (currentWorkflow == "A") {
        num result = 1;
        for (num i = 0; i < 4; ++i) result *= (ranges[i].second - ranges[i].first);
        return result;
    } else if (currentWorkflow == "R") {
        return 0;
    }
    Rule rule = workflows[currentWorkflow][ruleIndex];
    if (rule.acceptAll) {
        num result = 1;
        for (num i = 0; i < 4; ++i) result *= (ranges[i].second - ranges[i].first);
        return result;
    } else if (rule.rejectAll) {
        return 0;
    } else {
        if (rule.condition == ' ') {
            return combinations(workflows, rule.destination, 0, ranges);
        } else if (rule.condition == '<') {
            if (ranges[rule.applyOnIndex].second <= rule.limit) {
                return combinations(workflows, rule.destination, 0, ranges);
            } else if (ranges[rule.applyOnIndex].first >= rule.limit) {
                return combinations(workflows, currentWorkflow, ruleIndex + 1, ranges);
            } else {
                pair<num, num> leftRange = {ranges[rule.applyOnIndex].first, rule.limit};
                pair<num, num> rightRange = {rule.limit, ranges[rule.applyOnIndex].second};
                vector<pair<num, num>> leftRanges = ranges;
                vector<pair<num, num>> rightRanges = ranges;
                leftRanges[rule.applyOnIndex] = leftRange;
                rightRanges[rule.applyOnIndex] = rightRange;
                return combinations(workflows, rule.destination, 0, leftRanges) + combinations(workflows, currentWorkflow, ruleIndex + 1, rightRanges);
            }
        } else if (rule.condition == '>') {
            if (ranges[rule.applyOnIndex].first > rule.limit) {
                return combinations(workflows, rule.destination, 0, ranges);
            } else if (ranges[rule.applyOnIndex].second <= rule.limit + 1) {
                return combinations(workflows, currentWorkflow, ruleIndex + 1, ranges);
            } else {
                pair<num, num> leftRange = {ranges[rule.applyOnIndex].first, rule.limit + 1};
                pair<num, num> rightRange = {rule.limit + 1, ranges[rule.applyOnIndex].second};
                vector<pair<num, num>> leftRanges = ranges;
                vector<pair<num, num>> rightRanges = ranges;
                leftRanges[rule.applyOnIndex] = leftRange;
                rightRanges[rule.applyOnIndex] = rightRange;
                return combinations(workflows, currentWorkflow, ruleIndex + 1, leftRanges) + combinations(workflows, rule.destination, 0, rightRanges);
            }
        }
    }
    return 0;
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    map<string, vector<Rule>> workflows;
    while (getline(cin, line)) {
        if (line == "") break;
        string workflowName = line.substr(0, line.find("{"));
        string rulesPart = line.substr(line.find("{") + 1);
        string allRules = rulesPart.substr(0, rulesPart.length() - 1);
        stringstream ss(allRules);
        string ruleString;
        workflows[workflowName] = {};
        while (getline(ss, ruleString, ',')) workflows[workflowName].push_back(Rule(ruleString));
    }
    while (getline(cin, line)) {
        replace(line.begin(), line.end(), 'x', ' ');
        replace(line.begin(), line.end(), 'm', ' ');
        replace(line.begin(), line.end(), 'a', ' ');
        replace(line.begin(), line.end(), 's', ' ');
        replace(line.begin(), line.end(), '{', ' ');
        replace(line.begin(), line.end(), '}', ' ');
        replace(line.begin(), line.end(), '=', ' ');
        replace(line.begin(), line.end(), ',', ' ');
        stringstream ss(line);
        num category;
        vector<num> part(4, 0);
        for (num i = 0; i < 4; ++i) ss >> part[i];
        string result;
        string currentWork = "in";
        while (true) {
            vector<Rule> rules = workflows[currentWork];
            for (Rule &rule : rules) {
                string ruleResult = rule.apply(part);
                if (ruleResult == "A") {
                    result = "A";
                    break;
                } else if (ruleResult == "R") {
                    result = "R";
                    break;
                } else if (ruleResult == "N") {
                    continue;
                } else {
                    currentWork = ruleResult;
                    break;
                }
            }
            if (result == "A" || result == "R") break;
        }
        if (result == "A") part1 += reduce(part.begin(), part.end());
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << combinations(workflows, "in", 0, {{1, 4001}, {1, 4001}, {1, 4001}, {1, 4001}}) << endl;
    return 0;
}
