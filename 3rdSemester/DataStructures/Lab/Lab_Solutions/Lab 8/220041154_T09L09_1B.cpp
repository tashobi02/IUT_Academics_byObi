#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define enl "\n"

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}

void soln() {
    string s1, s2;
    map<string, string> dictionary;
    while (true) {
        getline(cin, s1);
        if (s1.empty())
            break;
        stringstream ss(s1);
        ss >> s1 >> s2;
        dictionary[s2] = s1;
    }
    string key;
    while (true) {
        getline(cin, key);
        if (key.empty() || key == "exit")
            break;
        if (dictionary.find(key) != dictionary.end()) {
            cout << dictionary[key] << enl;
        } else {
            cout << "eh" << enl;
        }
    }
}

int main() {
    fast();
    lli t = 1;
    while (t--) soln();
    return 0;
}
// Author: tashobi_02 //
