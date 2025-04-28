#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;
int main() {
    list<int> numbers;
    int num;
    while (true) {
        cin >> num;
        if (num == -1)
            break;
        numbers.push_back(num);
    }
    numbers.unique();
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}
