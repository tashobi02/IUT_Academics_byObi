#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define endl "\n"

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}

void push(vi &stack, lli element, lli maxSize) {
    if (stack.size() < maxSize) {
        stack.pb(element);
        cout << element << endl;
    } else {
        cout << "Overflow" << endl;
    }
}

void pop(vi &stack) {
    if (!stack.empty()) {
        cout << stack.back() << endl;
        stack.pop_back();
    } else {
        cout << "Underflow" << endl;
    }
}

bool isEmpty(const vi &stack) { return stack.empty(); }

bool isFull(const vi &stack, lli maxSize) { return stack.size() == maxSize; }

lli size(const vi &stack) { return stack.size(); }

lli top(const vi &stack) {
    if (!stack.empty()) {
        return stack.back();
    } else {
        cout << "Underflow" << endl;
        return -1;
    }
}

int main() {
    fast();
    lli N;
    cin >> N;
    vi stack;
    lli maxSize = 5;
    lli functionID, element;
    while (cin >> functionID && functionID != -1) {
        switch (functionID) {
            case 1:
                cin >> element;
                push(stack, element, maxSize);
                break;
            case 2:
                pop(stack);
                break;
            case 3:
                cout << isEmpty(stack) ? "True" : "False") << endl;
                break;
            case 4:
                cout << (isFull(stack, maxSize) ? "Yes" : "No") << endl;
                break;
            case 5:
                cout << size(stack) << endl;
                break;
            case 6:
                cout << top(stack) << endl;
                break;
            default:
                cout << "Invalid function ID" << endl;
                break;
        }
    }
    return 0;
}
