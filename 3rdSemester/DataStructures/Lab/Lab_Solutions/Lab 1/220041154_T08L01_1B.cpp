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
    lli n;
    cin >> n;
    bool valid = true;
    cin.ignore();
    stack<char> prt;
    vector<string> lines(n);
    loop(i, n) getline(cin, lines[i]);
    loop(i, n) {
        lli len = lines[i].size();
        loop(j, len) {
            if (lines[i][j] == '{') {
                prt.push('{');
            } else if (lines[i][j] == '}') {
                if (prt.top() == '{')
                    prt.pop();
                else
                    valid = false;
            }
        }
    }
    if (prt.empty() && valid)
        cout << "No Errors" << endl;
    else
        cout << "Error" << endl;
}
int main() {
    fast();
    lli t = 1;
    while (t--) soln();
}