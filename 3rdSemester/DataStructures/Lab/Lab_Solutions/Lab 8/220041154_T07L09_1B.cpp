#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define enl "\n"

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}

void soln() {
    string DNA;
    cin >> DNA;
    lli hashValue = 0;
    string sequence;
    vector<lli> hashValues;
    vector<string> sequences;
    vector<lli> counts;
    for (lli i = 0; i < 10; i++) {
        hashValue += (DNA[i] - 'A' + 1) * pow(10, i);
        sequence.push_back(DNA[i]);
    }
    hashValues.push_back(hashValue);
    sequences.push_back(sequence);
    counts.push_back(1);

    for (lli i = 1; i <= (lli)DNA.size() - 10; i++) {
        bool found = false;
        hashValue -= (DNA[i - 1] - 'A' + 1);
        hashValue /= 10;
        hashValue += (DNA[i + 9] - 'A' + 1) * pow(10, 9);
        sequence = DNA.substr(i, 10);
        for (lli j = 0; j < (lli)sequences.size(); j++) {
            if (sequences[j] == sequence) {
                found = true;
                counts[j]++;
                break;
            }
        }
        if (!found) {
            hashValues.push_back(hashValue);
            sequences.push_back(sequence);
            counts.push_back(1);
        }
    }
    for (lli j = 0; j < (lli)sequences.size(); j++) {
        if (counts[j] > 1) {
            cout << sequences[j] << enl;
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
