#include <bits/stdc++.h>

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
    getline(cin, line);


    cout << sum << endl;
}

int main() {
    setup();
    problem1();
    setup();
    problem2();
    return 0;
}

