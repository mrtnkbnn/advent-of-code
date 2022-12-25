#include <bits/stdc++.h>
using namespace std;

long long toDecimal(string snafu) {
    long long result = 0LL;
    for (long long i = 0; i < snafu.length(); ++i) {
        char c = snafu[i];
        long long multiplier;
        if (c == '=') {
            multiplier = -2LL;
        } else if (c == '-') {
            multiplier = -1LL;
        } else {
            multiplier = c - '0';
        }
        long long exp = pow(5, snafu.length() - i - 1LL);
        result += exp * multiplier;
    }
    return result;
}

string toSnafu(long long decimal) {
    string result = "";
    while (decimal != 0) {
        int reminder = decimal % 5;
        char c = reminder + '0';
        if (reminder == 3) {
            c = '=';
            decimal += 2;
        } else if (reminder == 4) {
            c = '-';
            decimal += 1;
        }
        decimal /= 5;
        result.insert(0, 1, c);
    }
    return result;
}

int main() {
    string line;
    long long sum = 0LL;
    while (getline(cin, line)) {
        sum += toDecimal(line);
    }
    cout << "Part 1: " << toSnafu(sum) << endl;
    return 0;
}
