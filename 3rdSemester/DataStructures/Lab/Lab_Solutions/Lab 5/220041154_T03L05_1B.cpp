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
Node* insert(Node* node, lli key) {
    if (node == NULL) {
        return new Node(key);
    }
    if (node->key == key) {
        return node;
    }
    if (node->key < key) {
        node->right = insert(node->right, key);
    } else {
        node->left = insert(node->left, key);
    }
    return node;
}
Node* lca(Node* root, lli a, lli b) {
    if (root == NULL) {
        return NULL;
    }
    if (root->key == a || root->key == b) {
        return root;
    }
    Node* left = lca(root->left, a, b);
    Node* right = lca(root->right, a, b);
    if (left == NULL)
        return right;
    else if (right == NULL)
        return left;
    else
        return root;
}
int main() {
    fast();
    lli n, x, q, a, b;
    cin >> n;
    Node* root = NULL;
    loop(i, n) {
        cin >> x;
        root = insert(root, x);
    }
    cin >> q;
    Node* ancestor;
    while (q--) {
        cin >> a >> b;
        ancestor = lca(root, a, b);
        cout << ancestor->key << endl;
    }
}