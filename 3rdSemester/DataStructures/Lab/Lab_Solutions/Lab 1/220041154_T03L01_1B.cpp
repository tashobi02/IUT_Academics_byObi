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
    lli l;
    vi num;
    while(1) {
        cin >> l;
        if(l == -1) {
            break;
        } else {
            num.pb(l);
        }
    }
    lli s, k = 1;
    cin >> s;
    loop(i, s) {
        if(num[i] == k) {
            cout << "Push ";
            k++;
            if(num[i] == s) {
                break;
            }
        } else {
            cout << "Push Pop ";
            k++;
            i--;
        }
    }
    return 0;
}
