#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define enl "\n"
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
void soln() {
    lli n, e, q;
    cin >> n >> e >> q;
    unordered_set<string> citySet;
    vector<string> cities(n);
    for (lli i = 0; i < n; i++) {
        cin >> cities[i];
        citySet.insert(cities[i]);
    }
    unordered_map<string, vector<string>> graph;
    for (lli i = 0; i < e; i++) {
        string city1, city2;
        cin >> city1 >> city2;
        graph[city1].push_back(city2);
        graph[city2].push_back(city1);
    }
    while (q--) {
        string src, dst;
        lli k;
        cin >> src >> dst >> k;
        if (citySet.find(src) == citySet.end() ||
            citySet.find(dst) == citySet.end()) {
            cout << "NO" << enl;
            continue;
        }
        queue<pair<string, vector<string>>> q;
        unordered_set<string> visited;
        q.push({src, {src}});
        visited.insert(src);
        bool found = false;
        while (!q.empty()) {
            auto [node, path] = q.front();
            q.pop();
            if (node == dst) {
                if ((path.size() - 1) % k == 0) {
                    for (lli i = 0; i < (lli)path.size(); i++) {
                        cout << path[i];
                        if (i < (lli)path.size() - 1)
                            cout << " ";
                    }
                    cout << enl;
                } else {
                    cout << "NO" << enl;
                }
                found = true;
                break;
            }
            for (auto &neighbor : graph[node]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    vector<string> newPath = path;
                    newPath.push_back(neighbor);
                    q.push({neighbor, newPath});
                }
            }
        }
        if (!found)
            cout << "NO" << enl;
    }
}
int main() {
    fast();
    lli t = 1;
    // cin >> t;
    while (t--) soln();
    return 0;
}
