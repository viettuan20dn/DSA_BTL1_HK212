#pragma once
#include <iostream>
using namespace std;

class Element
{
    private:
        float value;
        int typeCode;
    public:
        Element(){}
        Element(float value, int typeCode)
        {
            this->value=value;
            this->typeCode=typeCode;
        }
        // ham de test gia tri
        int getTypeCode()
        {
            return this->typeCode;
        }
        float getValue()
        {
            return this->value;
        }
        void show()
        {
            cout<<"Value: "<<value<<endl;
        }
        bool operator==(const Element &element)
        {
            return (this->value=element.value&&this->typeCode==element.typeCode);
        }
};

template <class T>
class SlinkedList
{
public:
    class Node;

private:
    Node *head;
    Node *tail;
    unsigned int count;

public:
    SlinkedList()
    {
        this->head = this->tail = NULL;
        count = 0;
    }
    /*
        * them vao cuoi danh sach
    */
    void add(T item)
    {
        Node *newNode = new Node(item);
        if (count == 0)
        {
            this->head = this->tail = newNode;
            count = 1;
        }
        else
        {
            this->tail->next = newNode;
            this->tail = newNode;
            count++;
        }
    }
    void add(int index, T item)
    {
        if (index<0||index>this->count) throw out_of_range("Index is not valid");
        if (this->count==index) 
        {
            return this->add(item);
        }
        if (index==0)
        {
            Node* newNode= new Node(item,this->head);
            this->head=newNode;
            this->count++;
            return;
        }
        else
        {
            Node* newNode= new Node(item);
            Node* tmp=this->head;

            for (int i=0;i<index-1;i++)
            {
                tmp=tmp->next;
            }

            newNode->next=tmp->next;
            tmp->next=newNode;
            this->count++;
            return;
        }
    }
    T removeAt(int index)
    {
        if (index<0||index>=this->count) throw out_of_range("Index is not valid");
        if (this->count==1)
        {
            T valueToReturn=this->head->data;
            delete this->head;
            this->head=this->tail=NULL;
            this->count=0;
            return valueToReturn;
        }
        if (index==0)
        {
            T valueToReturn=this->head->data;
            Node* tmp=this->head;
            this->head=this->head->next;
            delete tmp;
            this->count--;
            return valueToReturn;
        }
        
        Node* tmp=this->head;
        for (int i=0;i<index-1;i++)
        {
            tmp=tmp->next;
        }

        if (index==(this->count-1))
        {
            T valueToReturn=this->tail->data;
            delete this->tail;
            tmp->next=NULL;
            this->tail=tmp;
            this->count--;
            return valueToReturn;
        }else
        {
            T valueToReturn=tmp->next->data;
            Node* delNode=tmp->next;
            tmp->next=delNode->next;
            delete delNode;
            this->count--;
            return valueToReturn;
        }

    }
    bool removeItem(T item)
    {
        int index=this->indexOf(item);
        if (index!=-1) 
        {
            this->removeAt(index);
            return true;
        }
        return false;
        
    }
    int indexOf(T item)
    {
        Node* tmp=this->head;
        for (int i=0;i<this->count;i++)
        {
            if (tmp->data==item) return i;
            tmp=tmp->next;
        }
        return -1;
    }
    T get(int index)
    {
        if (index<0||index>=this->count) throw out_of_range("Index is not valid");

        Node* tmp=this->head;
        for (int i=0;i<index;i++)
        {
            tmp=tmp->next;
        }
        return tmp->data;
    }
    int empty()
    {
        return this->count==0;
    }
    int size()
    {
        return this->count;
    }
    void printList()
    {
        cout<<"Danh sach gom co: \n";
        Node *tmp = this->head;
        while (tmp)
        {
            tmp->data.show();
            tmp = tmp->next;
        }
        cout<<endl;
    }
    void clear()
    {
        while (this->head)
        {
            Node *tmp = this->head;
            this->head = this->head->next;
            delete tmp;
        }
        this->tail = NULL;
        this->count = 0;
    }
    ~SlinkedList()
    {
        this->clear();
        //cout<<"Danh sach da bi huy \n";
    }

public:
    class Node
    {
    public:
        T data;
        Node *next;

    public:
        Node()
        {
            next = NULL;
        }
        Node(T data, Node *next = NULL)
        {
            this->data = data;
            this->next = next;
        }
    };
};

// int main()
// {
//     SlinkedList<Element> list;
//     Element e(3,0);
//     list.add(e);
//     Element e1(4,0);
//     list.add(e1);
//     list.printList();
//     list.removeItem(e);
//     list.printList();
// }