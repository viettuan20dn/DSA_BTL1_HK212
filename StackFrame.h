#pragma once
#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>

/*
* Khai bao 1 phan tu stack hay 1 toán hang
*/
class Element
{
private:
    float value;
    int typeCode;

public:
    Element() {}
    Element(float value, int typeCode);
    
    void setTCode(const int&);
    void setValue(const float&);
    float getValue();   
    int getTCode();

    void show();
    bool operator==(const Element &e);
    bool operator!=(const Element &e);
    bool operator<(const Element &e);
    bool operator>(const Element &e);
    friend Element operator*(const Element&e1,const Element&e2);
    friend Element operator+(const Element&e1,const Element&e2);
    friend Element operator-(const Element&e1,const Element&e2);
    friend Element operator/(const Element&e1,const Element&e2);
    friend Element operator%(const Element&e1,const Element&e2);
    friend Element operator&(const Element&e1,const Element&e2);
    friend Element operator|(const Element&e1,const Element&e2);
};

/*
* khai bao node cho linkedlist
*/
class Node
{
public:
    Element data;
    Node *next;

public:
    Node();
    Node(Element data, Node *next);
};

/*
* Hien thuc danh sach lien kết don
*/
class SlinkedList
{
private:
    Node *head;
    Node *tail;
    int count;

public:
    SlinkedList();
    void add(Element item);
    void add(int index, const Element& item);
    Element removeAt(const int& index);
    int indexOf(const Element& item);
    Element get(const int& index);
    bool empty();
    int size();
    void clear();
    ~SlinkedList();
};

/*
* Hien thuc Stack tren nen tang Slinkedlist
*/
class Stack
{
private:
    SlinkedList list;

public:

    void push(const Element& e);
    Element top();
    void pop();
    int size();
    bool empty();
};

/*
*StackFrame declaration
*/
class StackFrame
{
    int opStackMaxSize;  // max size of operand stack
    int localVarArrSize; // size of local variable array
    Stack st;   // operand stack
    float *LVArr;        // local variable array
    int line;   // cho biet dong lenh dang chay

public:
    /*
    Constructor of StackFrame
    */
    StackFrame();

    /*
    Run the method written in the testcase
    @param filename name of the file
    */
    void run(std::string filename);
    ~StackFrame();
};

#endif // !__STACK_FRAME_H__