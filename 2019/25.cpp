#include "intcode.hpp"

void command(intcode &prog, string cmd) {
    vector<num> input;
    for (char c : cmd) input.push_back(c);
    input.push_back(10);
    prog.run(input);
}

void print(intcode &prog) {
    for (num n : prog.output) cout << (char)n;
    prog.output = {};
}

void test(intcode prog, num pointer, vector<string> &collectAllItems) {
    if (pointer == collectAllItems.size()) {
        if (prog.halted) print(prog);
        return;
    }
    string cmd = collectAllItems[pointer];
    if (cmd[0] == 't') {
        test(prog, pointer + 1, collectAllItems);
        command(prog, cmd);
        test(prog, pointer + 1, collectAllItems);
    } else {
        command(prog, cmd);
        test(prog, pointer + 1, collectAllItems);
    }
}

int main() {
    string line;
    getline(cin, line);
    intcode prog(line);
    prog.run();
    vector<string> collectAllItems = {
        "south",
        "east",
        "take boulder",
        "west",
        "north",
        "west",
        "take hypercube",
        "west",
        "take space law space brochure",
        "west",
        "north",
        "take shell",
        "west",
        "take mug",
        "south",
        "take festive hat",
        "north",
        "east",
        "south",
        "east",
        "east",
        "east",
        "east",
        "north",
        "west",
        "north",
        "take whirled peas",
        "west",
        "west",
        "take astronaut ice cream",
        "south",
        "south"
    };
    test(prog, 0, collectAllItems);
    return 0;
}
