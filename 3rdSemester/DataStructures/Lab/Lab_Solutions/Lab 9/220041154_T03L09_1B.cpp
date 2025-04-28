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

    Node() { fill(begin(links), end(links), nullptr); }

    bool containsKey(char ch) { return links[ch - 'a'] != NULL; }
    void put(char ch, Node* node) { links[ch - 'a'] = node; }
    Node* get(char ch) { return links[ch - 'a']; }
    void endMark() { flag = true; }
    bool isEnd() { return flag; }
};

class Trie {
   private:
    Node* root;

   public:
    Trie() { root = new Node(); }

    void insert(const string& word) {
        Node* node = root;
        for (char ch : word) {
            if (!node->containsKey(ch)) {
                node->put(ch, new Node());
            }
            node = node->get(ch);
        }
        node->endMark();
    }

    vector<string> getSuggestions(Node* curr, const string& prefix,
                                  int limit = 3) {
        vector<string> results;
        search(curr, prefix, results, limit);
        return results;
    }

    void search(Node* node, const string& word, vector<string>& results,
                int limit) {
        if (!node || (int)results.size() >= limit)
            return;
        if (node->isEnd()) {
            results.push_back(word);
        }
        for (int i = 0; i < 26 && (int)results.size() < limit; i++) {
            if (node->links[i]) {
                search(node->links[i], word + char(i + 'a'), results, limit);
            }
        }
    }

    vector<string> searchSuggestions(const string& prefix) {
        Node* node = root;
        for (char ch : prefix) {
            if (!node->containsKey(ch))
                return {};
            node = node->get(ch);
        }
        return getSuggestions(node, prefix);
    }
};

void soln() {
    Trie trie;
    string line;

    getline(cin, line);
    stringstream ss(line);
    string word;
    vector<string> products;

    while (ss >> word) {
        products.push_back(word);
    }
    sort(products.begin(), products.end());
    for (const string& product : products) {
        trie.insert(product);
    }

    string searchWord;
    cin >> searchWord;

    string prefix = "";
    for (char ch : searchWord) {
        prefix += ch;
        vector<string> suggestions = trie.searchSuggestions(prefix);

        if (suggestions.empty()) {
            cout << "Null" << enl;
        } else {
            for (const string& suggestion : suggestions) {
                cout << suggestion << " ";
            }
            cout << enl;
        }
    }
}

int main() {
    fast();
    lli t = 1;
    while (t--) soln();
    return 0;
}
// Author: tashobi_02 //
