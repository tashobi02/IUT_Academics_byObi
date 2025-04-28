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
void circular_enq(lli q[], lli item, lli &rear, lli N, lli &ct) {
    if (ct == N) {
        cout << "Overflow!!" << endl;
    } else {
        q[rear] = item;
        rear = (rear + 1) % N;
        ct++;
    }
}

void circular_deq(lli &front, lli N, lli &ct) {
    if (ct == 0) {
        cout << "Underflow!!" << endl;
    } else {
        front = (front + 1) % N;
        ct--;
    }
}

bool isEmpty(lli ct) { return ct == 0; }

bool isFull(lli ct, lli N) { return ct == N; }

lli frontElement(lli q[], lli front, lli ct) {
    if (isEmpty(ct)) {
        return -1;
    }
    return q[front];
}

lli rearElement(lli q[], lli rear, lli N, lli ct) {
    if (isEmpty(ct)) {
        return -1;
    }
    return q[(rear + N - 1) % N];
}

void printQueue(lli q[], lli front, lli N, lli ct) {
    if (isEmpty(ct)) {
        cout << "-" << endl;
        return;
    }
    lli i = front;
    lli count = ct;
    while (count--) {
        cout << q[i] << " ";
        i = (i + 1) % N;
    }
    cout << endl;
}

void soln() {
    lli N;
    cin >> N;
    lli q[N];
    lli front = 0, rear = 0, ct = 0;
    string command;
    while (true) {
        cin >> command;
        if (command == "-1") {
            break;
        } else if (command == "E") {
            lli item;
            cin >> item;
            circular_enq(q, item, rear, N, ct);
        } else if (command == "D") {
            circular_deq(front, N, ct);
        }
        cout << "Current Size : " << ct << endl;
        cout << "Full? : " << (isFull(ct, N) ? "Yes" : "No") << endl;
        cout << "Empty? : " << (isEmpty(ct) ? "Yes" : "No") << endl;
        lli front_elem = frontElement(q, front, ct);
        lli rear_elem = rearElement(q, rear, N, ct);
        cout << "Front Element : "
             << (front_elem == -1 ? "-" : to_string(front_elem)) << endl;
        cout << "Front Index : " << (isEmpty(ct) ? 0 : front) << endl;
        cout << "Rear Element : "
             << (rear_elem == -1 ? "-" : to_string(rear_elem)) << endl;
        cout << "Rear Index : " << (isEmpty(ct) ? 0 : (rear + N - 1) % N)
             << endl;
        cout << "Queue Elements : ";
        printQueue(q, front, N, ct);
        cout.flush();
    }
}

int main() {
    fast();
    soln();
    return 0;
}
