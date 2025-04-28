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
queue<lli> q1, q2;
lli maxSize;
void push(lli x) {
    if (q1.size() == maxSize) {
        cout << "Overflow!!" << endl;
        return;
    }
    q2.push(x);
    while (!q1.empty()) {
        q2.push(q1.front());
        q1.pop();
    }
    swap(q1, q2);
}
void pop() {
    if (q1.empty()) {
        cout << "Underflow!!" << endl;
    } else {
        q1.pop();
    }
}
bool isFull() { return q1.size() == maxSize; }
bool isEmpty() { return q1.empty(); }
lli top() {
    if (isEmpty()) {
        return -1;
    } else {
        return q1.front();
    }
}
lli size() { return q1.size(); }
void printStack() {
    if (isEmpty()) {
        return;
    }
    vector<lli> temp;
    queue<lli> q = q1;
    while (!q.empty()) {
        temp.pb(q.front());
        q.pop();
    }
    for (lli i = temp.size() - 1; i >= 0; i--) {
        cout << temp[i] << " ";
    }
    cout << endl;
}
void soln() {
    lli N;
    cin >> N;
    maxSize = N;
    string cmd;
    lli x;
    while (true) {
        cin >> cmd;
        if (cmd == "-1")
            break;
        if (cmd == "push") {
            cin >> x;
            push(x);
            printStack();
        } else if (cmd == "pop") {
            pop();
            printStack();
        } else if (cmd == "isFull") {
            cout << (isFull() ? "Yes" : "No") << endl;
        } else if (cmd == "isEmpty") {
            cout << (isEmpty() ? "Yes" : "No") << endl;
        } else if (cmd == "top") {
            lli topElement = top();
            if (topElement == -1) {
                cout << "Empty Stack" << endl;
            } else {
                cout << topElement << endl;
            }
        } else if (cmd == "size") {
            cout << size() << endl;
        }
        cout.flush();
    }
}

int main() {
    fast();
    soln();
    return 0;
}
