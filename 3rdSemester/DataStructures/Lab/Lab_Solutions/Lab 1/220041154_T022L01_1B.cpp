#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <vector>


using namespace std;

void fast() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
}

int main() {
  fast();
  int n;
  cin >> n;
  cin.ignore(); // To ignore the newline character after n

  stack<string> tagStack;
  vector<string> lines(n);

  // Reading all lines of HTML code
  for (int i = 0; i < n; ++i) {
    getline(cin, lines[i]);
  }

  // Checking each line
  for (int i = 0; i < n; ++i) {
    int len = lines[i].size();
    for (int j = 0; j < len; ++j) {
      if (lines[i][j] == '<') {
        string tag;
        int k = j + 1;

        // Extract the tag name
        while (k < len && lines[i][k] != '>') {
          tag += lines[i][k];
          ++k;
        }

        // Move the index to the end of the tag
        j = k;

        // Skip self-closing tags or empty tags
        if (tag.empty() || (tag[0] == '/' && tag.size() == 1)) {
          continue;
        }

        if (tag[0] != '/') {
          // Push opening tags onto the stack
          tagStack.push(tag);
        } else {
          // Remove '/' to match the closing tag with the opening tag
          tag = tag.substr(1);

          // Check if the stack is empty or the tags do not match
          if (tagStack.empty() || tagStack.top() != tag) {
            cout << "Error at line " << i + 1 << endl;
            return 0;
          } else {
            tagStack.pop();
          }
        }
      }
    }
  }

  // Check if any unmatched opening tags are left in the stack
  if (!tagStack.empty()) {
    cout << "Error at line " << n << endl;
  } else {
    cout << "No error" << endl;
  }

  return 0;
}
