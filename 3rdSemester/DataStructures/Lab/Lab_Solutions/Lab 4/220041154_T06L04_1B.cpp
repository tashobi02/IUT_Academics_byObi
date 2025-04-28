#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Node {
    int data;
    Node* next;
};
Node* head = nullptr;
Node* tail = nullptr;
Node* create_node(int x) {
    Node* newNode = new Node();
    newNode->data = x;
    newNode->next = nullptr;
    return newNode;
}
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
int getSize(Node* head) {
    int size = 0;
    Node* current = head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}
void push(int key) {
    Node* newNode = create_node(key);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
}
void pop() {
    Node* temp = head;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
}
void top() {
    Node* temp = head;
    while (temp != nullptr) {
        temp = temp->next;
        if (temp->next == nullptr) {
            cout << temp->data << endl;
            break;
        }
    }
}
void print_list(Node* current) {
    if (current == nullptr) {
        return;
    }
    print_list(current->next);
    cout << current->data << " ";
}
int main() {
    fast();
    int N;
    cin >> N;
    int id, value;
    while (1) {
        cin >> id;
        if (id == 1) {
            if (getSize(head) == N) {
                cout << "Overflow" << endl;
            } else {
                cin >> value;
                push(value);
                print_list(head);
                cout << endl;
            }
        } else if (id == 2) {
            if (getSize(head) == 0) {
                cout << "Underflow" << endl;
            } else {
                pop();
                print_list(head);
                cout << endl;
            }
        } else if (id == 3) {
            if (getSize(head) == 0) {
                cout << "True" << endl;
            } else {
                cout << "False" << endl;
            }
        } else if (id == 4) {
            if (getSize(head) == N) {
                cout << "True" << endl;
            } else {
                cout << "False" << endl;
            }
        } else if (id == 5) {
            cout << getSize(head) << endl;
        } else if (id == 6) {
        } else if (id == -1) {
            return 0;
        }
        cout.flush();
    }
}