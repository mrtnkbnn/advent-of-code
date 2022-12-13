#include <bits/stdc++.h>
using namespace std;

struct packet {
    int value = -1;
    vector<packet*> elements;

    packet() {
    }

    packet(int _value) {
        value = _value;
    }

    bool isValue() {
        return value != -1;
    }
};

packet* parse(string line) {
    if (line == "[]") {
        return new packet();
    } else if (line.find('[') == string::npos) {
        return new packet(stoi(line));
    } else {
        packet* listPacket = new packet();
        line = line.substr(1, line.length() - 2);
        int depth = 0;
        vector<int> commas;
        for (int i = 0; i < line.length(); ++i) {
            char c = line[i];
            if (c == ',' && depth == 0) {
                commas.push_back(i);
            } else if (c == '[') {
                ++depth;
            } else if (c == ']') {
                --depth;
            }
        }
        if (commas.size() == 0) {
            listPacket->elements.push_back(parse(line));
        } else {
            for (int i = 0; i < commas.size(); ++i) {
                if (i == 0) {
                    listPacket->elements.push_back(parse(line.substr(0, commas[i])));
                } else {
                    listPacket->elements.push_back(parse(line.substr(commas[i - 1] + 1, commas[i] - commas[i - 1] - 1)));
                }
            }
            listPacket->elements.push_back(parse(line.substr(commas[commas.size() - 1] + 1, line.length())));
        }
        return listPacket;
    }
}

int compare(packet* left, packet* right) {
    if (left->isValue() && right->isValue()) {
        if (left->value == right->value) {
            return 0;
        } else if (left->value < right->value) {
            return -1;
        } else {
            return 1;
        }
    }

    vector<packet*> leftElements;
    if (left->isValue()) {
        leftElements.push_back(left);
    } else {
        leftElements = left->elements;
    }
    vector<packet*> rightElements;
    if (right->isValue()) {
        rightElements.push_back(right);
    } else {
        rightElements = right->elements;
    }

    for (int i = 0; i < leftElements.size(); ++i) {
        if (i == rightElements.size()) {
            return 1;
        }
        int result = compare(leftElements[i], rightElements[i]);
        if (result != 0) {
            return result;
        }
    }
    if (leftElements.size() == rightElements.size()) {
        return 0;
    }
    return -1;
}

bool comparator(packet* left, packet* right) {
    return compare(left, right) == -1;
}

int main() {
    string line;
    vector<packet*> packets;
    while (getline(cin, line)) {
        if (!line.empty()) {
            packets.push_back(parse(line));
        }
    }
    int N = packets.size();
    int pair = 1, part1 = 0;
    for (int i = 0; i < N; i += 2) {
        if (comparator(packets[i], packets[i + 1])) {
            part1 += pair;
        }
        ++pair;
    }
    packet* div1 = parse("[[2]]");
    packet* div2 = parse("[[6]]");
    packets.push_back(div1);
    packets.push_back(div2);
    sort(packets.begin(), packets.end(), comparator);
    int part2 = 1;
    for (int i = 0; i < packets.size(); ++i) {
        packet* p = packets[i];
        if (p == div1 || p == div2) {
            part2 *= (i + 1);
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
