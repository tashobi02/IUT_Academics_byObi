#include <algorithm>
#include <cmath>
#include <cstring>
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
    string s, fs = "";
    cin >> s;
    stack<char> adj;
    lli sz = s.size();
    loop(i, sz) {
        if (adj.empty())
            adj.push(s[i]);
        else {
            if (s[i] == adj.top())
                adj.pop();
            else
                adj.push(s[i]);
        }
    }
    if (adj.empty()) {
        cout << "NULL" << endl;
        return;
    }
    while (!adj.empty()) {
        fs += adj.top();
        adj.pop();
    }
    reverse(fs.begin(), fs.end());
    cout << fs << endl;
}
int main() {
    fast();
    lli t = 1;
    while (t--) soln();
}