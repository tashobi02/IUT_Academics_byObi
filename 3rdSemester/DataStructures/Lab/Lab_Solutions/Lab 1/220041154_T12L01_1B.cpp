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
    lli n, ct = 0;
    char x;
    cin >> n;
    stack<char> prt;
    stack<char> backs;
    loop(i, n) {
        cin >> x;
        if (x == '(') {
            prt.push(x);
        } else if (x == ')') {
            if (!prt.empty()) {
                if (prt.top() == '(')
                    prt.pop();
                else
                    backs.push(x);
            } else
                backs.push(x);
        }
    }
    while (!prt.empty()) {
        if (prt.top() == '(' && backs.top() == ')') {
            prt.pop();
            backs.pop();
            ct++;
        }
    }
    cout << ct << endl;
}
int main() {
    lli t;
    cin >> t;
    while (t--) soln();
}