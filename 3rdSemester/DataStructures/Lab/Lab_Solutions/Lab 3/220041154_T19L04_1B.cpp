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
void max_heapify(lli i) {
    lli largest = i;
    lli li = left(i);
    lli ri = right(i);
    if (li <= heapSize && heap[li] > heap[largest]) {
        largest = li;
    }
    if (ri <= heapSize && heap[ri] > heap[largest]) {
        largest = ri;
    }
    if (largest != i) {
        swap(heap[i], heap[largest]);
        max_heapify(largest);
    }
}
void build_max_heap() {
    for (lli i = heapSize / 2; i >= 1; i--) {
        max_heapify(i);
    }
}
lli Heap_Maximum() { return heap[1]; }
lli Heap_extract_max() {
    lli max = heap[1];
    heap[1] = heap[heapSize];
    heapSize--;
    max_heapify(1);
    return max;
}
void Max_heap_insert(lli key) {
    heapSize++;
    if (heapSize >= heap.size()) {
        heap.pb(0);
    }
    heap[heapSize] = key;
    lli i = heapSize;
    while (i > 1 && heap[parent(i)] < heap[i]) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}
void Heap_decrease_key(lli i, lli value) {
    heap[i] -= value;
    max_heapify(i);
}
void Heap_increase_key(lli i, lli value) {
    heap[i] += value;
    while (i > 1 && heap[parent(i)] < heap[i]) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
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
        Max_heap_insert(x);
    }
    build_max_heap();
    cout << "Max Heap: ";
    printHeap();
    lli func_id;
    while (cin >> func_id && func_id != -1) {
        if (func_id == 1) {
            cout << "Maximum: " << Heap_Maximum() << endl;
        } else if (func_id == 2) {
            cout << "Extracted max: " << Heap_extract_max() << endl;
        } else if (func_id == 3) {
            lli value;
            cin >> value;
            Max_heap_insert(value);
            build_max_heap();
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
