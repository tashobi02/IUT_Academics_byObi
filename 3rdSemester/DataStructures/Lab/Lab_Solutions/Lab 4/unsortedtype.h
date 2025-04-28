#ifndef UNSORTEDTYPE_H
#define UNSORTEDTYPE_H
template <class T>
class UnsortedType
{
private:
    struct Node
    {
        T data;
        Node* next;
    };
    Node* head;
    Node* pointTo;
    int size;
public:
    UnsortedType();
    ~UnsortedType();
    int Length();
    void Insert(T value);
    void Search(T value, bool &found);
    void Delete(T value);
    void MakeEmpty();
    void GetNext(T &value);
    void Reset();
};
#endif // UNSORTEDTYPE_H
