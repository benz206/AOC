#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cctype>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <functional>

using namespace std;

typedef long long ll;

void setup() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("day11.txt", "r", stdin);
    cin.clear();
    fseek(stdin, 0, SEEK_SET);
}

void problem1() {
    string line;

    unordered_map<string, vector<string>> adj;

    while (getline(cin, line)) {
        size_t colon = line.find(':');
        if (colon == string::npos) continue;

        string from = line.substr(0, colon);
        while (!from.empty() && isspace(static_cast<unsigned char>(from.back()))) {
            from.pop_back();
        }

        string rest = line.substr(colon + 1);
        size_t pos = 0;
        while (pos < rest.size() && isspace(static_cast<unsigned char>(rest[pos]))) {
            ++pos;
        }
        rest = rest.substr(pos);

        // parse targets
        stringstream ss(rest);
        string to;
        while (ss >> to) {
            adj[from].push_back(to);
        }

        if (!adj.count(from)) adj[from] = {};
    }

    unordered_map<string, ll> memo;
    unordered_set<string> visiting;

    function<ll(const string&)> dfs = [&](const string &u) -> ll {
        if (u == "out") return 1LL;

        auto it = memo.find(u);
        if (it != memo.end()) return it->second;

        visiting.insert(u);
        ll ways = 0;

        auto jt = adj.find(u);
        if (jt != adj.end()) {
            for (const string &v : jt->second) {
                ways += dfs(v);
            }
        }
        visiting.erase(u);

        memo[u] = ways;
        return ways;
    };

    ll totalPaths = dfs("you");
    cout << totalPaths << '\n';
}

void problem2() {
    string line;

    unordered_map<string, vector<string>> adj;

    while (getline(cin, line)) {
        size_t colon = line.find(':');
        if (colon == string::npos) continue;

        string from = line.substr(0, colon);
        while (!from.empty() && isspace(static_cast<unsigned char>(from.back()))) {
            from.pop_back();
        }

        string rest = line.substr(colon + 1);
        size_t pos = 0;
        while (pos < rest.size() && isspace(static_cast<unsigned char>(rest[pos]))) {
            ++pos;
        }
        rest = rest.substr(pos);

        // parse targets
        stringstream ss(rest);
        string to;
        while (ss >> to) {
            adj[from].push_back(to);
        }

        if (!adj.count(from)) adj[from] = {};
    }

    // bitmask for tracking whether we've seen dac / fft:
    // bit 0 -> seen dac
    // bit 1 -> seen fft
    auto addSpecial = [](int mask, const string &node) {
        if (node == "dac") mask |= 1;
        if (node == "fft") mask |= 2;
        return mask;
    };

    unordered_map<string, array<ll, 4>> memo;
    unordered_set<string> visiting;

    function<ll(const string&, int)> dfs =
        [&](const string &u, int mask) -> ll {
            // if we're at out, only count this path if we've seen both dac and fft
            if (u == "out") {
                return (mask == 3) ? 1LL : 0LL; // 11 to set both
            }

            auto itNode = memo.find(u);
            if (itNode != memo.end()) {
                ll cached = itNode->second[mask];
                if (cached != -1) return cached;
            } else {
                memo[u] = { -1, -1, -1, -1 };
            }

            visiting.insert(u);

            ll ways = 0;
            auto it = adj.find(u);
            if (it != adj.end()) {
                for (const string &v : it->second) {
                    int newMask = addSpecial(mask, v);
                    ways += dfs(v, newMask);
                }
            }

            visiting.erase(u);

            memo[u][mask] = ways;
            return ways;
        };

    ll totalPaths = dfs("svr", 0);
    cout << totalPaths << '\n';
}

int main() {
    setup();
    problem1();
    setup();
    problem2();
    return 0;
}
