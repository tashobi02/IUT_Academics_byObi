#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
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
#define enl "\n"
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
ld slope(ld x1, ld y1, ld x2, ld y2) {
    if (x2 - x1 == 0) {
        return numeric_limits<ld>::infinity();
    }
    return (y2 - y1) / (x2 - x1);
}

void soln() {
    lli n;
    cin >> n;
    vector<pair<lli, lli>> points(n);
    map<ld, lli> slope_frequency;
    lli inf_count = 0;
    lli xc = 0;
    for (lli i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
        if (points[i].first == 0)
            xc++;
    }
    for (lli i = 0; i < n - 1; i++) {
        for (lli j = i + 1; j < n; j++) {
            ld x1 = (ld)points[i].first;
            ld y1 = (ld)points[i].second;
            ld x2 = (ld)points[j].first;
            ld y2 = (ld)points[j].second;
            ld sl = slope(x1, y1, x2, y2);
            if (sl == numeric_limits<ld>::infinity()) {
                inf_count++;
            } else {
                slope_frequency[sl]++;
            }
        }
    }
    lli ct = 0;
    ld slf;
    // cout << "Infinite Slopes: " << inf_count << enl;
    // cout << "Slope Frequencies:" << enl;
    for (auto px : slope_frequency) {
        // cout << "Slope: " << px.first << ", Count: " << px.second << enl;
        if (ct < px.second) {
            ct = px.second;
            slf = px.first;
        }
    }
    if (inf_count >= ct) {
        cout << "x = 0" << enl;
        cout << xc << enl;
    } else {
        ld X1, Y1;
        for (lli i = 0; i < n - 1; i++) {
            for (lli j = i + 1; j < n; j++) {
                ld x1 = (ld)points[i].first;
                ld y1 = (ld)points[i].second;
                ld x2 = (ld)points[j].first;
                ld y2 = (ld)points[j].second;
                ld sl = slope(x1, y1, x2, y2);
                if (slf == sl) {
                    X1 = (ld)points[i].first;
                    Y1 = (ld)points[i].second;
                    break;
                }
            }
        }
        ld X, Y, Yx, C;
        C = (Y1 - (slf * X1));
        lli ctx = 0;
        for (lli i = 0; i < n; i++) {
            X = (ld)points[i].first;
            Y = (ld)points[i].second;
            Yx = (slf * X) + C;
            if (Yx == Y)
                ctx++;
        }
        cout << "y = " << (slf == 1 ? "" : to_string(slf) + "x")
             << (C == 0 ? ""
                        : (C > 0 ? " + " + to_string(C)
                                 : " - " + to_string(abs(C))))
             << enl;
    }
    cout.flush();
}

int main() {
    fast();
    lli t = 1;
    // cin >> t;
    while (t--) soln();
}
// Author: tashobi_02 //