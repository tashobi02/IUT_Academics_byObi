#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
typedef long long int lli;
typedef vector<long long int> vi;
#define pb push_back
#define loop(i, n) for (lli i = 0; i < (n); i++)
#define endl "\n"
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
void soln() {
    string mth;
    getline(cin, mth);
    lli x = mth.size();
    stack<char> parenthesis;
    char p;
    loop(i, x) {
        p = mth[i];
        if (p == '[' || p == '{' || p == '(') {
            parenthesis.push(p);
        } else if (p == ']' || p == '}' || p == ')') {
            if (parenthesis.empty()) {
                cout << "No" << endl;
                return;
            } else {
                char top = parenthesis.top();
                if ((p == ')' && top == '(') || (p == '}' && top == '{') ||
                    (p == ']' && top == '[')) {
                    parenthesis.pop();
                } else {
                    cout << "No" << endl;
                    return;
                }
            }
        }
    }
    cout << (parenthesis.empty() ? "Yes" : "No") << endl;
}
int main() {
    fast();
    lli t;
    cin >> t;
    cin.ignore();
    while (t--) {
        soln();
    }
}