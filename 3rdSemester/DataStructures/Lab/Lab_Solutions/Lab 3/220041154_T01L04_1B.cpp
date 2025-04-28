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
lli heapSize;
lli N;
void max_heapify(vi &heap, lli i) {
    lli l = 2 * i + 1;
    lli r = 2 * i + 2;
    lli largest = i;
    if (l < heapSize && heap[l] > heap[largest]) {
        largest = l;
    }
    if (r < heapSize && heap[r] > heap[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(heap[i], heap[largest]);
        max_heapify(heap, largest);
    }
}

void build_max_heap(vi &heap) {
    heapSize = heap.size();
    N = heap.size();
    for (lli i = heapSize / 2 - 1; i >= 0; i--) {
        max_heapify(heap, i);
    }
}

void heap_sort(vi &heap) {
    build_max_heap(heap);
    for (lli i = heapSize - 1; i > 0; i--) {
        swap(heap[0], heap[i]);
        heapSize--;
        max_heapify(heap, 0);
    }
}

void print_max_heap(vi &heap) {
    cout << "Max Heap: ";
    for (lli i = N - 1; i >= 0; i--) {
        cout << heap[i] << " ";
    }
    cout << endl;
}

void print_sorted(vi &heap) {
    cout << "Sorted: ";
    for (lli i = N - 1; i >= 0; i--) {
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
    heap_sort(heap);
    print_max_heap(heap);
    print_sorted(heap);
}
int main() {
    fast();
    lli t = 1;
    while (t--) soln();
}
