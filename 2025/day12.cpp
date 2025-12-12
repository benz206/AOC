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
    freopen("day12.txt", "r", stdin);
    cin.clear();
    fseek(stdin, 0, SEEK_SET);
}

void problem1() {
    // not sure how to do this, backtrack with vectors, gen all 4 rotations and 2 flips, dedupe that and then place all on bottom like tetris and repeat?
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
