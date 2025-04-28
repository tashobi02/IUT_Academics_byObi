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
    lli height;
    lli left_subtree;
    Node(lli k) {
        key = k;
        left = nullptr;
        right = nullptr;
        height = 1;
        left_subtree = 1;
    }
};

lli height(Node *N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

lli subtreeSize(Node *N) {
    if (N == nullptr)
        return 0;
    return N->left_subtree;
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *temp = x->right;
    x->right = y;
    y->left = temp;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    y->left_subtree = 1 + subtreeSize(y->left) + subtreeSize(y->right);
    x->left_subtree = 1 + subtreeSize(x->left) + subtreeSize(x->right);
    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *temp = y->left;
    y->left = x;
    x->right = temp;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    x->left_subtree = 1 + subtreeSize(x->left) + subtreeSize(x->right);
    y->left_subtree = 1 + subtreeSize(y->left) + subtreeSize(y->right);
    return y;
}

lli getBalance(Node *N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

Node *insert(Node *node, lli key) {
    if (node == nullptr)
        return new Node(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;
    node->height = 1 + max(height(node->left), height(node->right));
    node->left_subtree = 1 + subtreeSize(node->left) + subtreeSize(node->right);

    lli balance = getBalance(node);
    if (balance > 1 && key < node->left->key)  // LL case
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)  // RR case
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {  // LR case
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {  // RL case
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

lli lowerCount(Node *root, lli query) {
    if (root == nullptr)
        return 0;
    if (query <= root->key)
        return lowerCount(root->left, query);
    else {
        lli leftCount = subtreeSize(root->left);
        return leftCount + 1 + lowerCount(root->right, query);
    }
}

void preOrder(Node *root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    fast();
    Node *root = nullptr;
    lli x;
    while (true) {
        cin >> x;
        if (x == -1) {
            break;
        }
        root = insert(root, x);
    }
    lli q, k;
    cin >> q;
    while (q--) {
        cin >> x;
        k = lowerCount(root, x);
        cout << k << endl;
        cout.flush();
    }
}
