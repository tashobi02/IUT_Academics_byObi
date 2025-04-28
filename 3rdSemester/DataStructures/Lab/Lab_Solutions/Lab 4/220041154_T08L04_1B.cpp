#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> originalList;
    int num;
    while (true) {
        cin >> num;
        if (num == 0)
            break;
        originalList.push_back(num);
    }
    list<int> oddList, evenList;
    auto it = originalList.begin();
    bool isOdd = true;
    while (it != originalList.end()) {
        if (isOdd) {
            oddList.push_back(*it);
        } else {
            evenList.push_back(*it);
        }
        isOdd = !isOdd;
        ++it;
    }
    oddList.insert(oddList.end(), evenList.begin(), evenList.end());
    for (auto it = oddList.begin(); it != oddList.end(); ++it) {
        cout << *it << " ";
    }
    cout << "NULL" << endl;
    return 0;
}
