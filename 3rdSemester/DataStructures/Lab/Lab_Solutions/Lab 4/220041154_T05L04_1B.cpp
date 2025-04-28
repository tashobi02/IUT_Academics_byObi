#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
void insertNode(Node*& head, int data) {
    Node* newNode = new Node(data);
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
void intersections(Node* list1, Node* list2) {
    Node* ptr1 = list1;
    Node* ptr2 = list2;
    bool found = false;
    while (ptr1 != nullptr && ptr2 != nullptr) {
        if (ptr1->data == ptr2->data) {
            cout << ptr1->data << " ";
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
            found = true;
        } else if (ptr1->data < ptr2->data) {
            ptr1 = ptr1->next;
        } else {
            ptr2 = ptr2->next;
        }
    }
    if (!found)
        cout << "Empty" << endl;
    cout << endl;
}
int main() {
    fast();
    Node* list1 = nullptr;
    Node* list2 = nullptr;
    int x;
    while (1) {
        cin >> x;
        if (x == -1)
            break;
        else {
            insertNode(list1, x);
        }
    }
    while (1) {
        cin >> x;
        if (x == -1)
            break;
        else {
            insertNode(list2, x);
        }
    }
    intersections(list1, list2);
}

