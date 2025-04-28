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
    Node* left;
    Node* right;
    Node* parent;
    lli height;
    Node(lli k) {
        key = k;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        height = 1;
    }
};

lli height(Node* N) { return (N == nullptr) ? 0 : N->height; }

lli getBalance(Node* N) {
    return (N == nullptr) ? 0 : height(N->left) - height(N->right);
}

void updateHeight(Node* N) {
    while (N != nullptr) {
        N->height = 1 + max(height(N->left), height(N->right));
        N = N->parent;
    }
}

Node* insert(Node* root, lli key) {
    if (root == nullptr) {
        return new Node(key);
    }
    Node* parent = nullptr;
    Node* current = root;
    while (current) {
        parent = current;
        if (key == current->key) {
            return root;
        }
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    Node* newNode = new Node(key);
    newNode->parent = parent;
    if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    updateHeight(newNode);
    return root;
}

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->key << "(" << getBalance(root) << ") ";
        inorder(root->right);
    }
}

int main() {
    fast();
    lli x;
    Node* root = nullptr;
    while (true) {
        cin >> x;
        if (x == -1)
            break;
        root = insert(root, x);
        inorder(root);
        cout << endl;
        cout.flush();
    }
    return 0;
}
