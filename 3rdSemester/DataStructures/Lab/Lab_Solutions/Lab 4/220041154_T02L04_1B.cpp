#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Node {
    int data;
    Node* next;
    Node* prev;
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
    newNode->prev = nullptr;
    return newNode;
}
void insert_front(int key) {
    Node* newNode = create_node(key);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}
void insert_back(int key) {
    Node* newNode = create_node(key);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
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
        return;
    }
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != nullptr) {
        temp->next->prev = newNode;
    } else {
        tail = newNode;
    }
    temp->next = newNode;
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
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
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
    while (temp != nullptr && temp->data != key) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "Value " << key << " not found." << endl;
        return;
    }
    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }
    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    }
    if (temp == tail) {
        tail = temp->prev;
    }
    delete temp;
}
void remove_end() {
    if (tail == nullptr) {
        cout << "Underflow" << endl;
        return;
    }
    Node* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
}
void print_list_forward() {
    if (head == nullptr) {
        cout << "Head = Null, Tail = Null, Empty" << endl;
        return;
    }
    cout << "List from head to tail: ";
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}
void print_list_backward() {
    if (tail == nullptr) {
        cout << "Head = Null, Tail = Null, Empty" << endl;
        return;
    }
    cout << "List from tail to head: ";
    Node* temp = tail;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->prev;
    }
    cout << endl;
}
void print_list() {
    print_list_forward();
    print_list_backward();
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
