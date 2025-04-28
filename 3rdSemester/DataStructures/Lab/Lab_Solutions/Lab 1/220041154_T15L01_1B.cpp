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
bool isFull(vi &stack, lli n) { return stack.size() == n; }
bool isEmpty(vi &stack) { return stack.size() == 0; }
void push(vi &stack, lli n, lli x) {
    if (!isFull(stack, n)) {
        stack.pb(x);
        cout << "Size : " << stack.size() << endl;
        cout << "Stack elements : ";
        for (lli i : stack) cout << i << " ";
        cout << endl;
        cout << "Top Element : " << stack.back() << endl;
        cout << "isFull : " << (isFull(stack, n) ? "True" : "False") << endl;
        cout << "isEmpty : " << (isEmpty(stack) ? "True" : "False") << endl;
    } else {
        cout << "Overflow !!!" << endl;
        cout << "Size : " << stack.size() << endl;
        cout << "Stack elements : ";
        for (lli i : stack) cout << i << " ";
        cout << endl;
        cout << "Top Element : " << stack.back() << endl;
        cout << "isFull : True" << endl;
        cout << "isEmpty : False" << endl;
    }
}
void pop(vi &stack) {
    if (!isEmpty(stack)) {
        stack.pop_back();
        cout << "Size : " << stack.size() << endl;
        cout << "Stack elements : ";
        for (lli i : stack) cout << i << " ";
        cout << endl;
        if (!stack.empty())
            cout << "Top Element : " << stack.back() << endl;
        else
            cout << "Top Element : 0" << endl;
        cout << "isFull : False" << endl;
        cout << "isEmpty : " << (isEmpty(stack) ? "True" : "False") << endl;
    } else {
        cout << "Stack is empty!" << endl;
    }
}
void soln() {
    lli n;
    cin >> n;
    vi stack;
    string command;
    while (true) {
        cin >> command;
        if (command == "/")
            break;
        if (command == "+") {
            lli x;
            cin >> x;
            push(stack, n, x);
        } else if (command == "-") {
            pop(stack);
        }
        cout.flush();
    }
}
int main() {
    fast();
    soln();
}
