#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
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
#define all(v) v.begin(), v.end()
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}

class HashTable {
   public:
    vi table;
    lli size;
    lli ct;
    lli cc;
    HashTable(lli cc, lli sz) : cc(cc), size(sz), ct(0) {
        table.assign(sz, -1);
    }
    lli hash1(lli x) { return x % size; }
    lli hash2(lli x) {
        lli R = 7;
        return R - (x % R);
    }
    lli probe(lli x, lli i) {
        if (cc == 1) {  // Linear Probing
            return (hash1(x) + i) % size;
        } else if (cc == 2) {  // Quadratic Probing
            return (hash1(x) + i * i) % size;
        } else if (cc == 3) {  // Double Hashing
            return (hash1(x) + i * hash2(x)) % size;
        }
        return -1;
    }
    void insert(lli x) {
        lli i = 0;
        while (i < 6) {
            lli index = probe(x, i);
            if (table[index] == -1) {
                table[index] = x;
                ct++;
                cout << "Inserted : Index - " << index << " (L.F = " << fixed
                     << setprecision(3) << (double)ct / size << ")" << endl;
                return;
            } else {
                cout << "Collision: Index - " << index << endl;
            }
            i++;
        }
        cout << "Input Abandoned" << endl;
        cout.flush();
    }
};
int main() {
    lli cc, sz, q;
    cin >> cc >> sz >> q;
    HashTable hashTable(cc, sz);
    loop(i, q) {
        lli x;
        cin >> x;
        hashTable.insert(x);
    }
    return 0;
}
