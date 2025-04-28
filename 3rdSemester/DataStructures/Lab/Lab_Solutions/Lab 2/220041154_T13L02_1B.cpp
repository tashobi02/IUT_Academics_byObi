#include <algorithm>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <string>
using namespace std;
typedef long long int lli;
#define loop(i, n) for (lli i = 0; i < (n); i++)
#define endl "\n"
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}
void soln(lli n) {
    lli z = 1;
    deque<lli> cards;
    loop(i, n) {
        cards.push_back(z);
        z++;
    }
    cout << "Discarded cards: ";
    while (cards.size() > 1) {
        cout << cards.front();
        cards.pop_front();
        if (cards.size() > 1)
            cout << ", ";
        if (cards.size() > 1) {
            cards.push_back(cards.front());
            cards.pop_front();
        }
    }
    cout << endl;
    cout << "Remaining cards: " << cards.front() << endl;
}
int main() {
    fast();
    lli n;
    while (1) {
        cin >> n;
        if (n == 0)
            break;
        else
            soln(n);
        cout.flush();
    }
}