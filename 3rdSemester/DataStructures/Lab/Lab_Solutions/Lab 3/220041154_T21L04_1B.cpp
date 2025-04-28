#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
typedef long long int lli;
struct Student {
    string name;
    string department;
    double cgpa;
};
vector<Student> heap(1);
lli heapSize = 0;
lli parent(lli i) { return i / 2; }
lli left(lli i) { return 2 * i; }
lli right(lli i) { return 2 * i + 1; }
void max_heapify(lli i) {
    lli largest = i;
    lli l = left(i);
    lli r = right(i);
    if (l <= heapSize && heap[l].cgpa > heap[largest].cgpa) {
        largest = l;
    }
    if (r <= heapSize && heap[r].cgpa > heap[largest].cgpa) {
        largest = r;
    }
    if (largest != i) {
        swap(heap[i], heap[largest]);
        max_heapify(largest);
    }
}
void Max_heap_insert(Student student) {
    heapSize++;
    if (heapSize >= heap.size()) {
        heap.push_back({"", "", 0});
    }
    heap[heapSize] = student;
    lli i = heapSize;
    while (i > 1 && heap[parent(i)].cgpa < heap[i].cgpa) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}
Student Heap_extract_max() {
    Student max = heap[1];
    heap[1] = heap[heapSize];
    heapSize--;
    max_heapify(1);
    return max;
}
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
void soln() {
    lli n;
    cin >> n;
    cin.ignore();
    string line;
    for (lli i = 0; i < n; i++) {
        getline(cin, line);
        stringstream ss(line);
        Student student;
        string cgpaStr;
        getline(ss, student.name, ',');
        getline(ss, student.department, ',');
        getline(ss, cgpaStr);
        student.cgpa = stod(cgpaStr);
        Max_heap_insert(student);
    }
    vector<string> awards = {"Shiny Gold Medal", "First to lose",
                             "Best among the leftovers"};
    vector<string> output(n);
    for (lli i = 0; i < n; i++) {
        Student student = Heap_extract_max();
        if (i < 3) {
            output[n - 1 - i] = awards[i];
        } else {
            output[n - 1 - i] =
                "Thank you for participating (" + to_string(i - 2) + ")";
        }
    }
    for (const string& result : output) {
        cout << result << endl;
    }
}
int main() {
    fast();
    lli t = 1;
    while (t--) soln();
}
