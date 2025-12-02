#include <bits/stdc++.h>

using namespace std;

void setup() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("day1.txt", "r", stdin);
    cin.clear();
    fseek(stdin, 0, SEEK_SET);
}

void problem1() {
    int position = 50;
    int count = 0;
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        char direction = line[0];
        int distance = stoi(line.substr(1));
        
        if (direction == 'L') {
            position = (position - distance + 100) % 100;
        } else {
            position = (position + distance) % 100;
        }
        
        if (position == 0) {
            count++;
        }
    }
    
    cout << count << endl;
}

void problem2() {
    int position = 50;
    int count = 0;
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        char direction = line[0];
        int distance = stoi(line.substr(1));
        
        if (direction == 'L') {
            int start = position;
            int end = (position - distance + 100) % 100;
            
            for (int i = 1; i <= distance; i++) {
                int current = (start - i + 100) % 100;
                if (current == 0) {
                    count++;
                }
            }
            
            position = end;
        } else {
            int start = position;
            int end = (position + distance) % 100;
            
            for (int i = 1; i <= distance; i++) {
                int current = (start + i) % 100;
                if (current == 0) {
                    count++;
                }
            }
            
            position = end;
        }
    }
    
    cout << count << endl;
}

int main() {
    setup();
    problem1();
    setup();
    problem2();
    return 0;
}

