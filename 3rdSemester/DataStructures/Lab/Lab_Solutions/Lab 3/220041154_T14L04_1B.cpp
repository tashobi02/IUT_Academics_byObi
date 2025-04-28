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
lli Heap_extract_min() {
    if (heapSize == 0) {
        throw runtime_error("Heap underflow");
    }
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
void printProductOfTop3(vector<lli>& A) {
    vector<lli> top3Heap(1);
    for (lli i = 0; i < A.size(); i++) {
        Min_heap_insert(A[i]);
        if (heapSize > 3) {
            Heap_extract_min();
        }
        if (heapSize < 3) {
            cout << "-1" << endl;
        } else {
            lli product = heap[1] * heap[2] * heap[3];
            cout << product << endl;
        }
    }
}
void soln() {
    lli N;
    cin >> N;
    vector<lli> A(N);
    loop(i, N) { cin >> A[i]; }
    printProductOfTop3(A);
}
int main() {
    fast();
    lli t = 1;
    while (t--) soln();
}
