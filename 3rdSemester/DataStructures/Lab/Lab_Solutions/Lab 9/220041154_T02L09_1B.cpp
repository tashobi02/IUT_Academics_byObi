#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
typedef long long int lli;
#define enl "\n"
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}

struct Node {
    Node* links[26];
    bool flag = false;
    int countPrefix = 0;
    Node() { fill(begin(links), end(links), nullptr); }

    bool containsKey(char ch) { return (links[ch - 'a']) != NULL; }
    void put(char ch, Node* node) { links[ch - 'a'] = node; }
    Node* get(char ch) { return links[ch - 'a']; }
    void endMark() { flag = true; }
    bool isEnd() { return flag; }
    void increasePrefix() { countPrefix++; }
};

class Trie {
   private:
    Node* root;

   public:
    Trie() { root = new Node(); }

    void insert(string word) {
        if (search(word))
            return;
        Node* node = root;
        for (char ch : word) {
            if (!node->containsKey(ch)) {
                node->put(ch, new Node());
            }
            node = node->get(ch);
            node->increasePrefix();
        }
        node->endMark();
    }

    bool search(string word) {
        Node* node = root;
        for (char ch : word) {
            if (!node->containsKey(ch)) {
                return false;
            }
            node = node->get(ch);
        }
        return node->isEnd();
    }

    void display(Node* curr, string prefix) {
        if (curr->isEnd()) {
            cout << prefix << " ";
        }
        for (int i = 0; i < 26; i++) {
            if (curr->links[i] != NULL) {
                char nextChar = i + 'a';
                display(curr->links[i], prefix + nextChar);
            }
        }
    }

    int countWordsStartingWith(string prefix) {
        Node* node = root;
        for (char ch : prefix) {
            if (!node->containsKey(ch)) {
                return 0;
            }
            node = node->get(ch);
        }
        return node->countPrefix;
    }
    void displayAll() { display(root, ""); }
};

void soln() {
    int n, q;
    Trie trie;
    cin >> n >> q;
    string word, prefix;

    while (n--) {
        cin >> word;
        for (char& ch : word) ch = tolower(ch);
        trie.insert(word);
    }
    // trie.displayAll();
    cout << enl;

    while (q--) {
        cin >> prefix;
        for (char& ch : prefix) ch = tolower(ch);
        cout << trie.countWordsStartingWith(prefix) << enl;
    }
    cout.flush();
}

int main() {
    fast();
    lli t = 1;
    while (t--) soln();
    return 0;
}
// Author: tashobi_02 //
