#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long int lli;
typedef vector<long long int> vi;
#define pb push_back
#define loop(i, n) for (lli i = 0; i < (n); i++)
#define endl "\n"

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}

int main() {
    fast();
    lli n;
    cin >> n;
    cin.ignore();
    stack<string> tagStack;
    vector<string> lines(n);
    loop(i, n) {
        getline(cin, lines[i]);
    }
    for (lli i = 0; i < n; i++) {
        lli len = lines[i].size();
        for (lli j = 0; j < len; j++) {
            if (lines[i][j] == '<') {
                string tag;
                lli k = j + 1;
                while (k < len && lines[i][k] != '>') {
                    tag += lines[i][k];
                    k++;
                }
                j = k;
                if (tag.empty() || tag[0] == '/' && tag.size() == 1) continue;
                if (tag[0] != '/') {
                    tagStack.push(tag);
                } else {
                    tag = tag.substr(1);
                    if (tagStack.empty() || tagStack.top() != tag) {
                        cout << "Error at line " << i + 1 << endl;
                        return 0;
                    } else {
                        tagStack.pop();
                    }
                }
            }
        }
    }
    if (!tagStack.empty()) {
        cout << "Error at line " << n << endl;
    } else {
        cout << "No error" << endl;
    }

    return 0;
}
