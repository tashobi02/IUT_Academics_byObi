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
    lli n;
    cin >> n;
    vi trucks(n);
    stack<lli> trc;
    stack<lli> backs;
    loop(i, n) { cin >> trucks[i]; }
    for (lli i = n - 1; i >= 0; i--) {
        trc.push(trucks[i]);
    }
    lli flag = 1;
    while (!trc.empty() || !backs.empty()) {
        if (!trc.empty() && trc.top() == flag) {
            flag++;
            trc.pop();
        } else if (!backs.empty() && backs.top() == flag) {
            flag++;
            backs.pop();
        } else if (!trc.empty()) {
            backs.push(trc.top());
            trc.pop();
        } else {
            break;
        }
    }
    if (flag == n + 1)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}
int main() {
    lli t = 1;
    while (t--) soln();
}