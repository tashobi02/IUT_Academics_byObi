#include <algorithm>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <stack>
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
    lli n, x, q = 0;
    cin >> n;
    deque<lli> students;
    stack<lli> dishes;
    cout << "Students: ";
    cout.flush();
    loop(i, n) {
        cin >> x;
        students.push_back(x);
    }
    cout << "Dishes: ";
    cout.flush();
    loop(i, n) {
        cin >> x;
        dishes.push(x);
    }
    while (!dishes.empty()) {
        if (students.front() == dishes.top()) {
            dishes.pop();
            students.pop_front();
            q = 0;
        } else {
            x = students.front();
            q++;
        }
        if (q >= dishes.size())
            break;
        students.pop_front();
        students.push_back(x);
    }
    cout << students.size() << endl;
}
int main() {
    fast();
    soln();
}
