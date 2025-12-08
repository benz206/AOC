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
    freopen("day8.txt", "r", stdin);
    cin.clear();
    fseek(stdin, 0, SEEK_SET);
}

struct Point {
    int x;
    int y;
    int z;
};

struct Edge {
    int u, v;
    ll w;
};

ll dist(const Point& a, const Point& b) {
    ll dx = (ll)b.x - a.x;
    ll dy = (ll)b.y - a.y;
    ll dz = (ll)b.z - a.z;
    return dx * dx + dy * dy + dz * dz;
}

vector<string> split(const string& s, const string& delimiter) {
    vector<string> tokens;
    string temp = s;
    size_t pos = 0;

    while ((pos = temp.find(delimiter)) != string::npos) {
        tokens.push_back(temp.substr(0, pos));
        temp.erase(0, pos + delimiter.size());
    }

    tokens.push_back(temp);
    return tokens;
}

// disjoint unino set
struct DSU {
    vector<int> parent;
    vector<int> size;

    DSU(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }


    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return false;

        if (size[a] < size[b]) {
            swap(a, b);
        }

        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

void problem1() {
    vector<Point> pts;

    string line;

    while (getline(cin, line)) {
        vector<string> raw = split(line, ",");

        int x = stoi(raw[0]);
        int y = stoi(raw[1]);
        int z = stoi(raw[2]);
        pts.push_back({ x, y, z });
    }

    int n = pts.size();

    // gen all edges
    vector<Edge> edges;
    edges.reserve((ll)n * (n - 1) / 2);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            edges.push_back({ i, j, dist(pts[i], pts[j]) });
        }
    }

    // sort based on ascending dist
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
        });

    DSU dsu(n);

    int used = 0;
    for (auto& e : edges) {
        ++used;
        dsu.unite(e.u, e.v); // merges if different
        if (used == 1000) break;
    }

    vector<int> sizes;
    sizes.reserve(n);
    for (int i = 0; i < n; ++i) {
        // find root & check if i is root
        if (dsu.find(i) == i) {
            sizes.push_back(dsu.size[i]);
        }
    }

    sort(sizes.begin(), sizes.end(), greater<int>());

    ll ans = 1LL * sizes[0] * sizes[1] * sizes[2];

    cout << ans << "\n";
}

void problem2() {
    vector<Point> pts;
    string line;

    while (getline(cin, line)) {
        vector<string> raw = split(line, ",");

        int x = stoi(raw[0]);
        int y = stoi(raw[1]);
        int z = stoi(raw[2]);
        pts.push_back({x, y, z});
    }

    int n = pts.size();

    // generate all edges
    vector<Edge> edges;
    edges.reserve((ll)n * (n-1) / 2);

    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            edges.push_back({i, j, dist(pts[i], pts[j])});
        }
    }

    // sort edges by distance
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b){
        return a.w < b.w;
    });

    DSU dsu(n);
    int components = n;   // initially, each point is its own component
    int lastU = -1, lastV = -1;

    // now only consider unconnected points
    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {  // true when two different components are merged
            components--;
            if (components == 1) {  // all in one big circuit now
                lastU = e.u;
                lastV = e.v;
                break;
            }
        }
    }

    // multiply X coordinates of those last two junction boxes
    ll ans = 1LL * pts[lastU].x * pts[lastV].x;
    cout << ans << "\n";
}

int main() {
    setup();
    problem1();
    setup();
    problem2();
    return 0;
}
