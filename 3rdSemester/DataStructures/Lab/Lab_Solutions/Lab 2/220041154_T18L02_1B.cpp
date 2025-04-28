#include <iostream>
#include <string>
using namespace std;
typedef long long int lli;

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}

lli frontIndex(lli front) { return front; }

lli rearIndex(lli rear, lli N, lli ct) {
    if (ct == 0)
        return -1;
    return (rear - 1 + N) % N;
}

bool isFull(lli ct, lli N) { return ct == N; }

bool isEmpty(lli ct) { return ct == 0; }

lli size(lli ct) { return ct; }

void push_front(lli q[], lli &front, lli N, lli &ct, lli x) {
    if (isFull(ct, N)) {
        cout << "Overflow" << endl;
        return;
    }
    front = (front - 1 + N) % N;
    q[front] = x;
    ct++;
}

void push_back(lli q[], lli &rear, lli N, lli &ct, lli x) {
    if (isFull(ct, N)) {
        cout << "Overflow" << endl;
        return;
    }
    q[rear] = x;
    rear = (rear + 1) % N;
    ct++;
}

lli pop_front(lli q[], lli &front, lli N, lli &ct) {
    if (isEmpty(ct)) {
        cout << "Underflow" << endl;
        return -1;
    }
    lli x = q[front];
    front = (front + 1) % N;
    ct--;
    return x;
}

lli pop_back(lli q[], lli &rear, lli N, lli &ct) {
    if (isEmpty(ct)) {
        cout << "Underflow" << endl;
        return -1;
    }
    rear = (rear - 1 + N) % N;
    lli x = q[rear];
    ct--;
    return x;
}

void printDeque(lli q[], lli front, lli N, lli ct) {
    if (isEmpty(ct))
        return;
    lli count = ct;
    while (count--) {
        cout << q[front] << " ";
        front = (front + 1) % N;
    }
    cout << endl;
}

void soln() {
    lli N;
    cin >> N;
    lli q[N];
    lli front = 0, rear = 0, ct = 0;
    string cmd;
    lli x;
    while (true) {
        cin >> cmd;
        if (cmd == "E")
            break;
        if (cmd == "PF") {
            cin >> x;
            push_front(q, front, N, ct, x);
            printDeque(q, front, N, ct);
        } else if (cmd == "PB") {
            cin >> x;
            push_back(q, rear, N, ct, x);
            printDeque(q, front, N, ct);
        } else if (cmd == "DF") {
            x = pop_front(q, front, N, ct);
            if (x != -1)
                printDeque(q, front, N, ct);
        } else if (cmd == "DB") {
            x = pop_back(q, rear, N, ct);
            if (x != -1)
                printDeque(q, front, N, ct);
        } else if (cmd == "S") {
            cout << size(ct) << endl;
        } else if (cmd == "F") {
            cout << frontIndex(front) << endl;
        } else if (cmd == "R") {
            cout << rearIndex(rear, N, ct) << endl;
        } else if (cmd == "STAT") {
            if (isFull(ct, N))
                cout << "FULL" << endl;
            else if (isEmpty(ct))
                cout << "EMPTY" << endl;
            else
                cout << "NONE" << endl;
        }
    }
}

int main() {
    fast();
    soln();
    return 0;
}
