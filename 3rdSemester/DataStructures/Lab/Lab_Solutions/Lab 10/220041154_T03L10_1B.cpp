#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define enl "\n"
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
const lli N = 1e5 + 10;
lli parent[N], sz[N];
lli components, max_size;
void make(lli v) {
    parent[v] = v;
    sz[v] = 1;
}
lli find(lli v) {
    if (v == parent[v])
        return v;
    return parent[v] = find(parent[v]);  // Path Compression
}
void Union(lli a, lli b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (sz[a] < sz[b])
            swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        components--;
        max_size = max(max_size, sz[a]);
    }
}
int main() {
    fast();
    lli n, m;
    cin >> n >> m;
    components = n;
    max_size = 1;
    for (lli i = 1; i <= n; i++) {
        make(i);
    }
    while (m--) {
        lli u, v;
        cin >> u >> v;
        Union(u, v);
        cout << components << " " << max_size << endl;
    }
    return 0;
}
