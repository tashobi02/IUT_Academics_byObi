#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
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

void soln() {
    priority_queue<lli> pq;
    lli x;
    while (cin >> x && x != -1) {
        pq.push(x);
    }
    while (pq.size() > 1) {
        lli y = pq.top();
        pq.pop();
        lli x = pq.top();
        pq.pop();
        if (x != y) {
            pq.push(y - x);
        }
    }
    cout << (pq.empty() ? 0 : pq.top()) << endl;
}

int main() {
    fast();
    lli t = 10;
    while (t--) soln();
}
