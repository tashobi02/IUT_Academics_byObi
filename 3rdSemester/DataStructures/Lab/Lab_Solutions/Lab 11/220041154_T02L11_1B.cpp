#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define enl "\n"
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
void soln() {
    lli n, m;
    cin >> n >> m;
    vector<vector<lli>> lis(n + 1);
    set<lli> degree;
    for (lli i = 0; i < m; i++) {
        lli u, v;
        cin >> u >> v;
        lis[u].push_back(v);
        lis[v].push_back(u);
    }
    for (lli i = 1; i <= n; i++) {
        // cout << i << " -> ";
        // for (auto j : lis[i]) {
        //     cout << j << " ";
        // }
        // cout << enl;
        degree.insert(lis[i].size());
    }
    if (degree.size() == 1) {
        cout << "Yes" << enl;
    } else {
        cout << "No" << enl;
    }
}
int main() {
    fast();
    lli t = 1;
    // cin >> t;
    while (t--) soln();
}
// Author: tashobi_02 //