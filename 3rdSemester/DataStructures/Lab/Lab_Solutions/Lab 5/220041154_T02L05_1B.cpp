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
    Node(lli item) {
        key = item;
        left = NULL;
        right = NULL;
    }
};

Node* insert(Node* root, lli key) {
    Node* newNode = new Node(key);
    if (root == NULL) {
        return newNode;
    }
    Node* parent = NULL;
    Node* current = root;
    while (current != NULL) {
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
    if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    return root;
}

Node* search(Node* root, lli key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (root->key < key) {
        return search(root->right, key);
    }
    return search(root->left, key);
}

void inorder(Node* root, Node* parent) {
    if (root != NULL) {
        inorder(root->left, root);
        cout << root->key << "(";
        if (parent != NULL)
            cout << parent->key;
        else
            cout << "None";
        cout << ") ";
        inorder(root->right, root);
    }
}

void preorder(Node* root, Node* parent) {
    if (root != NULL) {
        cout << root->key << "(";
        if (parent != NULL)
            cout << parent->key;
        else
            cout << "null";
        cout << ") ";
        preorder(root->left, root);
        preorder(root->right, root);
    }
}

void postorder(Node* root, Node* parent) {
    if (root != NULL) {
        postorder(root->left, root);
        postorder(root->right, root);
        cout << root->key << "(";
        if (parent != NULL)
            cout << parent->key;
        else
            cout << "null";
        cout << ") ";
    }
}

void levelorder(Node* root) {
    if (root == NULL)
        return;
    lli ct = 0;
    queue<pair<Node*, Node*>> Q;
    Q.push({root, NULL});
    while (!Q.empty()) {
        ct++;
        lli levelSize = Q.size();
        cout << "Level " << ct << ": ";
        for (lli i = 0; i < levelSize; i++) {
            Node* current = Q.front().first;
            Node* parent = Q.front().second;
            Q.pop();
            cout << current->key << "(";
            if (parent != NULL)
                cout << parent->key;
            else
                cout << "null";
            cout << ") ";
            if (current->left != NULL)
                Q.push({current->left, current});
            if (current->right != NULL)
                Q.push({current->right, current});
        }
        cout << endl;
    }
}

int main() {
    fast();
    lli n, x;
    Node* root;
    cin >> n;
    loop(i, n) {
        cin >> x;
        if (i == 0) {
            root = new Node(x);
        } else {
            insert(root, x);
        }
    }
    cout << "Inorder: " << endl;
    inorder(root, root);
    cout << endl << "Preorder: " << endl;
    preorder(root, root);
    cout << endl << "Postorder: " << endl;
    postorder(root, root);
    cout << endl << "Levelorder: " << endl;
    levelorder(root);
    cout << endl;
    return 0;
}
