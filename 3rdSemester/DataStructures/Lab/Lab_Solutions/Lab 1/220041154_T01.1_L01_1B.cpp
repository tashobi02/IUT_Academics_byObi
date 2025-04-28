#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
typedef long long int lli;
#define endl "\n"
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}

void push(stack<lli> &s, lli element, lli maxSize) {
    if (s.size() < maxSize) {
        s.push(element);
        cout << element << endl;
    } else {
        cout << "Overflow" << endl;
    }
}

void pop(stack<lli> &s) {
    if (!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    } else {
        cout << "Underflow" << endl;
    }
}

bool isEmpty(const stack<lli> &s) { return s.empty(); }

bool isFull(const stack<lli> &s, lli maxSize) { return s.size() == maxSize; }

lli size(const stack<lli> &s) { return s.size(); }

lli top(const stack<lli> &s) {
    if (!s.empty()) {
        return s.top();
    } else {
        cout << "Underflow" << endl;
        return -1;
    }
}

int main() {
    fast();
    lli N;
    cin >> N;
    stack<lli> s;
    lli maxSize = 5;
    lli functionID, element;

    while (cin >> functionID && functionID != -1) {
        switch (functionID) {
            case 1:
                cin >> element;
                push(s, element, maxSize);
                break;
            case 2:
                pop(s);
                break;
            case 3:
                cout << (isEmpty(s) ? "True" : "False") << endl;
                break;
            case 4:
                cout << (isFull(s, maxSize) ? "Yes" : "No") << endl;
                break;
            case 5:
                cout << size(s) << endl;
                break;
            case 6:
                cout << top(s) << endl;
                break;
            default:
                cout << "Invalid function ID" << endl;
                break;
        }
    }

    return 0;
}
