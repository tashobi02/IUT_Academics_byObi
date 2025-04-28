#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <queue>
#include <sstream>
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
    char key;
    Node* left;
    Node* right;
    Node(char item) {
        key = item;
        left = NULL;
        right = NULL;
    }
};

Node* buildTree(vector<string>& preorder, lli& index) {
    if (index >= ((lli)preorder.size()) || preorder[index] == "-") {
        index++;
        return NULL;
    }
    Node* root = new Node(preorder[index][0]);
    index++;
    root->left = buildTree(preorder, index);
    root->right = buildTree(preorder, index);
    return root;
}

void inorder(Node* root) {
    if (root == NULL) {
        cout << "- ";
        return;
    }
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL) {
        cout << "- ";
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->key << " ";
}

int main() {
    fast();
    vector<string> preorder;
    string line, s;
    getline(cin, line);
    stringstream ss(line);
    while (ss >> s) {
        preorder.pb(s);
    }
    lli index = 0;
    Node* root = buildTree(preorder, index);
    cout << "Inorder: ";
    inorder(root);
    cout << endl;
    cout << "Postorder: ";
    postorder(root);
    cout << endl;
    return 0;
}
