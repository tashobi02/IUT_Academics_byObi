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
    string brackets;
    getline(cin, brackets);
    stack<char> brc;
    lli len = brackets.size();
    lli ct = 0;
    loop(i, len) {
        if (brackets[i] == '(') {
            brc.push('(');
        } else {
            if (!brc.empty()) {
                brc.pop();
                ct = ct + 2;
            }
        }
    }
    cout << ct << endl;
}
int main() {
    lli t = 1;
    while (t--) soln();
}