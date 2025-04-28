#include <algorithm>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <string>
using namespace std;
typedef long long int lli;
#define loop(i, n) for (lli i = 0; i < (n); i++)
#define endl "\n"
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}
void soln() {
    string s;
    deque<char> text;
    while (cin >> s) {
        deque<char> temp;
        bool atf = false;
        for (lli i = 0; i < s.size(); i++) {
            if (s[i] == '[') {
                atf = true;
                temp.clear();
            } else if (s[i] == ']') {
                if (atf) {
                    while (!temp.empty()) {
                        text.push_front(temp.back());
                        temp.pop_back();
                    }
                }
                atf = false;
            } else {
                if (atf) {
                    temp.push_back(s[i]);
                } else {
                    text.push_back(s[i]);
                }
            }
        }
        if (atf && !temp.empty()) {
            while (!temp.empty()) {
                text.push_front(temp.back());
                temp.pop_back();
            }
        }
        while (!text.empty()) {
            cout << text.front();
            text.pop_front();
        }
        cout << endl;
    }
}
int main() {
    fast();
    soln();
}
