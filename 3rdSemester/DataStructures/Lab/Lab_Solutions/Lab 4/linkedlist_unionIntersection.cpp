#include <iostream>

#include "unsortedtype.cpp"

using namespace std;

int main() {
    UnsortedType<int> firstList;
    UnsortedType<int> secondList;
    UnsortedType<int> intersectionList;

    firstList.Insert(10);
    firstList.Insert(1);
    firstList.Insert(5);
    firstList.Insert(6);
    firstList.Insert(10);
    firstList.Insert(16);
    firstList.Insert(20);
    firstList.Insert(25);
    firstList.Insert(31);
    firstList.Insert(38);
    firstList.Insert(40);

    secondList.Insert(12);
    secondList.Insert(2);
    secondList.Insert(4);
    secondList.Insert(7);
    secondList.Insert(9);
    secondList.Insert(16);
    secondList.Insert(19);
    secondList.Insert(23);
    secondList.Insert(24);
    secondList.Insert(32);
    secondList.Insert(35);
    secondList.Insert(38);
    secondList.Insert(42);
    UnsortedType<int> secondListCopy = secondList;
    int num;
    bool found;
    firstList.Reset();
    for (int i = 0; i < firstList.Length(); i++) {
        firstList.GetNext(num);
        secondListCopy.Search(num, found);
        if (found) {
            intersectionList.Insert(num);
        }
    }
    for (int i = 0; i < secondList.Length(); i++) {
        secondList.GetNext(num);
        firstList.Insert(num);
    }
    secondList.MakeEmpty();
    int max;
    while (firstList.Length() != 0) {
        firstList.Reset();
        firstList.GetNext(num);
        max = num;
        for (int i = 0; i < firstList.Length(); i++) {
            firstList.GetNext(num);
            if (num > max)
                max = num;
        }
        firstList.Delete(max);
        secondList.Search(max, found);
        if (!found)
            secondList.Insert(max);
    }
    cout << "Union: ";
    secondList.Reset();
    for (int i = 0; i < secondList.Length(); i++) {
        secondList.GetNext(num);
        cout << num << " ";
    }
    cout << endl;
    cout << "Intersection: ";
    intersectionList.Reset();
    for (int i = 0; i < intersectionList.Length(); i++) {
        intersectionList.GetNext(num);
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
