#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define enl "\n"
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
void soln() {
    lli T, M, N;
    string name, query;
    string qx = "";
    vector<pair<string, string>> wr(T);
    unordered_map<string, lli> freq;
    cin >> T >> M >> N;
    for (lli z = 0; z < T; z++) {
        string qx = "";
        cin >> name;
        wr[z].first = name;

        for (lli i = 0; i < N; i++) {
            cin >> query;
            qx += query;
        }

        wr[z].second = qx;
        freq[qx]++;
    }
    for (auto mx : freq) {
        for (lli i = 0; i < T; i++) {
            if (mx.first == wr[i].second) {
                cout << wr[i].first << " ";
            }
        }
        cout << enl;
    }
}
int main() {
    fast();
    lli t = 1;
    // cin >> t;
    while (t--) soln();
}
// Author: tashobi_02 //