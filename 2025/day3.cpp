#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

void setup() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("day3.txt", "r", stdin);
    cin.clear();
    fseek(stdin, 0, SEEK_SET);
}

void problem1() {
    string line;

    int maxjoltage = 0;
    
    while (getline(cin, line)) {
        if (line.empty()) continue;
        int joltage = 0;
        
        // find the largest number excluding final
        int largest = 0;
        for (int i = 0; i < line.length() - 1; i++) {
            int num = line[i] - '0';
            if (num > largest) {
                largest = num;
            }

            if (num == 9) {
                break;
            }
        }

        joltage += largest * 10;

        int index = line.find(to_string(largest));
        largest = line[index + 1] - '0';
        for (int i = index + 1; i < line.length(); i++) {
            int num = line[i] - '0';
            if (num > largest) {
                largest = num;
            }
        }

        joltage += largest;

        maxjoltage += joltage;
    }

    cout << maxjoltage << endl;
}

void problem2() {
    string line;
    long long total = 0;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        int n = (int)line.size();

        int remove = n - 12;
        string st;
        st.reserve(n);

        for (char c : line) {
            while (!st.empty() && remove > 0 && st.back() < c) {
                st.pop_back();
                --remove;
            }
            st.push_back(c);
        }

        // trim the end if needed
        if ((int)st.size() > 12) st.resize(12);

        long long value = 0;
        for (char c : st) {
            value = value * 10 + (c - '0');
        }

        total += value;
    }

    cout << total << endl;
}

int main() {
    setup();
    problem1();
    setup();
    problem2();
    return 0;
}

