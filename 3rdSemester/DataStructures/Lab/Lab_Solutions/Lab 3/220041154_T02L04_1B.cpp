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
lli Heap_Minimum() { return heap[1]; }
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
}
void Heap_decrease_key(lli i, lli value) {
    heap[i] -= value;
    while (i > 1 && heap[parent(i)] > heap[i]) {
        swap(heap[parent(i)], heap[i]);
        i = parent(i);
    }
}
void Heap_increase_key(lli i, lli value) {
    heap[i] += value;
    min_heapify(i);
}
void printHeap() {
    for (lli i = 1; i <= heapSize; i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}
void soln() {
    lli x;
    while (cin >> x && x != -1) {
        Min_heap_insert(x);
    }
    build_min_heap();
    cout << "Min Heap: ";
    printHeap();
    lli func_id;
    while (cin >> func_id && func_id != -1) {
        if (func_id == 1) {
            cout << "Minimum: " << Heap_Minimum() << endl;
        } else if (func_id == 2) {
            cout << "Extracted min: " << Heap_extract_min() << endl;
        } else if (func_id == 3) {
            lli value;
            cin >> value;
            Min_heap_insert(value);
            build_min_heap();
        } else if (func_id == 4) {
            lli index, decrease;
            cin >> index >> decrease;
            Heap_decrease_key(index, decrease);
        } else if (func_id == 5) {
            lli index, increase;
            cin >> index >> increase;
            Heap_increase_key(index, increase);
        }
        cout << "Heap: ";
        printHeap();
        cout.flush();
    }
}
int main() {
    fast();
    lli t = 1;
    while (t--) soln();
}
