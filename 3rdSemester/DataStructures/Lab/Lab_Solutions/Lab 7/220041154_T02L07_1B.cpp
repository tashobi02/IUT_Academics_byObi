#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>
using namespace std;
typedef long long int lli;
typedef long double ld;
typedef vector<long long int> vi;
#define pb push_back
#define loop(i, n) for (lli i = 0; i < (n); i++)
#define endl "\n"
#define py cout << "YES" << endl
#define pn cout << "NO" << endl
#define all(v) v.begin(), v.end()
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}

struct Node {
    lli key;
    Node *left;
    Node *right;
    Node *parent;
    lli height;
    Node(lli k) {
        key = k;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        height = 1;
    }
};

lli height(Node *N) { return (N == nullptr) ? 0 : N->height; }

void updateHeight(Node *N) {
    while (N != nullptr) {
        N->height = 1 + max(height(N->left), height(N->right));
        N = N->parent;
    }
}

lli getBalance(Node *N) {
    return (N == nullptr) ? 0 : height(N->left) - height(N->right);
}

Node *rightRotate(Node *y) {
    cout << "Right_rotate(" << y->key << ")" << endl;
    Node *x = y->left;
    Node *zz = x->right;
    x->right = y;
    y->left = zz;
    if (zz != nullptr)
        zz->parent = y;
    x->parent = y->parent;
    y->parent = x;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

Node *leftRotate(Node *x) {
    cout << "Left_rotate(" << x->key << ")" << endl;
    Node *y = x->right;
    Node *zz = y->left;
    y->left = x;
    x->right = zz;
    if (zz != nullptr)
        zz->parent = x;
    y->parent = x->parent;
    x->parent = y;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

Node *balance(Node *node) {
    updateHeight(node);
    lli balanceFactor = getBalance(node);
    if (balanceFactor > 1 && getBalance(node->left) >= 0) {
        cout << "Imbalance at node: " << node->key << "\nLL case\n";
        return rightRotate(node);
    }
    if (balanceFactor > 1 && getBalance(node->left) < 0) {
        cout << "Imbalance at node: " << node->key << "\nLR case\n";
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balanceFactor < -1 && getBalance(node->right) <= 0) {
        cout << "Imbalance at node: " << node->key << "\nRR case\n";
        return leftRotate(node);
    }
    if (balanceFactor < -1 && getBalance(node->right) > 0) {
        cout << "Imbalance at node: " << node->key << "\nRL case\n";
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node *insert(Node *root, lli key) {
    Node *parent = nullptr;
    Node *current = root;
    while (current) {
        parent = current;
        if (key == current->key)
            return root;
        current = (key < current->key) ? current->left : current->right;
    }
    Node *newNode = new Node(key);
    newNode->parent = parent;
    if (parent == nullptr)
        root = newNode;
    else if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;
    for (Node *ancestor = newNode; ancestor != nullptr;
         ancestor = ancestor->parent) {
        ancestor = balance(ancestor);
        if (ancestor->parent == nullptr)
            root = ancestor;
    }
    return root;
}

void printAVL(Node *root) {
    if (root != nullptr) {
        printAVL(root->left);
        cout << root->key << "(" << getBalance(root) << ") ";
        printAVL(root->right);
    }
}

int main() {
    fast();
    Node *root = nullptr;
    lli x;

    while (true) {
        cin >> x;
        if (x == -1) {
            cout << "Status: ";
            printAVL(root);
            break;
        }
        root = insert(root, x);
        printAVL(root);
        cout << endl;
        cout.flush();
        if (getBalance(root) >= -1 && getBalance(root) <= 1)
            cout << "Balanced\n";
        else {
            cout << "Status: ";
            printAVL(root);
        }
        if (root != nullptr)
            cout << "Root=" << root->key << endl;
        cout.flush();
    }
    return 0;
}
