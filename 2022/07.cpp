#include <bits/stdc++.h>
using namespace std;

struct dir {
    dir* parent;
    map<string, dir*> subDirs;
    vector<int> files;

    int findSize() {
        int size = 0;
        for (auto [name, subDir] : subDirs) {
            size += subDir->findSize();
        }
        for (int file : files) {
            size += file;
        }
        return size;
    }
};

int main() {
    dir* root = new dir();
    dir* current;
    string line;
    while (getline(cin, line)) {
        if (line.substr(0, 4) == "$ cd") {
            string path = line.substr(5);
            if (path == "/") {
                current = root;
            } else if (path == "..") {
                current = current->parent;
            } else {
                current = current->subDirs[path];
            }
        } else if (line.substr(0, 4) == "$ ls") {
            // ignore
        } else if (line.substr(0, 3) == "dir") {
            string dirName = line.substr(4);
            dir* subDir = new dir();
            subDir->parent = current;
            current->subDirs.insert(make_pair(dirName, subDir));
        } else {
            int pos = line.find(' ');
            int size = stoi(line.substr(0, pos));
            current->files.push_back(size);
        }
    }

    int rootDirSize = root->findSize();
    int spaceNeeded = 30000000 - (70000000 - rootDirSize);
    int part1 = 0;
    int part2 = INT_MAX;
    queue<dir*> Q;
    Q.push(root);
    while (!Q.empty()) {
        dir* cur = Q.front();
        Q.pop();
        int dirSize = cur->findSize();
        if (dirSize <= 100000) {
            part1 += dirSize;
        }
        if (dirSize >= spaceNeeded) {
            part2 = min(part2, dirSize);
        }
        for (auto [name, subDir] : cur->subDirs) {
            Q.push(subDir);
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
