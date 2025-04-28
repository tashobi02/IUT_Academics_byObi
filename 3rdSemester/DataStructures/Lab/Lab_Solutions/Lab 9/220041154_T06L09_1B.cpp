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
    Node* links[10];
    bool flag = false;
    bool containsKey(char ch) { return (links[ch - '0']) != NULL; }
    void put(char ch, Node* node) { links[ch - '0'] = node; }
    Node* get(char ch) { return links[ch - '0']; }
    void endMark() { flag = true; }
    bool isEnd() { return flag; }
};
class Trie {
   private:
    Node* root;

   public:
    Trie() { root = new Node(); }
    void insert(string word) {
        Node* node = root;
        for (lli i = 0; i < (lli)word.length(); i++) {
            if (!node->containsKey(word[i])) {
                node->put(word[i], new Node());
            }
            node = node->get(word[i]);
        }
        node->endMark();
    }
    lli longestCommonPrefix(string word) {
        Node* node = root;
        lli prefixLength = 0;
        for (lli i = 0; i < (lli)word.length(); i++) {
            if (!node->containsKey(word[i])) {
                break;
            }
            node = node->get(word[i]);
            prefixLength++;
        }
        return prefixLength;
    }
};
void soln() {
    lli n, m;
    cin >> n >> m;
    vector<string> arr1(n), arr2(m);
    for (lli i = 0; i < n; i++) {
        lli num;
        cin >> num;
        arr1[i] = to_string(num);
    }
    for (lli i = 0; i < m; i++) {
        lli num;
        cin >> num;
        arr2[i] = to_string(num);
    }
    Trie trie;
    for (const string& num : arr1) {
        trie.insert(num);
    }
    lli maxLCP = 0;
    for (const string& num : arr2) {
        maxLCP = max(maxLCP, trie.longestCommonPrefix(num));
    }
    cout << maxLCP << enl;
}
int main() {
    fast();
    lli t = 1;
    while (t--) soln();
    return 0;
}
