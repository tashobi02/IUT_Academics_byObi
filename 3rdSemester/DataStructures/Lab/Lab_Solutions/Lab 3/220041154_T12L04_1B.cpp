#include <algorithm>
#include <cmath>
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
}
vector<lli> heap(1);
lli heapSize = 0;
lli parent(lli i) { return i / 2; }
lli left(lli i) { return 2 * i; }
lli right(lli i) { return 2 * i + 1; }
void min_heapify(lli i) {
    lli smallest = i;
    lli li = left(i);
    lli ri = right(i);
    if (li <= heapSize && heap[li] < heap[smallest]) {
        smallest = li;
    }
    if (ri <= heapSize && heap[ri] < heap[smallest]) {
        smallest = ri;
    }
    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        min_heapify(smallest);
    }
}
void build_min_heap() {
    for (lli i = heapSize / 2; i >= 1; i--) {
        min_heapify(i);
    }
}
lli Heap_extract_min() {
    lli min = heap[1];
    heap[1] = heap[heapSize];
    heapSize--;
    min_heapify(1);
    return min;
}
void Min_heap_insert(lli key) {
    heapSize++;
    if (heapSize >= heap.size()) {
        heap.pb(0);
    }
    heap[heapSize] = key;
    lli i = heapSize;
    while (i > 1 && heap[parent(i)] > heap[i]) {
        swap(heap[parent(i)], heap[i]);
        i = parent(i);
    }
}
void soln() {
    lli num;
    heapSize = 0;
    heap.resize(1);
    while (cin >> num && num != -1) {
        Min_heap_insert(num);
    }
    lli totalCost = 0;
    while (heapSize > 1) {
        lli first = Heap_extract_min();
        lli second = Heap_extract_min();
        lli cost = first + second;
        totalCost += cost;
        Min_heap_insert(cost);
    }
    cout << totalCost << endl;
}
int main() {
    fast();
    lli t = 1;
    while (t--) soln();
}
