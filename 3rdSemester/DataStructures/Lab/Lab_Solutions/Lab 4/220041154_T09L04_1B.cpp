#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* front = nullptr;
Node* rear = nullptr;
int queueSize = 0;
const int maxQueueSize = 5;

void printQueue() {
    Node* current = front;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void EnQueue(int key) {
    if (queueSize == maxQueueSize) {
        cout << "EnQueue: Overflow" << endl;
        return;
    }
    Node* newNode = new Node();
    newNode->data = key;
    newNode->next = nullptr;
    if (rear != nullptr) {
        rear->next = newNode;
    } else {
        front = newNode;
    }
    rear = newNode;
    queueSize++;
    cout << "EnQueue: ";
    printQueue();
}

int DeQueue() {
    if (front == nullptr) {
        cout << "DeQueue: Underflow" << endl;
        return -1;
    }
    int value = front->data;
    Node* temp = front;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    delete temp;
    queueSize--;
    return value;
}

bool isEmpty() { return queueSize == 0; }

bool isFull() { return queueSize == maxQueueSize; }

int size() { return queueSize; }

int Front() {
    if (front == nullptr) {
        cout << "Front: Queue is empty" << endl;
        return -1;
    }
    return front->data;
}

int main() {
    int N, choice, key;
    cin >> N;
    while (true) {
        cin >> choice;
        if (choice == -1)
            break;
        if (choice == 1) {
            cin >> key;
            EnQueue(key);
        } else if (choice == 2) {
            int value = DeQueue();
            if (value != -1)
                cout << "DeQueue: ";
            printQueue();
        } else if (choice == 3) {
            cout << "isEmpty: " << (isEmpty() ? "True" : "False") << endl;
        } else if (choice == 4) {
            cout << "isFull: " << (isFull() ? "True" : "False") << endl;
        } else if (choice == 5) {
            cout << "Size: " << size() << endl;
        } else if (choice == 6) {
            cout << "Front: " << Front() << endl;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
