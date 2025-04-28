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
lli heapSize, N;
void min_heapify(vi &heap, lli i) {
    lli l = 2 * i + 1;
    lli r = 2 * i + 2;
    lli smallest = i;
    if (l < heapSize && heap[l] < heap[smallest]) {
        smallest = l;
    }
    if (r < heapSize && heap[r] < heap[smallest]) {
        smallest = r;
    }
    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        min_heapify(heap, smallest);
    }
}
void build_min_heap(vi &heap) {
    heapSize = heap.size();
    N = heap.size();
    for (lli i = heapSize / 2 - 1; i >= 0; i--) {
        min_heapify(heap, i);
    }
}
void heap_sort(vi &heap) {
    build_min_heap(heap);
    for (lli i = heapSize - 1; i > 0; i--) {
        swap(heap[0], heap[i]);
        heapSize--;
        min_heapify(heap, 0);
    }
}
void print_min_heap(vi &heap) {
    cout << "Min Heap: ";
    for (lli i = 0; i < N; i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}
void print_sorted(vi &heap) {
    cout << "Sorted: ";
    for (lli i = 0; i < N; i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}
void soln() {
    lli x;
    vi heap;
    while (1) {
        cin >> x;
        if (x == -1)
            break;
        else
            heap.pb(x);
    }
    build_min_heap(heap);
    print_min_heap(heap);
    heap_sort(heap);
    reverse(heap.begin(), heap.end());
    print_sorted(heap);
}
int main() {
    fast();
    lli t = 1;
    while (t--) soln();
}

// Author: tashobi_02 //
