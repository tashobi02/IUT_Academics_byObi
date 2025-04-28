#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>
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
    lli x = s.size();
    stack<lli> nums;
    lli res;
    loop(i, x) {
        if (s[i] >= '0' && s[i] <= '9') {
            lli q = s[i] - '0';
            nums.push(q);
        } else {
            char c = s[i];
            lli q2 = nums.top();
            nums.pop();
            lli q1 = nums.top();
            nums.pop();
            if (c == '+') {
                res = q1 + q2;
            } else if (c == '*') {
                res = q1 * q2;
            } else if (c == '-') {
                res = q1 - q2;
            } else if (c == '/') {
                res = q1 / q2;
            }
            nums.push(res);
        }
    }
    cout << nums.top() << endl;
}

int main() {
    fast();
    lli t;
    cin >> t;
    while (t--) soln();
}
