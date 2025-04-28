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
void print_queue(lli deque[], lli front, lli rear, lli ct, lli N) {
    if (ct == 0) {
        cout << "Deque is empty" << endl;
        return;
    }
    for (lli i = 0; i < ct; i++) {
        cout << deque[(front + i) % N] << " ";
    }
    cout << endl;
}
void push_front(lli deque[], lli &front, lli &rear, lli &ct, lli N, lli key) {
    if (ct == N) {
        cout << "Overflow" << endl;
        return;
    }
    if (front == -1) {
        front = 0;
        rear = 0;
    } else {
        front = (front - 1 + N) % N;
    }
    deque[front] = key;
    ct++;
    print_queue(deque, front, rear, ct, N);
}
void push_back(lli deque[], lli &front, lli &rear, lli &ct, lli N, lli key) {
    if (ct == N) {
        cout << "Overflow" << endl;
        return;
    }
    if (rear == -1) {
        front = 0;
        rear = 0;
    } else {
        rear = (rear + 1) % N;
    }
    deque[rear] = key;
    ct++;
    print_queue(deque, front, rear, ct, N);
}
void pop_front(lli deque[], lli &front, lli &rear, lli &ct, lli N) {
    if (ct == 0) {
        cout << "Underflow" << endl;
        return;
    }
    front = (front + 1) % N;
    ct--;
    print_queue(deque, front, rear, ct, N);
}
void pop_back(lli deque[], lli &front, lli &rear, lli &ct, lli N) {
    if (ct == 0) {
        cout << "Underflow" << endl;
        return;
    }
    rear = (rear - 1 + N) % N;
    ct--;
    print_queue(deque, front, rear, ct, N);
}
lli size(lli ct) { return ct; }
int main() {
    lli N = 100;
    lli deque[N];
    lli front = -1, rear = -1, ct = 0;
    lli action, key;
    while (true) {
        cin >> action;
        if (action == 6) {
            cout << "Exit" << endl;
            break;
        }
        if (action == 1) {
            cin >> key;
            push_front(deque, front, rear, ct, N, key);
        } else if (action == 2) {
            cin >> key;
            push_back(deque, front, rear, ct, N, key);
        } else if (action == 3) {
            pop_front(deque, front, rear, ct, N);
        } else if (action == 4) {
            pop_back(deque, front, rear, ct, N);
        } else if (action == 5) {
            cout << size(ct) << endl;
        }
    }
    return 0;
}
