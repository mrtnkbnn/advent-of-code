#include <bits/stdc++.h>
using namespace std;

struct monkey {
    string name;
    long long value;
    bool isValueKnown;
    bool hadInitialValue;
    bool dependsOnHumn;
    monkey* left;
    monkey* right;
    string operation;

    monkey(string _name) {
        name = _name;
        value = 0;
        isValueKnown = false;
        hadInitialValue = false;
        dependsOnHumn = false;
    }

    monkey(string _name, long long _v) {
        name = _name;
        value = _v;
        isValueKnown = true;
        hadInitialValue = true;
        dependsOnHumn = false;
    }

    long long yell() {
        if (isValueKnown) {
            return value;
        }
        long long l = left->yell();
        long long r = right->yell();
        if (operation == "+") {
            value = l + r;
        } else if (operation == "-") {
            value = l - r;
        } else if (operation == "*") {
            value = l * r;
        } else {
            value = l / r;
        }
        isValueKnown = true;
        dependsOnHumn = left->dependsOnHumn || right->dependsOnHumn;
        return value;
    }
};

void calculateHumn(monkey* current, long long expectedResult) {
    if (current->name == "humn") {
        current->value = expectedResult;
        return;
    }
    bool leftDependsOnHumn = current->left->dependsOnHumn ? true : false;
    if (current->operation == "+") {
        if (leftDependsOnHumn) {
            long long result = current->right->yell();
            calculateHumn(current->left, expectedResult - result);
        } else {
            long long result = current->left->yell();
            calculateHumn(current->right, expectedResult - result);
        }
    } else if (current->operation == "-") {
        if (leftDependsOnHumn) {
            long long result = current->right->yell();
            calculateHumn(current->left, expectedResult + result);
        } else {
            long long result = current->left->yell();
            calculateHumn(current->right, result - expectedResult);
        }
    } else if (current->operation == "*") {
        if (leftDependsOnHumn) {
            long long result = current->right->yell();
            calculateHumn(current->left, expectedResult / result);
        } else {
            long long result = current->left->yell();
            calculateHumn(current->right, expectedResult / result);
        }
    } else {
        if (leftDependsOnHumn) {
            long long result = current->right->yell();
            calculateHumn(current->left, expectedResult * result);
        } else {
            long long result = current->left->yell();
            calculateHumn(current->right, result / expectedResult);
        }
    }
}

int main() {
    string line;
    map<string, monkey*> monkeys;
    vector<string> calculationLines;
    while (getline(cin, line)) {
        string name = line.substr(0, 4);
        if (line.length() < 17) {
            monkeys[name] = new monkey(name, stoll(line.substr(6)));
        } else {
            monkeys[name] = new monkey(name);
            calculationLines.push_back(line);
        }
    }
    monkeys["humn"]->dependsOnHumn = true;
    for (string line : calculationLines) {
        string name = line.substr(0, 4);
        string left = line.substr(6, 4);
        string right = line.substr(13);
        string operation = line.substr(11, 1);
        monkey* current = monkeys[name];
        current->left = monkeys[left];
        current->right = monkeys[right];
        current->operation = operation;
    }
    cout << "Part 1: " << monkeys["root"]->yell() << endl;
    monkey* dependsOnHumn = monkeys["root"]->left;
    long long expectedResult = monkeys["root"]->right->yell();
    if (monkeys["root"]->right->dependsOnHumn) {
        dependsOnHumn = monkeys["root"]->right;
        expectedResult = monkeys["root"]->left->yell();
    }
    calculateHumn(dependsOnHumn, expectedResult);
    cout << "Part 2: " << monkeys["humn"]->yell() << endl;
    return 0;
}
