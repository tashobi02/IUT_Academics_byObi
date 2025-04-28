#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
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
    string para;
    getline(cin, para);
    unordered_map<string, lli> freq;
    stringstream ss(para);
    string w;
    while (ss >> w) {
        string cw = "";
        lli sz = w.size();
        for (lli i = 0; i < sz; i++) {
            if ((w[i] >= 97 && w[i] <= 122) || (w[i] >= 65 && w[i] <= 90))
                cw += w[i];
            else
                continue;
        }
        if (!cw.empty())
            freq[cw]++;
    }
    for (const auto& entry : freq) {
        if (entry.second > 1) {
            cout << entry.first << " " << entry.second << endl;
        }
    }
}