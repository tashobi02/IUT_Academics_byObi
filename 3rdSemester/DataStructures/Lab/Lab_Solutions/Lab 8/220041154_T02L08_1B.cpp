#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
typedef long long int lli;
typedef long double ld;
typedef vector<long long int> vi;
#define pb push_back
#define loop(i, n) for (lli i = 0; i < (n); i++)
#define endl "\n"
#define py cout << "YES" << endl
#define pn cout << "NO" << endl
#define all(v) v.begin(), v.end()
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
int main() {
    vi val;
    lli z = 0, tp = 0;
    lli target, x, p, q;
    unordered_map<lli, lli> freq;
    while (1) {
        cin >> x;
        if (x == -1)
            break;
        else {
            val.pb(x);
            freq[x]++;
            z++;
        }
    }
    cin >> target;
    loop(i, z) {
        p = val[i];
        q = target - p;
        // cout << freq[p] << " " << freq[q] << endl;
        if (freq[q] > 0 && freq[p] > 0) {
            freq[p]--;
            freq[q]--;
            if (p == q && freq[p] == 1)
                continue;
            else {
                cout << "(" << p << "," << q << ")"
                     << " ";
                tp++;
            }
        }
    }
    if (tp == 0)
        cout << "No pairs found" << endl;
}