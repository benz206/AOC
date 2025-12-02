#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

void setup() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("day2.txt", "r", stdin);
    cin.clear();
    fseek(stdin, 0, SEEK_SET);
}

long long generateDouble(int base) {
    string str = to_string(base);
    string doubled = str + str;
    return stoll(doubled);
}

bool inRange(long long num, const vector<pair<long long, long long>> &ranges) {
    for (const auto &range : ranges) {
        if (num >= range.first && num <= range.second) {
            return true;
        }
    }
    return false;
}

void problem1() {
    string line;
    getline(cin, line);

    vector<pair<long long, long long>> ranges;
    stringstream ss(line);
    string rangeStr;
    while (getline(ss, rangeStr, ',')) {
        size_t dashPos = rangeStr.find('-');
        long long start = stoll(rangeStr.substr(0, dashPos));
        long long end = stoll(rangeStr.substr(dashPos + 1));
        ranges.push_back({start, end});
    }

    long long sum = 0;
    
    long long maxNum = 0;
    for (const auto &range : ranges) {
        maxNum = max(maxNum, range.second);
    }
    
    int maxBaseDigits = to_string(maxNum).length() / 2 + 1;
    
    for (int baseDigits = 1; baseDigits <= maxBaseDigits; baseDigits++) {
        int startBase = (baseDigits == 1) ? 1 : pow(10, baseDigits - 1);
        int endBase = pow(10, baseDigits) - 1;
        
        for (int base = startBase; base <= endBase; base++) {
            long long doubled = generateDouble(base);
            if (doubled > maxNum) break;
            if (inRange(doubled, ranges)) {
                sum += doubled;
            }
        }
    }

    cout << sum << endl;
}

long long generateRepeated(int base, int repetitions) {
    string str = to_string(base);
    string repeated = "";
    for (int i = 0; i < repetitions; i++) {
        repeated += str;
    }
    return stoll(repeated);
}

void problem2() {
    string line;
    getline(cin, line);

    vector<pair<long long, long long>> ranges;
    stringstream ss(line);
    string rangeStr;
    while (getline(ss, rangeStr, ',')) {
        size_t dashPos = rangeStr.find('-');
        long long start = stoll(rangeStr.substr(0, dashPos));
        long long end = stoll(rangeStr.substr(dashPos + 1));
        ranges.push_back({start, end});
    }

    set<long long> invalidIDs;
    
    long long maxNum = 0;
    for (const auto &range : ranges) {
        maxNum = max(maxNum, range.second);
    }
    
    int maxDigits = to_string(maxNum).length();
    
    for (int baseDigits = 1; baseDigits <= maxDigits / 2; baseDigits++) {
        int startBase = (baseDigits == 1) ? 1 : pow(10, baseDigits - 1);
        int endBase = pow(10, baseDigits) - 1;
        
        for (int base = startBase; base <= endBase; base++) {
            for (int repetitions = 2; repetitions <= maxDigits / baseDigits; repetitions++) {
                long long repeated = generateRepeated(base, repetitions);
                if (repeated > maxNum) break;
                if (inRange(repeated, ranges)) {
                    invalidIDs.insert(repeated);
                }
            }
        }
    }

    long long sum = 0;
    for (long long id : invalidIDs) {
        sum += id;
    }

    cout << sum << endl;
}

int main() {
    setup();
    problem1();
    setup();
    problem2();
    return 0;
}

