#include <iostream>
#include <string>
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
    bool containsKey(char ch) { return (links[ch - 'A']) != NULL; }
    void put(char ch, Node* node) { links[ch - 'A'] = node; }
    Node* get(char ch) { return links[ch - 'A']; }
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
            if (isupper(ch)) {
                if (!node->containsKey(ch)) {
                    node->put(ch, new Node());
                }
                node = node->get(ch);
            }
        }
        node->endMark();
    }
    bool matchesAbbreviation(const string& word, const string& abbr) {
        string extracted = "";
        for (char ch : word) {
            if (isupper(ch))
                extracted += ch;
        }
        return extracted == abbr;
    }
};
void soln() {
    Trie trie;
    vector<string> words;
    string word;
    while (cin >> word && word != "-1") {
        words.push_back(word);
        trie.insert(word);
    }
    string abbr;
    cin >> abbr;
    for (const string& word : words) {
        cout << (trie.matchesAbbreviation(word, abbr) ? "T" : "F") << " ";
    }
    cout << enl;
}
int main() {
    fast();
    lli t = 1;
    while (t--) soln();
    return 0;
}
