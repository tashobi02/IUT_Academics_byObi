#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define enl "\n"
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
void soln() {
    vector<string> morse = {
        ".-",   "-...", "-.-.", "-..",  ".",   "..-.", "--.",  "....", "..",
        ".---", "-.-",  ".-..", "--",   "-.",  "---",  ".--.", "--.-", ".-.",
        "...",  "-",    "..-",  "...-", ".--", "-..-", "-.--", "--.."};
    lli n;
    string q, qm = "";
    unordered_map<string, lli> freq;
    cin >> n;
    while (n--) {
        cin >> q;
        lli sz = q.size();
        for (lli i = 0; i < sz; i++) {
            qm += morse[q[i] - 'a'];
        }
        freq[qm]++;
        qm = "";
    }
    cout << freq.size() << endl;
    for (auto mx : freq) {
        cout << mx.first << endl;
    }
}
int main() {
    fast();
    lli t = 1;
    // cin >> t;
    while (t--) soln();
}
// Author: tashobi_02 //