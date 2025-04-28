#include <algorithm>
#include <cmath>
#include <cstring>
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
    cout.tie(0);
}
void soln() {
    lli n, x;
    cin >> n;
    deque<lli> piles;
    loop(i, n) {
        cin >> x;
        piles.push_back(x);
    }
    lli c;
    bool d = false;
    lli moves = 0;
    while (piles.size() != 1) {
        if (moves % 2 == 0) {  // Daiyan's move
            c = piles.front();
            piles.pop_front();
            piles.push_back(c);
            piles.pop_front();
            d = true;
        } else {  // Ishraq's move
            c = piles.front();
            piles.pop_front();
            piles.push_back(c);
            c = piles.front();
            piles.pop_front();
            piles.push_back(c);
            piles.pop_front();
            d = false;
        }
        moves++;
    }
    if (d) {
        cout << "Daiyan " << piles.front() << endl;
    } else {
        cout << "Ishraq " << piles.front() << endl;
    }
}
int main() {
    lli t = 1;
    cin >> t;
    while (t--) soln();
}