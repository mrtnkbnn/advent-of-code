#include <bits/stdc++.h>
using namespace std;

struct num {
    long long value;
    num* prev;
    num* next;

    num(long long _v) {
        value = _v;
    }
};

void mix(vector<num*>& nums, int N, int times) {
    for (int i = 0; i < N * times; ++i) {
        num* current = nums[i % N];
        int steps = current->value % (N - 1);
        if (steps < 0) {
            num* newNext = current;
            for (int step = 0; step < abs(steps); ++step) {
                newNext = newNext->prev;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current->next = newNext;
            current->prev = newNext->prev;
            current->next->prev = current;
            current->prev->next = current;
        } else if (steps > 0) {
            num* newPrev = current;
            for (int step = 0; step < abs(steps); ++step) {
                newPrev = newPrev->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current->prev = newPrev;
            current->next = newPrev->next;
            current->next->prev = current;
            current->prev->next = current;
        }
    }
}

int main() {
    long long cur;
    vector<num*> nums1;
    vector<num*> nums2;
    int N = 0;
    num* zero1;
    num* zero2;
    while (cin >> cur) {
        num* current1 = new num(cur);
        num* current2 = new num(cur * 811589153LL);
        nums1.push_back(current1);
        nums2.push_back(current2);
        if (N > 0) {
            nums1[N - 1]->next = current1;
            current1->prev = nums1[N - 1];
            nums2[N - 1]->next = current2;
            current2->prev = nums2[N - 1];
        }
        if (cur == 0) {
            zero1 = current1;
            zero2 = current2;
        }
        ++N;
    }
    nums1[0]->prev = nums1[nums1.size() - 1];
    nums1[nums1.size() - 1]->next = nums1[0];
    nums2[0]->prev = nums2[nums2.size() - 1];
    nums2[nums2.size() - 1]->next = nums2[0];
    mix(nums1, N, 1);
    mix(nums2, N, 10);
    int part1 = 0;
    long long part2 = 0;
    num* current1 = zero1;
    for (int i = 0; i < 3001; ++i) {
        if (i % 1000 == 0) {
            part1 += current1->value;
        }
        current1 = current1->next;
    }
    cout << "Part 1: " << part1 << endl;
    num* current2 = zero2;
    for (int i = 0; i < 3001; ++i) {
        if (i % 1000 == 0) {
            part2 += current2->value;
        }
        current2 = current2->next;
    }
    cout << "Part 2: " << part2 << endl;
    return 0;
}
