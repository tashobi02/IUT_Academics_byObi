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
    string s;
    cin >> s;
    stack<char> str;
    lli x = s.size();
    loop(i, x) str.push(s[i]);
    loop(i, x) {
        cout << str.top();
        str.pop();
    }
    cout << endl;
}
int main() {
    fast();
    // Basically we will implement the LIFO Principle
    lli t;
    cin >> t;
    while (t--) soln();
}