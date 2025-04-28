#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* front = nullptr;
Node* rear = nullptr;
int dequeSize = 0;

void push_front(int key) {
    Node* newNode = new Node();
    newNode->data = key;
    newNode->prev = nullptr;
    newNode->next = front;

    if (front != nullptr) {
        front->prev = newNode;
    } else {
        rear = newNode;
    }
    front = newNode;
    dequeSize++;
}

void push_back(int key) {
    Node* newNode = new Node();
    newNode->data = key;
    newNode->next = nullptr;
    newNode->prev = rear;

    if (rear != nullptr) {
        rear->next = newNode;
    } else {
        front = newNode;
    }
    rear = newNode;
    dequeSize++;
}

int pop_front() {
    if (front == nullptr) {
        cout << "Error: Deque is empty." << endl;
        return -1;
    }
    int value = front->data;
    Node* temp = front;
    front = front->next;

    if (front != nullptr) {
        front->prev = nullptr;
    } else {
        rear = nullptr;
    }
    delete temp;
    dequeSize--;
    return value;
}

int pop_back() {
    if (rear == nullptr) {
        cout << "Error: Deque is empty." << endl;
        return -1;
    }
    int value = rear->data;
    Node* temp = rear;
    rear = rear->prev;

    if (rear != nullptr) {
        rear->next = nullptr;
    } else {
        front = nullptr;
    }
    delete temp;
    dequeSize--;
    return value;
}

int size() { return dequeSize; }

void printDeque() {
    Node* current = front;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    int choice, key;
    while (true) {
        cin >> choice;
        if (choice == 1) {
            cin >> key;
            push_front(key);
            printDeque();
        } else if (choice == 2) {
            cin >> key;
            push_back(key);
            printDeque();
        } else if (choice == 3) {
            key = pop_front();
            if (key != -1)
                cout << key << endl;
            printDeque();
        } else if (choice == 4) {
            key = pop_back();
            if (key != -1)
                cout << key << endl;
            printDeque();
        } else if (choice == 5) {
            cout << size() << endl;
        } else if (choice == 6) {
            return 0;
        } else {
            cout << "Invalid choice" << endl;
        }
    }
}
