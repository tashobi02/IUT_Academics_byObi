#include "unsortedtype.h"
#include <iostream>
using namespace std;

template <class T>
UnsortedType<T>::UnsortedType()
{
    head = NULL;
    pointTo = NULL;
    size = 0;
}

template <class T>
int UnsortedType<T>::Length()
{
    return size;
}

template <class T>
void UnsortedType<T>::Insert(T value)
{
    Node* temp = new Node;
    temp->data = value;
    temp->next = head;
    head = temp;
    size++;
}

template <class T>
void UnsortedType<T>::Search(T value, bool &found)
{
    found = false;
    Node* i = head;
    while(i != NULL)
    {
        if (value == i->data)
        {
            found = true;
            break;
        }
        else
        {
            i = i->next;
        }
    }
}

template <class T>
void UnsortedType<T>::Delete(T value)
{
    Node* i = head;
    Node* prev = NULL;
    bool found = false;
    while(i != NULL)
    {
        if (value == i->data)
        {
            found = true;
            break;
        }
        else
        {
            prev = i;
            i = i->next;
        }
    }
    if (found)
    {
        if (prev == NULL) // first node / no previous nodes
            head = i->next;
        else
            prev->next = i->next;
        delete i;
        size--;
    }
}

template <class T>
void UnsortedType<T>::MakeEmpty()
{
    Node* i = head;
    Node* nextNode;
    while (i != NULL)
    {
        nextNode = i->next; // Store the next node
        delete i; // Delete the current node
        i = nextNode; // Move to the next node
    }
    head = NULL;
    size = 0;
}

template <class T>
UnsortedType<T>::~UnsortedType()
{
    MakeEmpty();
}

template <class T>
void UnsortedType<T>::GetNext(T &value)
{
    if (pointTo == NULL)
    {
        pointTo = head;
        value = pointTo->data;
    }
    else
    {
        value = pointTo->data;
    }
    pointTo = pointTo->next;
}

template <class T>
void UnsortedType<T>::Reset()
{
    pointTo = NULL;
}
