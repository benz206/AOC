#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

void setup() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("day5.txt", "r", stdin);
    cin.clear();
    fseek(stdin, 0, SEEK_SET);
}

void problem1() {
    string line;
    ll count = 0;

    vector<pair<ll, ll>> ranges;

    while (getline(cin, line)) {
        if (line.empty()) {
            break;
        }

        size_t delim = line.find('-');

        ll left  = stoll(line.substr(0, delim));
        ll right = stoll(line.substr(delim + 1));

        ranges.emplace_back(left, right);
    }

    sort(ranges.begin(), ranges.end());

    // merge overlapping ranges
    vector<pair<ll, ll>> merged;
    for (auto &p : ranges) {
        ll l = p.first;
        ll r = p.second;
        if (merged.empty() || l > merged.back().second) {
            merged.emplace_back(l, r);
        } else {
            if (r > merged.back().second) merged.back().second = r;
        }
    }
    ranges.swap(merged);

    while (getline(cin, line)) {
        if (line.empty()) continue;

        ll id = stoll(line);

        bool fresh = false;

        int lo = 0, hi = (int)ranges.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            ll L = ranges[mid].first;
            ll R = ranges[mid].second;

            if (id < L) {
                hi = mid - 1;
            } else if (id > R) {
                lo = mid + 1;
            } else {
                fresh = true;
                break;
            }
        }

        if (fresh) ++count;
    }

    cout << count << '\n';
}

void problem2() {
    // same idea literally just count ranges now
    string line;
    ll count = 0;

    vector<pair<ll, ll>> ranges;

    while (getline(cin, line)) {
        if (line.empty()) {
            break;
        }

        size_t delim = line.find('-');

        ll left  = stoll(line.substr(0, delim));
        ll right = stoll(line.substr(delim + 1));

        ranges.emplace_back(left, right);
    }

    sort(ranges.begin(), ranges.end());

    // merge overlapping ranges
    vector<pair<ll, ll>> merged;
    for (auto &p : ranges) {
        ll l = p.first;
        ll r = p.second;
        if (merged.empty() || l > merged.back().second) {
            merged.emplace_back(l, r);
        } else {
            if (r > merged.back().second) merged.back().second = r;
        }
    }
    ranges.swap(merged);

    for (auto &r : ranges) {
        count += r.second - r.first + 1;
    }

    cout << count << '\n';
}

int main() {
    setup();
    problem1();
    setup();
    problem2();
    return 0;
}
