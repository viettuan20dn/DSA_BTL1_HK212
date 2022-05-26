#include <iostream>
#include "SlinkedList.cpp"
using namespace std;

template <class T>
class Stack
{
private:
    SlinkedList<T> list;
public:
    Stack(){}
    void push(T e)
    {
        list.add(0,e);
    }
    T top()
    {
        if (this->empty()) throw out_of_range("khong ton tai phan tu");
        return list.get(0);
    }
    int size()
    {
        return list.size();
    }
    bool empty()
    {
        return list.size()==0;
    }
    void showSt()
    {
        list.printList();
    }
};
