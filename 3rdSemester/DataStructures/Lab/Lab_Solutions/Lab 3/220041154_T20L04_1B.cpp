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
    lli n, k;
    cin >> n;
    vi arr(n);
    loop(i, n) {
        lli a;
        cin >> a;
        arr[i] = a;
    }
    cin >> k;
    priority_queue<lli> pq;
    loop(i, n) {
        pq.push(arr[i]);
        lli total = arr[i];
        for (lli j = i + 1; j < n; j++) {
            total += arr[j];
            pq.push(total);
        }
    }
    for (lli i = 0; i < k - 1; i++) {
        pq.pop();
    }
    cout << pq.top() << endl;
}
int main() {
    fast();
    soln();
}