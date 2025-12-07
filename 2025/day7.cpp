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
    freopen("day7.txt", "r", stdin);
    cin.clear();
    fseek(stdin, 0, SEEK_SET);
}

void problem1() {
    vector<string> grid;
    string line;
    while (cin >> line) {
        grid.push_back(line);
    }

    int H = grid.size();
    int W = grid[0].size();

    int sr = -1, sc = -1;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (grid[i][j] == 'S') {
                sr = i;
                sc = j;
            }
        }
    }

    vector<vector<bool>> cur(H, vector<bool>(W));
    vector<vector<bool>> nxt(H, vector<bool>(W));

    cur[sr][sc] = true;

    ll splits = 0;

    while (true) {
        for (int i = 0; i < H; ++i) {
            fill(nxt[i].begin(), nxt[i].end(), false);
        }

        bool anyNext = false;

        for (int r = 0; r < H; ++r) {
            for (int c = 0; c < W; ++c) {
                if (!cur[r][c]) continue;

                int nr = r + 1;
                if (nr >= H) { // beam is gold
                    continue;
                }

                char ch = grid[nr][c];
                if (ch == '^') {
                    // hits something
                    ++splits;

                    if (c - 1 >= 0) {
                        if (!nxt[nr][c - 1]) {
                            nxt[nr][c - 1] = true;
                            anyNext = true;
                        }
                    }
                    if (c + 1 < W) {
                        if (!nxt[nr][c + 1]) {
                            nxt[nr][c + 1] = true;
                            anyNext = true;
                        }
                    }
                } else {
                    // continue beam
                    if (!nxt[nr][c]) {
                        nxt[nr][c] = true;
                        anyNext = true;
                    }
                }
            }
        }

        if (!anyNext) break;

        cur.swap(nxt);
    }

    cout << splits << "\n";
}

void problem2() {
    vector<string> grid;
    string line;
    while (cin >> line) {
        grid.push_back(line);
    }

    int H = grid.size();
    int W = grid[0].size();

    int sr = -1, sc = -1;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (grid[i][j] == 'S') {
                sr = i;
                sc = j;
            }
        }
    }

    vector<vector<ll>> cur(H, vector<ll>(W));
    vector<vector<ll>> nxt(H, vector<ll>(W));

    cur[sr][sc] = 1;

    ll timelines = 0;

    while (true) {
        for (int i = 0; i < H; ++i) {
            fill(nxt[i].begin(), nxt[i].end(), 0);
        }

        bool anyNext = false;

        for (int r = 0; r < H; ++r) {
            for (int c = 0; c < W; ++c) {
                ll cnt = cur[r][c];
                if (!cnt) continue;

                int nr = r + 1;
                if (nr >= H) {
                    timelines += cnt;
                    continue;
                }

                char ch = grid[nr][c];
                if (ch == '^') {
                    if (c - 1 >= 0) {
                        nxt[nr][c - 1] += cnt;
                        anyNext = true;
                    } else {
                        timelines += cnt;
                    }
                    if (c + 1 < W) {
                        nxt[nr][c + 1] += cnt;
                        anyNext = true;
                    } else {
                        timelines += cnt;
                    }
                } else {
                    nxt[nr][c] += cnt;
                    anyNext = true;
                }
            }
        }

        if (!anyNext) break;

        cur.swap(nxt);
    }

    cout << timelines << "\n";
}

int main() {
    setup();
    problem1();
    setup();
    problem2();
    return 0;
}
