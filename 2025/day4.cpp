#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

using namespace std;

void setup() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("day4.txt", "r", stdin);
    cin.clear();
    fseek(stdin, 0, SEEK_SET);
}

bool canPick(vector<vector<char>> grid, int x, int y) {
    int count = 0;

    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i == x && j == y) continue;
            if (i < 0 || i >= grid.size() || j < 0 || j >= grid[i].size()) continue;
            if (grid[i][j] == '@') count++;
        }
    }

    return count < 4;
}

int count(vector<vector<char>> grid, int x, int y) {
    int count = 0;

    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i == x && j == y) continue;
            if (i < 0 || i >= grid.size() || j < 0 || j >= grid[i].size()) continue;
            if (grid[i][j] == '@') count++;
        }
    }

    return count;
}

void problem1() {
    string line;
    int ans = 0;

    vector<vector<char>> grid;

    while (getline(cin, line)) {
        grid.push_back(vector<char>(line.begin(), line.end()));
    }

    int x = 0;
    int y = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] == '@' && canPick(grid, i, j)) {
                ans++;
            }
        }
    }

    cout << ans << endl;
}

void problem2() {
    // problem 1 was pretty simple
    // thinking of how to prune the grid more efficiently since I assume I can't just iterate my previous solution over and over again
    // Maybe some sort of bfs over each paper
    // Ok, treat it as a graph, each paper is a node, each edge is just the adj papers
    // Keep track of all cells that have been visited
    // Then keep track of a queue, add each node that has less than 4 edges to queue
    // While items r in queue, process one, remove, decrement edge counts from adjacent cells and then add to queue if it goes under a certain amount

    string line;
    int ans = 0;

    vector<vector<char>> grid;
    while (getline(cin, line)) {
        grid.push_back(vector<char>(line.begin(), line.end()));
    }

    vector<vector<bool>> visited;
    visited.resize(grid.size(), vector<bool>(grid[0].size()));

    vector<vector<int>> edges;
    edges.resize(grid.size(), vector<int>(grid[0].size()));

    queue<pair<int, int>> toCheck;

    // now we can go ahead and precompute

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == '@') {
                edges[i][j] = count(grid, i, j);
                if (edges[i][j] < 4) {
                    toCheck.push({i, j});
                }
            }
        }
    }

    while (toCheck.size() > 0) {
        pair<int, int> coord = toCheck.front();
        int x = coord.first;
        int y = coord.second;
        toCheck.pop();
        if (visited[x][y]) continue;
        visited[x][y] = true;

        // found a node we should be checking
        ++ans;
        // check surrounding nodes that are now updated
        for (int i = x - 1; i <= x + 1; ++i) {
            for (int j = y - 1; j <= y + 1; ++j) {
                if (i == x && j == y) continue;
                if (i < 0 || i >= grid.size() || j < 0 || j >= grid[i].size()) continue;
                if (visited[i][j] || grid[i][j] != '@') continue; // skip checked
                edges[i][j]--;
                // check if its been lowered to 3 aka it has enough to go!
                if (edges[i][j] == 3) toCheck.push({i, j});
            }
        }
    }

    cout << ans << endl;
}

int main() {
    setup();
    problem1();
    setup();
    problem2();
    return 0;
}

