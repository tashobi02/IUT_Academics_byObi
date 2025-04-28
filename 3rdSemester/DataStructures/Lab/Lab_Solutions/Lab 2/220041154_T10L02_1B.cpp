#include <algorithm>
#include <cmath>
#include <cstring>
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
void print_q(stack<lli> &enq, stack<lli> &deq, lli N) {
    lli sz = enq.size() + deq.size();
    if (sz == 0) {
        cout << "Size:" << 0 << " Elements: Null";
        return;
    } else if (sz > N) {
        cout << "Size:" << N << " Elements: Overflow!";
        return;
    }
    vi printing;
    stack<lli> temp = deq;
    while (!temp.empty()) {
        printing.pb(temp.top());
        temp.pop();
    }
    temp = enq;
    vi temp_v;
    while (!temp.empty()) {
        temp_v.pb(temp.top());
        temp.pop();
    }
    reverse(temp_v.begin(), temp_v.end());
    for (lli i = 0; i < temp_v.size(); i++) printing.pb(temp_v[i]);
    cout << "Size:" << sz << " Elements: ";
    for (lli i = 0; i < printing.size(); i++) cout << printing[i] << " ";
}
void stack_enq(stack<lli> &enq, stack<lli> &deq, lli q, lli N) {
    if (enq.size() + deq.size() == N) {
        print_q(enq, deq, N);
        return;
    }
    enq.push(q);
    print_q(enq, deq, N);
}
void stack_deq(stack<lli> &enq, stack<lli> &deq, lli N) {
    if (deq.empty()) {
        if (enq.empty()) {
            print_q(enq, deq, N);
            return;
        }
        while (!enq.empty()) {
            deq.push(enq.top());
            enq.pop();
        }
    }
    deq.pop();
    print_q(enq, deq, N);
}
void soln(lli N) {
    lli x, q;
    static stack<lli> enq, deq;
    cin >> x;
    if (x == 1) {
        cin >> q;
        stack_enq(enq, deq, q, N);
    } else if (x == 2) {
        stack_deq(enq, deq, N);
    }
}
int main() {
    fast();
    lli N, Q;
    cin >> N >> Q;
    while (Q--) {
        soln(N);
        cout << endl;
        cout.flush();
    }
    return 0;
}
