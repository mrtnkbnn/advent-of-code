#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = tuple<num, num, num>;

num find(num a, vector<num> &link) {
    while (a != link[a]) a = link[a];
    return a;
}

num add(num a, num b, vector<num> &link, vector<num> &size) {
    a = find(a, link);
    b = find(b, link);
    if (a == b) return size[a];
    if (size[a] < size[b]) swap(a, b);
    size[a] += size[b];
    link[b] = a;
    return size[a];
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    vector<coord> boxes;
    while (getline(cin, line)) {
        num x, y, z;
        sscanf(line.c_str(), "%lld,%lld,%lld", &x, &y, &z);
        boxes.push_back({x, y, z});
    }
    priority_queue<coord> dists;
    for (num i = 0; i < boxes.size(); ++i) {
        for (num j = i + 1; j < boxes.size(); ++j) {
            num dx = get<0>(boxes[i]) - get<0>(boxes[j]);
            num dy = get<1>(boxes[i]) - get<1>(boxes[j]);
            num dz = get<2>(boxes[i]) - get<2>(boxes[j]);
            num dist = dx * dx + dy * dy + dz * dz;
            dists.push({-dist, i, j});
        }
    }
    vector<num> link(boxes.size()), size(boxes.size(), 1);
    for (num i = 0; i < boxes.size(); ++i) link[i] = i;
    for (num i = 0; i < (boxes.size() == 20 ? 10 : 1000); ++i) {
        coord dist = dists.top();
        dists.pop();
        add(get<1>(dist), get<2>(dist), link, size);
    }
    vector<num> sizes;
    for (num i = 0; i < boxes.size(); ++i) {
        if (link[i] == i) sizes.push_back(size[i]);
    }
    nth_element(sizes.begin(), sizes.begin() + 3, sizes.end(), greater<num>());
    part1 = sizes[0] * sizes[1] * sizes[2];
    num i = 0;
    while (true) {
        coord dist = dists.top();
        dists.pop();
        if (add(get<1>(dist), get<2>(dist), link, size) == boxes.size()) {
            part2 = get<0>(boxes[get<1>(dist)]) * get<0>(boxes[get<2>(dist)]);
            break;
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
