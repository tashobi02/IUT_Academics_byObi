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
    lli n, q, x, flag;
    cin >> n >> q;
    stack<lli> sc;
    stack<lli> backs;
    vi shuttlecocks(n);
    vi flags(q);
    bool found;
    loop(i, n) cin >> shuttlecocks[i];
    for (lli i = n - 1; i >= 0; i--) sc.push(shuttlecocks[i]);
    loop(i, q) {
        cin >> x;
        flag = 1;
        found = false;
        while (!found && !sc.empty()) {
            if (x == sc.top()) {
                sc.pop();
                flags[i] = flag;
                found = true;
            } else {
                backs.push(sc.top());
                sc.pop();
                flag++;
            }
        }
        while (!backs.empty()) {
            sc.push(backs.top());
            backs.pop();
        }
        sc.push(x);
    }
    loop(i, q) cout << flags[i] << " ";
    cout << endl;
    return;
}
int main() {
    fast();
    lli t = 1;
    while (t--) soln();
}