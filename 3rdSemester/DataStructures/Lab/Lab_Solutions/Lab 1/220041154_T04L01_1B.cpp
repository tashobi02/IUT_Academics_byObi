#include <iostream>
#include <stack>
#include <vector>

using namespace std;
typedef long long int lli;
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
int main() {
    fast();
    vector<lli> numbers;
    stack<lli> nums;
    vector<lli> nge;
    while (true) {
        lli e;
        cin >> e;
        if (e == -1) {
            break;
        }
        numbers.push_back(e);
    }
    lli sz = numbers.size();
    nge.resize(sz, -1);
    for (lli i = 0; i < sz; ++i) {
        while (!nums.empty() && numbers[nums.top()] < numbers[i]) {
            nge[nums.top()] = numbers[i];
            nums.pop();
        }
        nums.push(i);
    }
    for (lli i = 0; i < sz; ++i) {
        cout << nge[i] << " ";
    }
    cout << endl;
    return 0;
}
