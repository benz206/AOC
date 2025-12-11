#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cctype>
#include <numeric>
#include <queue>
#include <unordered_map>

using namespace std;

void setup() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("day10.txt", "r", stdin);
    cin.clear();
    fseek(stdin, 0, SEEK_SET);
}

void problem1() {
    string line;
    long long total = 0;

    // read each machine, one per line
    while (getline(cin, line)) {
        if (line.empty()) continue;
        bool allSpace = true;
        for (char ch : line) {
            if (!isspace(static_cast<unsigned char>(ch))) {
                allSpace = false;
                break;
            }
        }
        if (allSpace) continue;

        // parse indicator pattern inside [...]
        size_t lb = line.find('[');
        size_t rb = line.find(']', lb + 1);
        if (rb == string::npos) continue;

        string pattern = line.substr(lb + 1, rb - lb - 1);
        int nLights = (int)pattern.size();

        // find { to know where button list ends
        size_t lcurly = line.find('{', rb + 1);
        if (lcurly == string::npos) lcurly = line.size();

        // parse all button schematics ( ... )
        vector<vector<int>> buttonIdx;
        size_t pos = rb + 1;
        while (true) {
            size_t lp = line.find('(', pos);
            if (lp == string::npos || lp >= lcurly) break;
            size_t rp = line.find(')', lp + 1);
            if (rp == string::npos) break;

            string inside = line.substr(lp + 1, rp - lp - 1);

            // parse comma separated integers inside ()
            vector<int> idx;
            int cur = 0;
            bool have = false;
            for (char c : inside) {
                if (c >= '0' && c <= '9') {
                    cur = cur * 10 + (c - '0');
                    have = true;
                } else {
                    if (have) {
                        idx.push_back(cur);
                        cur = 0;
                        have = false;
                    }
                }
            }
            if (have) idx.push_back(cur);

            buttonIdx.push_back(idx);
            pos = rp + 1;
        }

        int m = (int)buttonIdx.size();
        if (m == 0) {
            // No buttons only valid if pattern is all .
            bool ok = true;
            for (char c : pattern) {
                if (c == '#') {
                    ok = false;
                    break;
                }
            }
            // if !ok then unsolvable but puzzle shouldn't do this
            continue;
        }

        // set up linear system over GF(2): mat * x = rhs
        int nEq = nLights;
        vector<unsigned long long> mat(nEq, 0ULL); // one row per light
        vector<int> rhs(nEq, 0);                  // 1 if target light is '#'

        // rhs is just desired on/off for each light
        for (int r = 0; r < nEq; ++r) {
            if (pattern[r] == '#') rhs[r] = 1;
        }

        // build matrix columns from buttons, mat[row][col] = 1 if button col flips light row
        for (int j = 0; j < m; ++j) {
            for (int idx : buttonIdx[j]) {
                if (idx >= 0 && idx < nEq) {
                    mat[idx] ^= (1ULL << j);
                }
            }
        }

        // gaussian elimination over GF(2)
        vector<int> where(m, -1);
        int row = 0;
        for (int col = 0; col < m && row < nEq; ++col) {
            // find pivot row that has a 1 in this column
            int sel = row;
            while (sel < nEq && (((mat[sel] >> col) & 1ULL) == 0ULL)) ++sel;
            if (sel == nEq) continue;

            swap(mat[sel], mat[row]);
            swap(rhs[sel], rhs[row]);
            where[col] = row;

            // eliminate this column from all other rows
            for (int i = 0; i < nEq; ++i) {
                if (i != row && ((mat[i] >> col) & 1ULL)) {
                    mat[i] ^= mat[row];
                    rhs[i] ^= rhs[row];
                }
            }
            ++row;
        }

        // back-substitute to get one particular solution x
        vector<int> x(m, 0);
        for (int col = m - 1; col >= 0; --col) {
            int r = where[col];
            if (r == -1) {
                x[col] = 0; // free variable, choose 0 in particular solution
                continue;
            }
            int val = rhs[r];
            unsigned long long rowmask = mat[r];
            for (int j = col + 1; j < m; ++j) {
                if ((rowmask >> j) & 1ULL) val ^= x[j];
            }
            x[col] = val;
        }

        // pack particular solution into a bitmask
        unsigned long long xpMask = 0ULL;
        for (int i = 0; i < m; ++i) {
            if (x[i]) xpMask |= (1ULL << i);
        }

        // build nullspace basis
        vector<unsigned long long> basisMasks; // each is length-m mask
        for (int col = 0; col < m; ++col) {
            if (where[col] == -1) {
                // Free variable col = 1, all other free vars = 0
                vector<int> z(m, 0);
                z[col] = 1;

                // Compute pivot variables from bottom-up
                for (int c = m - 1; c >= 0; --c) {
                    int r = where[c];
                    if (r == -1) continue;
                    int val = 0;
                    unsigned long long rowmask = mat[r];
                    for (int j = c + 1; j < m; ++j) {
                        if ((rowmask >> j) & 1ULL) val ^= z[j];
                    }
                    z[c] = val;
                }

                // convert this null vector into a mask
                unsigned long long zm = 0ULL;
                for (int j = 0; j < m; ++j) {
                    if (z[j]) zm |= (1ULL << j);
                }
                basisMasks.push_back(zm);
            }
        }

        int k = (int)basisMasks.size();
        int bestCost = (int)1e9;

        // search over all combinations of nullspace basis to minimize popcount
        if (k == 0) {
            // only one solution, the particular one
            bestCost = __builtin_popcountll(xpMask);
        } else if (k <= 22) {
            // 2^k brute force is fine here
            int totalSub = 1 << k;
            for (int mask = 0; mask < totalSub; ++mask) {
                unsigned long long curMask = xpMask;
                for (int b = 0; b < k; ++b) {
                    if (mask & (1 << b)) curMask ^= basisMasks[b];
                }
                int cost = __builtin_popcountll(curMask);
                if (cost < bestCost) bestCost = cost;
            }
        } else {
            // nullspace too big, just give up and use particular solution
            cout << "uhoh" << endl;
            bestCost = __builtin_popcountll(xpMask);
        }

        // add minimal presses for this machine
        total += bestCost;
    }

    cout << total << '\n';
}

void problem2() {

}

int main() {
    setup();
    problem1();
    setup();
    problem2();
    return 0;
}
