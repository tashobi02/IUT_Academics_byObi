#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
typedef long long int lli;
typedef long double ld;
typedef vector<long long int> vi;
#define pb push_back
#define loop(i, n) for (lli i = 0; i < (n); i++)
#define endl "\n"
#define py cout << "YES" << endl
#define pn cout << "NO" << endl

struct Wizard {
    string name;
    lli age;
    string house;
    lli order;
    bool operator<(const Wizard &other) const {
        if (age == other.age)
            return order > other.order;
        return age < other.age;
    }
};

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}

void soln() {
    priority_queue<Wizard> pq;
    lli order = 0;
    string cmd;
    while (cin >> cmd) {
        if (cmd == "I") {
            string name, house, dummy;
            lli age;
            getline(cin, dummy);
            getline(cin, name, ',');
            cin >> age;
            getline(cin, dummy);
            cin >> house;
            pq.push({name, age, house, order++});
        } else if (cmd == "S") {
            if (!pq.empty()) {
                Wizard top = pq.top();
                cout << "Name: " << top.name << ", Age: " << top.age
                     << ", House: " << top.house << endl;
                pq.pop();
            }
        } else if (cmd == "X") {
            break;
        }
        cout.flush();
    }
}

int main() {
    fast();
    soln();
    return 0;
}
