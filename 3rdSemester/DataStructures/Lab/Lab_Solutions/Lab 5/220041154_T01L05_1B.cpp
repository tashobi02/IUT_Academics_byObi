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

Node* long_search(Node* root, lli key) {
    lli parent = -1, ln = -1, rn = -1;
    string ls = "", rs = "";
    while (root != NULL && root->key != key) {
        parent = root->key;
        // cout << parent;
        if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
        if (root != NULL) {
            if (root->left == NULL)
                ls = "null";
            else {
                ln = root->left->key;
                // cout << "ln: " << ln << endl;
            }
            if (root->right == NULL)
                rs = "null";
            else {
                rn = root->right->key;
                // cout << "rn: " << rn << endl;
            }
        }
    }
    if (root != NULL && root->key == key) {
        cout << "Present" << endl;
        cout << "Parent(" << parent << "), ";
        if (ls == "null")
            cout << "Left(" << ls << "), ";
        else
            cout << "Left(" << ln << "), ";
        if (rs == "null")
            cout << "Right(" << rs << ")" << endl;
        else
            cout << "Right(" << rn << ")" << endl;
    } else {
        cout << "Not Present" << endl;
    }
    return root;
}

Node* short_search(Node* root, lli key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (root->key < key) {
        return short_search(root->right, key);
    }
    return short_search(root->left, key);
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

lli findHeight(Node* key) {
    lli lh, rh;
    if (key == NULL)
        return -1;
    else {
        lh = findHeight(key->left);
        rh = findHeight(key->right);
    }
    return max(lh, rh) + 1;
}

void findBeforeAfter(Node* root, lli key, Node*& before, Node*& after,
                     Node*& prev, bool& found) {
    if (root == NULL)
        return;
    findBeforeAfter(root->left, key, before, after, prev, found);
    if (found) {
        after = root;
        found = false;
        return;
    }
    if (root->key == key) {
        found = true;
        before = prev;
    }
    prev = root;
    findBeforeAfter(root->right, key, before, after, prev, found);
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
    inorder(root);
    cout.flush();
    lli command;
    while (1) {
        cin >> command;
        if (command == 3) {
            lli ss;
            cin >> ss;
            long_search(root, ss);
        } else if (command == 4) {
            lli key;
            cin >> key;
            Node* HeightNode = short_search(root, key);
            cout << findHeight(HeightNode) << endl;
        } else if (command == 5) {
            lli key;
            cin >> key;
            Node* before = NULL;
            Node* after = NULL;
            Node* prev = NULL;
            bool found = false;
            findBeforeAfter(root, key, before, after, prev, found);
            if (before != NULL)
                cout << before->key << endl;
            else
                cout << "null";
            if (after != NULL)
                cout << " " << after->key;
            else
                cout << " null" << endl;
        }
        cout.flush();
    }
    return 0;
}
