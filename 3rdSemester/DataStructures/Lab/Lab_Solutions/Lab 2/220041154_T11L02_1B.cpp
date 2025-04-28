#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>
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
    cout.tie(0);
}
string match_queue(deque<char> dq) {
    string res = "";
    lli sz = dq.size();
    loop(i, sz) {
        res += dq.front();
        dq.pop_front();
    }
    return res;
}
void soln() {
    string s1, s2, rs1, rs2;
    cin >> s1 >> s2;
    lli ct = 0;
    lli sz = s1.size();
    bool valid = false;
    deque<char> sq1, sq2;
    loop(i, sz) {
        sq1.push_back(s1[i]);
        sq2.push_back(s2[i]);
    }
    while (sz--) {
        rs1 = match_queue(sq1);
        rs2 = match_queue(sq2);
        if (rs1 == rs2) {
            valid = true;
            break;
        } else {
            char x;
            x = sq1.back();
            sq1.pop_back();
            sq1.push_front(x);
            ct++;
        }
    }
    if (valid) {
        cout << "Yes. "
             << "After " << ct << " clockwise rotations";
    } else {
        cout << "No.";
    }
    return;
}
int main() {
    fast();
    soln();
}