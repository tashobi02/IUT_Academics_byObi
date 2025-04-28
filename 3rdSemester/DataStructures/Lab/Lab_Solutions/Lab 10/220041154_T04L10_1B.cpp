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
vector<pair<lli, lli>> redundant;
vector<tuple<lli, lli, lli, lli>> replacements;
void make(lli v) {
    parent[v] = v;
    sz[v] = 1;
}
lli find(lli v) {
    if (v == parent[v])
        return v;
    return parent[v] = find(parent[v]);
}
bool Union(lli a, lli b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (sz[a] < sz[b])
            swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
    return false;
}
int main() {
    fast();
    lli n;
    cin >> n;
    vector<pair<lli, lli>> edges;
    for (lli i = 1; i <= n; i++) {
        make(i);
    }
    for (lli i = 1; i < n; i++) {
        lli u, v;
        cin >> u >> v;
        if (!Union(u, v)) {
            redundant.push_back({u, v});
        }
    }
    vector<lli> components;
    for (lli i = 1; i <= n; i++) {
        if (find(i) == i) {
            components.push_back(i);
        }
    }
    for (lli i = 1; i < (lli)components.size(); i++) {
        if (!redundant.empty()) {
            lli old_u = redundant.back().first;
            lli old_v = redundant.back().second;
            redundant.pop_back();
            lli new_u = components[i - 1];
            lli new_v = components[i];
            replacements.push_back({old_u, old_v, new_u, new_v});
            Union(new_u, new_v);
        }
    }
    cout << replacements.size() << enl;
    for (auto [old_u, old_v, new_u, new_v] : replacements) {
        cout << old_u << " " << old_v << "  " << new_u << " " << new_v << enl;
    }
    return 0;
}
