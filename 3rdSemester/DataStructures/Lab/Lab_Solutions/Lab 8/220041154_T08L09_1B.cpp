#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define enl "\n"

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}

string computeHash(const string& word) {
    set<char> uniqueChars(word.begin(), word.end());
    // for (const auto& i : uniqueChars) {
    //     cout << i << " ";
    // }
    // cout << endl;
    string hashValue(uniqueChars.begin(), uniqueChars.end());
    // cout << "Hash value: " << hashValue << endl;
    return hashValue;
}

void soln() {
    string sentence, target;
    getline(cin, sentence);
    cin >> target;
    string hash = computeHash(target);
    // cout << hash << endl;
    stringstream ss(sentence);
    string word;
    vector<string> matchingWords;
    while (ss >> word) {
        if (computeHash(word) == hash) {
            matchingWords.push_back(word);
        }
    }
    for (const string& match : matchingWords) {
        cout << match << " ";
    }
    cout << enl;
}

int main() {
    fast();
    lli t = 1;
    while (t--) soln();
    return 0;
}
// Author: tashobi_02 //
