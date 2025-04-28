#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
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
void circular_enq(lli q[], lli item, lli &rear, lli N, lli &ct) {
    if (ct == N) {
        cout << "Overflow" << endl;
    } else {
        q[rear] = item;
        cout << "EnQueue: " << q[rear] << endl;
        rear = (rear + 1) % N;
        ct++;
    }
}
void circular_deq(lli q[], lli &front, lli N, lli &ct) {
    if (ct == 0) {
        cout << "Underflow" << endl;
    } else {
        cout << "DeQueue: " << q[front] << endl;
        front = (front + 1) % N;
        ct--;
    }
}
lli size(lli ct) { return ct; }
bool isEmpty(lli ct) { return ct == 0; }
bool isFull(lli ct, lli N) { return ct == N; }
lli frontElement(lli q[], lli front, lli ct) {
    if (isEmpty(ct)) {
        cout << "queue is Empty" << endl;
        return -1;
    }
    return q[front];
}
int main() {
    fast();
    lli N;
    cin >> N;
    lli q[N];
    lli front = 0, rear = 0, ct = 0;
    lli action, item;
    while (true) {
        cin >> action;
        if (action == -1) {
            cout << "Exit" << endl;
            break;
        }
        if (action == 1) {
            cin >> item;
            circular_enq(q, item, rear, N, ct);
        } else if (action == 2) {
            circular_deq(q, front, N, ct);
        } else if (action == 3) {
            cout << "isEmpty: " << (isEmpty(ct) ? "True" : "False") << endl;
        } else if (action == 4) {
            cout << "isFull: " << (isFull(ct, N) ? "True" : "False") << endl;
        } else if (action == 5) {
            cout << "Size: " << size(ct) << endl;
        } else if (action == 6) {
            cout << "Front Element: " << frontElement(q, front, ct) << endl;
        }
        cout.flush();
    }
    return 0;
}
