#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>
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
    lli n;
    cin >> n;
    vi heights(n);
    loop(i, n) cin >> heights[i];
    stack<pair<lli, lli>> calc;
    lli maxArea = 0;
    lli start, height, index;
    loop(i, n) {
        start = i;
        while (!calc.empty() && calc.top().second > heights[i]) {
            height = calc.top().second;
            index = calc.top().first;
            calc.pop();
            maxArea = max(maxArea, height * (i - index));
            start = index;
        }
        calc.push({start, heights[i]});
    }
    while (!calc.empty()) {
        lli height = calc.top().second;
        lli index = calc.top().first;
        calc.pop();
        maxArea = max(maxArea, height * (n - index));
    }
    cout << maxArea << endl;
}
int main() {
    fast();
    soln();
}
