#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define enl "\n"
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
void soln() {
    lli n;
    cin >> n;
    vector<lli> a(n);
    lli mx = 0, ix;
    for (lli i = 0; i < n; i++) {
        cin >> a[i];
        if (mx < a[i]) {
            mx = a[i];
            ix = i + 1;
        } else if (mx == a[i]) {
            if ((ix + 1) % 2 == 1) {
                mx = a[i];
                ix = i + 1;
            }
        }
    }
    lli ans;
    if (n % 2 == 0)
        ans = mx + (n / 2);
    else {
        if (ix % 2 == 0)
            ans = mx + floor((long double)n / 2.0);
        else
            ans = mx + ceil((long double)n / 2.0);
    }
    cout << ans << enl;
}
int main() {
    fast();
    lli t = 1;
    cin >> t;
    while (t--) soln();
}
// Author: tashobi_02 //