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
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
Node* create_node(int x) {
    Node* newNode = new Node();
    newNode->data = x;
    newNode->next = nullptr;
    return newNode;
}

void insert_front(int key) {
    Node* newNode = create_node(key);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
}

void insert_back(int key) {
    Node* newNode = create_node(key);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void insert_after_node(int key, int v) {
    Node* newNode = create_node(key);
    Node* temp = head;
    while (temp != nullptr && temp->data != v) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "Value " << v << " not found." << endl;
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    if (temp == tail) {
        tail = newNode;
    }
}

void update_node(int key, int v) {
    Node* temp = head;
    while (temp != nullptr && temp->data != v) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "Value " << v << " not found." << endl;
        return;
    }
    temp->data = key;
}

void remove_head() {
    if (head == nullptr) {
        cout << "Underflow" << endl;
        return;
    }
    Node* temp = head;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
    cout << "Removed head node." << endl;
}

void remove_element(int key) {
    if (head == nullptr) {
        cout << "Underflow" << endl;
        return;
    }
    if (head->data == key) {
        remove_head();
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr && temp->next->data != key) {
        temp = temp->next;
    }
    if (temp->next == nullptr) {
        cout << "Value " << key << " not found." << endl;
        return;
    }
    Node* to_delete = temp->next;
    temp->next = temp->next->next;
    if (to_delete == tail) {
        tail = temp;
    }
    delete to_delete;
}

void remove_end() {
    if (head == nullptr) {
        cout << "Underflow" << endl;
        return;
    }
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        return;
    }
    Node* temp = head;
    while (temp->next != tail) {
        temp = temp->next;
    }
    delete tail;
    tail = temp;
    tail->next = nullptr;
}

void print_list() {
    if (head == nullptr) {
        cout << "Head = Null, Tail = Null, Empty" << endl;
        return;
    }
    cout << "Head = " << head->data << ",Tail = " << tail->data << ", ";
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    fast();
    int option, value, after;
    while (true) {
        cin >> option;
        if (option == 1) {
            cin >> value;
            insert_front(value);
            print_list();
        } else if (option == 2) {
            cin >> value;
            insert_back(value);
            print_list();
        } else if (option == 3) {
            cin >> value;
            cin >> after;
            insert_after_node(value, after);
            print_list();
        } else if (option == 4) {
            cin >> value;
            cin >> after;
            update_node(value, after);
            print_list();
        } else if (option == 5) {
            remove_head();
            print_list();
        } else if (option == 6) {
            cin >> value;
            remove_element(value);
            print_list();
        } else if (option == 7) {
            remove_end();
            print_list();
        } else if (option == 8) {
            cout << "Exiting program." << endl;
            break;
        } else {
            cout << "Invalid" << endl;
        }
    }
    return 0;
}