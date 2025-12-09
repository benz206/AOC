#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cctype>
#include <numeric>

using namespace std;

typedef long long ll;

void setup() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("day9.txt", "r", stdin);
    cin.clear();
    fseek(stdin, 0, SEEK_SET);
}

void problem1() {
    vector<pair<ll,ll>> pts;
    string s;
    while (getline(cin, s)) {
        if (s.empty()) continue;
        size_t comma = s.find(',');

        ll x = stoll(s.substr(0, comma));
        ll y = stoll(s.substr(comma + 1));
        pts.emplace_back(x, y);
    }

    ll best = 0;
    int n = (int)pts.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ll dx = llabs(pts[i].first  - pts[j].first);
            ll dy = llabs(pts[i].second - pts[j].second);
            // tiles are inclusive, so +1 in each dimension
            ll area = (dx + 1) * (dy + 1);
            if (area > best) best = area;
        }
    }

    cout << best << endl;
}

void problem2() {
    vector<pair<ll,ll>> pts;
    string s;
    while (getline(cin, s)) {
        if (s.empty()) continue;
        size_t comma = s.find(',');

        ll x = stoll(s.substr(0, comma));
        ll y = stoll(s.substr(comma + 1));
        pts.emplace_back(x, y);
    }

    int n = (int)pts.size();
    if (n < 2) {
        cout << 0 << endl;
        return;
    }

    // get min max of both axis
    ll minX = pts[0].first, maxX = pts[0].first;
    ll minY = pts[0].second, maxY = pts[0].second;
    for (auto &p : pts) {
        minX = min(minX, p.first);
        maxX = max(maxX, p.first);
        minY = min(minY, p.second);
        maxY = max(maxY, p.second);
    }

    vector<ll> xs, ys;
    xs.reserve(n + 2);
    ys.reserve(n + 2);

    xs.push_back(minX - 1);
    xs.push_back(maxX + 1);
    ys.push_back(minY - 1);
    ys.push_back(maxY + 1);

    for (auto &p : pts) {
        xs.push_back(p.first);
        ys.push_back(p.second);
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    int W = xs.size() - 1;
    int H = ys.size() - 1;

    // map from compressed to actual
    unordered_map<ll,int> xIdx, yIdx;
    xIdx.reserve(xs.size() * 2);
    yIdx.reserve(ys.size() * 2);

    for (int i = 0; i < xs.size(); ++i) xIdx[xs[i]] = i;
    for (int i = 0; i < ys.size(); ++i) yIdx[ys[i]] = i;

    // --- walls between compressed cells ---
    // hwall[r][c] = wall between row r-1 and r at column c (1 <= r <= H-1, 0 <= c < W)
    // vwall[r][c] = wall between col c-1 and c at row r (0 <= r < H, 1 <= c <= W-1)
    vector<vector<char>> hwall(H + 1, vector<char>(W, 0));
    vector<vector<char>> vwall(H,     vector<char>(W + 1, 0));

    // build polygon edges from consecutive red tiles (wrap around)
    for (int i = 0; i < n; ++i) {
        auto [x1, y1] = pts[i];
        auto [x2, y2] = pts[(i + 1) % n];

        int ix1 = xIdx[x1];
        int iy1 = yIdx[y1];
        int ix2 = xIdx[x2];
        int iy2 = yIdx[y2];

        if (y1 == y2) {
            // horizontal edge at y = y1 between x1 and x2
            int rowLine = iy1;                   // grid line index in ys
            int xa = min(ix1, ix2);
            int xb = max(ix1, ix2);
            // mark walls between rows rowLine-1 and rowLine for columns covering [x1, x2)
            for (int c = xa; c < xb; ++c) {
                hwall[rowLine][c] = 1;
            }
        } else if (x1 == x2) {
            // vertical edge at x = x1 between y1 and y2
            int colLine = ix1;
            int ya = min(iy1, iy2);
            int yb = max(iy1, iy2);
            // mark walls between cols colLine-1 and colLine for rows covering [y1, y2)
            for (int r = ya; r < yb; ++r) {
                vwall[r][colLine] = 1;
            }
        }
    }

    // --- flood-fill outside region on compressed grid ---
    vector<vector<char>> outside(H, vector<char>(W, 0));
    queue<pair<int,int>> q;

    auto push_if_out = [&](int r, int c) {
        if (r < 0 || r >= H || c < 0 || c >= W) return;
        if (outside[r][c]) return;
        outside[r][c] = 1;
        q.emplace(r, c);
    };

    // start from border cells of the compressed grid
    for (int c = 0; c < W; ++c) {
        push_if_out(0, c);
        push_if_out(H - 1, c);
    }
    for (int r = 0; r < H; ++r) {
        push_if_out(r, 0);
        push_if_out(r, W - 1);
    }

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        // up down left right
        if (r > 0 && !hwall[r][c] && !outside[r - 1][c]) {
            outside[r - 1][c] = 1;
            q.emplace(r - 1, c);
        }
        if (r + 1 < H && !hwall[r + 1][c] && !outside[r + 1][c]) {
            outside[r + 1][c] = 1;
            q.emplace(r + 1, c);
        }
        if (c > 0 && !vwall[r][c] && !outside[r][c - 1]) {
            outside[r][c - 1] = 1;
            q.emplace(r, c - 1);
        }
        if (c + 1 < W && !vwall[r][c + 1] && !outside[r][c + 1]) {
            outside[r][c + 1] = 1;
            q.emplace(r, c + 1);
        }
    }

    // prefix sum the fake cells
    vector<vector<int>> pref(H + 1, vector<int>(W + 1, 0));
    for (int r = 0; r < H; ++r) {
        int rowSum = 0;
        for (int c = 0; c < W; ++c) {
            rowSum += outside[r][c] ? 1 : 0;
            pref[r + 1][c + 1] = pref[r][c + 1] + rowSum;
        }
    }

    auto rect_has_outside = [&](int r1, int c1, int r2, int c2) -> bool {
        // r1..r2-1, c1..c2-1 inclusive in cell indices
        int sum = pref[r2][c2] - pref[r1][c2] - pref[r2][c1] + pref[r1][c1];
        return sum > 0;
    };

    ll best = 0;
    for (int i = 0; i < n; ++i) {
        auto [x1, y1] = pts[i];
        for (int j = i + 1; j < n; ++j) {
            auto [x2, y2] = pts[j];

            ll dx = llabs(x1 - x2);
            ll dy = llabs(y1 - y2);
            if (dx == 0 || dy == 0) continue; // degenerate

            ll area = (dx + 1) * (dy + 1);

            ll xMin = min(x1, x2);
            ll xMax = max(x1, x2);
            ll yMin = min(y1, y2);
            ll yMax = max(y1, y2);

            // map back
            int c1 = xIdx[xMin];
            int c2 = xIdx[xMax];
            int r1 = yIdx[yMin];
            int r2 = yIdx[yMax];

            if (rect_has_outside(r1, c1, r2, c2)) {
                continue; // rectangle includes some outside cells
            }

            if (area > best) best = area;
        }
    }

    cout << best << endl;
}

int main() {
    setup();
    problem1();
    setup();
    problem2();
    return 0;
}
