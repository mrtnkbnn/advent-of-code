#include <bits/stdc++.h>
using namespace std;

struct monkey {
    queue<int> items;
    char operation;
    int multiplier = -1;
    int test;
    int ifTrue;
    int ifFalse;
    int inspections = 0;

    long long inspect(int item) {
        ++inspections;
        int multi = multiplier == -1 ? item : multiplier;
        if (operation == '+') {
            return item + multi;
        } else {
            return (long long) item * (long long) multi;
        }
    }

    monkey* clone() {
        monkey* m = new monkey();
        m->items = items;
        m->operation = operation;
        m->multiplier = multiplier;
        m->test = test;
        m->ifTrue = ifTrue;
        m->ifFalse = ifFalse;
        return m;
    }
};

int main() {
    vector<monkey*> monkeys1;
    vector<monkey*> monkeys2;
    string line;
    int modulo = 1;
    while (getline(cin, line)) {
        monkey* m = new monkey();
        monkeys1.push_back(m);
        string startingItems, operation, test, ifTrue, ifFalse;
        getline(cin, startingItems);
        getline(cin, operation);
        getline(cin, test);
        getline(cin, ifTrue);
        getline(cin, ifFalse);
        getline(cin, line);
        string item;
        stringstream items(startingItems.substr(18));
        while (getline(items, item, ','))  {
            m->items.push(stoi(item));
        }
        m->operation = operation.substr(23)[0];
        string multiplier = operation.substr(25);
        if (multiplier != "old") {
            m->multiplier = stoi(multiplier);
        }
        m->test = stoi(test.substr(21));
        modulo *= m->test;
        m->ifTrue = stoi(ifTrue.substr(29));
        m->ifFalse = stoi(ifFalse.substr(30));
        monkeys2.push_back(m->clone());
    }

    for (int round = 0; round < 20; ++round) {
        for (int i = 0; i < monkeys1.size(); ++i) {
            monkey* m = monkeys1[i];
            while (!m->items.empty()) {
                int item = m->items.front();
                m->items.pop();
                long long worryLevel = m->inspect(item);
                worryLevel /= 3;
                if (worryLevel % m->test == 0) {
                    monkeys1[m->ifTrue]->items.push(worryLevel);
                } else {
                    monkeys1[m->ifFalse]->items.push(worryLevel);
                }
            }
        }
    }
    for (int round = 0; round < 10000; ++round) {
        for (int i = 0; i < monkeys2.size(); ++i) {
            monkey* m = monkeys2[i];
            while (!m->items.empty()) {
                int item = m->items.front();
                m->items.pop();
                long long worryLevel = m->inspect(item);
                worryLevel %= modulo;
                if (worryLevel % m->test == 0) {
                    monkeys2[m->ifTrue]->items.push(worryLevel);
                } else {
                    monkeys2[m->ifFalse]->items.push(worryLevel);
                }
            }
        }
    }

    vector<int> inspections1;
    for (int i = 0; i < monkeys1.size(); ++i) {
        inspections1.push_back(monkeys1[i]->inspections);
    }
    vector<int> inspections2;
    for (int i = 0; i < monkeys2.size(); ++i) {
        inspections2.push_back(monkeys2[i]->inspections);
    }
    sort(inspections1.begin(), inspections1.end(), greater());
    sort(inspections2.begin(), inspections2.end(), greater());
    cout << "Part 1: " << inspections1[0] * inspections1[1] << endl;
    cout << "Part 2: " << (long long) inspections2[0] * (long long) inspections2[1] << endl;
    return 0;
}
