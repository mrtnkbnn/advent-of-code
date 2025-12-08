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
    vector<tuple<double, num, num>> dists;
    for (num i = 0; i < boxes.size(); ++i) {
        for (num j = i + 1; j < boxes.size(); ++j) {
            num dx = get<0>(boxes[i]) - get<0>(boxes[j]);
            num dy = get<1>(boxes[i]) - get<1>(boxes[j]);
            num dz = get<2>(boxes[i]) - get<2>(boxes[j]);
            double dist = sqrt(dx * dx + dy * dy + dz * dz);
            dists.push_back({dist, i, j});
        }
    }
    sort(dists.begin(), dists.end());
    vector<num> link(boxes.size()), size(boxes.size(), 1);
    for (num i = 0; i < boxes.size(); ++i) link[i] = i;
    for (num i = 0; i < 1000; ++i) add(get<1>(dists[i]), get<2>(dists[i]), link, size);
    set<num> parents;
    for (num i = 0; i < boxes.size(); ++i) parents.insert(find(i, link));
    vector<num> sizes;
    for (num parent : parents) sizes.push_back(size[parent]);
    sort(sizes.rbegin(), sizes.rend());
    part1 = sizes[0] * sizes[1] * sizes[2];
    num i = 0;
    while (true) {
        if (add(get<1>(dists[i]), get<2>(dists[i]), link, size) == boxes.size()) {
            part2 = get<0>(boxes[get<1>(dists[i])]) * get<0>(boxes[get<2>(dists[i])]);
            break;
        }
        ++i;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
