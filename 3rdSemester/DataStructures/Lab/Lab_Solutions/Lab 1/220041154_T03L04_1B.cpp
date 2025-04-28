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
    vi numbers;
    lli e;
    while(1) {
        cin >> e;
        if(e == -1) {
            break;
        } else {
            numbers.pb(e);
        }
    }
}
