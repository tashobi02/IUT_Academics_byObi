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
    lli n, c, x, scenario = 1;
    while (true) {
        cin >> n;
        if (n == 0)
            break;
        cout << "Scenario #" << scenario++ << endl;
        vector<lli> person(1000000, -1);
        vector<deque<lli>> circles(n);
        queue<lli> queue_order;
        vector<bool> c_queue(n, false);
        loop(i, n) {
            cin >> c;
            while (c--) {
                cin >> x;
                person[x] = i;
            }
        }
        string cmd;
        while (cin >> cmd && cmd != "STOP") {
            if (cmd == "ENQUEUE") {
                cin >> x;
                lli c_id = person[x];
                if (!c_queue[c_id]) {
                    queue_order.push(c_id);
                    c_queue[c_id] = true;
                }
                circles[c_id].push_back(x);
            } else if (cmd == "DEQUEUE") {
                lli front_circle = queue_order.front();
                cout << circles[front_circle].front() << endl;
                circles[front_circle].pop_front();
                if (circles[front_circle].empty()) {
                    queue_order.pop();
                    c_queue[front_circle] = false;
                }
            }
        }
        cout << endl;
        cout.flush();
    }
}
int main() {
    fast();
    soln();
}
