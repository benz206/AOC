#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

typedef long long ll;

void setup() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("day6.txt", "r", stdin);
    cin.clear();
    fseek(stdin, 0, SEEK_SET);
}

void problem1() {
    vector<string> lines;
    string line;
    while (getline(cin, line)) lines.push_back(line);

    int H = (int)lines.size();
    int W = 0;
    for (auto &s : lines) W = max(W, (int)s.size());
    for (auto &s : lines) if ((int)s.size() < W) s.append(W - s.size(), ' ');

    vector<bool> isSep(W, false);
    for (int col = 0; col < W; ++col) {
        bool allSpace = true;
        for (int row = 0; row < H; ++row) {
            if (lines[row][col] != ' ') {
                allSpace = false;
                break;
            }
        }
        isSep[col] = allSpace;
    }

    ll grandTotal = 0;
    int col = 0;
    while (col < W) {
        while (col < W && isSep[col]) col++;
        if (col >= W) break;
        int L = col;
        while (col < W && !isSep[col]) col++;
        int R = col - 1;

        char op = '?';
        for (int c = L; c <= R; ++c) {
            char ch = lines[H - 1][c];
            if (ch == '+' || ch == '*') {
                op = ch;
                break;
            }
        }

        vector<ll> nums;
        for (int row = 0; row < H - 1; ++row) {
            string digits;
            for (int c = L; c <= R; ++c) {
                char ch = lines[row][c];
                if (isdigit((char)ch)) digits.push_back(ch);
            }
            if (!digits.empty()) {
                ll v = stoll(digits);
                nums.push_back(v);
            }
        }

        if (!nums.empty() && (op == '+' || op == '*')) {
            ll res;
            if (op == '+') {
                res = 0;
                for (auto v : nums) res += v;
            } else {
                res = 1;
                for (auto v : nums) res *= v;
            }
            grandTotal += res;
        }
    }

    cout << grandTotal << endl;
}

void problem2() {
    vector<string> lines;
    string line;
    while (getline(cin, line)) lines.push_back(line);

    int H = (int)lines.size();
    int W = 0;
    for (auto &s : lines) W = max(W, (int)s.size());
    for (auto &s : lines) if ((int)s.size() < W) s.append(W - s.size(), ' ');

    vector<bool> isSep(W, false);
    for (int col = 0; col < W; ++col) {
        bool allSpace = true;
        for (int row = 0; row < H; ++row) {
            if (lines[row][col] != ' ') {
                allSpace = false;
                break;
            }
        }
        isSep[col] = allSpace;
    }

    ll grandTotal = 0;
    int col = 0;
    while (col < W) {
        while (col < W && isSep[col]) col++;
        if (col >= W) break;
        int L = col;
        while (col < W && !isSep[col]) col++;
        int R = col - 1;

        char op = '?';
        for (int c = L; c <= R; ++c) {
            char ch = lines[H - 1][c];
            if (ch == '+' || ch == '*') {
                op = ch;
                break;
            }
        }

        vector<ll> nums;
        for (int c = R; c >= L; --c) {
            string digits;
            for (int row = 0; row < H - 1; ++row) {
                char ch = lines[row][c];
                if (isdigit((char)ch)) digits.push_back(ch);
            }
            if (!digits.empty()) {
                ll v = stoll(digits);
                nums.push_back(v);
            }
        }

        if (!nums.empty() && (op == '+' || op == '*')) {
            ll res;
            if (op == '+') {
                res = 0;
                for (auto v : nums) res += v;
            } else {
                res = 1;
                for (auto v : nums) res *= v;
            }
            grandTotal += res;
        }
    }

    cout << grandTotal << endl;
}

int main() {
    setup();
    problem1();
    setup();
    problem2();
    return 0;
}
