#include "intcode.hpp"

pair<num, num> network(string line) {
    vector<intcode> computers;
    for (num i = 0; i < 50; ++i) {
        intcode prog(line);
        prog.run(i);
        computers.push_back(prog);
    }
    num firstY = -1, lastY = -1;
    pair<num, num> nat;
    vector<vector<pair<num, num>>> q(50);
    while (true) {
        for (num i = 0; i < 50; ++i) {
            auto packets = q[i];
            for (auto packet : packets) computers[i].run({packet.first, packet.second});
            q[i] = {};
            computers[i].run(-1);
        }
        for (num i = 0; i < 50; ++i) {
            if (!computers[i].output.empty()) {
                for (num j = 0; j < computers[i].output.size(); j += 3) {
                    num dest = computers[i].output[j];
                    num x = computers[i].output[j + 1];
                    num y = computers[i].output[j + 2];
                    if (dest == 255) {
                        nat = {x, y};
                        if (firstY == -1) firstY = y;
                    } else q[dest].push_back({x, y});
                }
                computers[i].output = {};
            }
        }
        bool idle = true;
        for (num i = 0; i < 50; ++i) {
            if (!q[i].empty()) {
                idle = false;
                break;
            }
        }
        if (idle) {
            if (lastY == nat.second) return {firstY, lastY};
            q[0].push_back(nat);
            lastY = nat.second;
        }
    }
    return {-1, -1};
}

int main() {
    string line;
    getline(cin, line);
    auto ans = network(line);
    cout << "Part 1: " << ans.first << endl;
    cout << "Part 2: " << ans.second << endl;
    return 0;
}
