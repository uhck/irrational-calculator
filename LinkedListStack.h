#ifndef LINKEDLISTSTACK_H
#define LINKEDLISTSTACK_H

#include "linkedlist.h"
#include "basenode.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
enum STACK_ERRORS {STACK_EMPTY,STACK_FULL};

using std::istream;
using std::ostream;
using std::cout;
using std::endl;
using std::string;

template<typename T>
class LinkedListStack : public linkedList
{
public:
    LinkedListStack(size_t size = 50);
    ~LinkedListStack();
    LinkedListStack(const LinkedListStack<T>&other);
    LinkedListStack<T>& operator=(const LinkedListStack<T> &other);

    LinkedListStack<T>& operator<<(const T& d); //Push chainable
    LinkedListStack<T>& operator>>(T &d);       //Pop chainable

    T pop();                      //pops out the first element
    T top();                      //looks at the top element
    void push(const T& d);        //push elements into the array
    bool full();                  //checks if the stack is full
    bool empty();                 //check if the stack is empty
    void clear();                 //clears the stack
    size_t size();                //returns the current size of the stack
    size_t max_size();            //returns the max size of the stack

    template<typename Y>
    friend
    ostream& operator<<(ostream &out, const LinkedListStack<Y> &stack);

    template<typename Y>
    friend
    istream& operator>>(istream &in, LinkedListStack<Y> &stack);


private:
    void copy(const LinkedListStack<T>& other);
    void nukem();
};

template<typename T>
LinkedListStack<T>::LinkedListStack(size_t size)
{
    maxQty = size;
    anchor = new baseNode;
}

template<typename T>
LinkedListStack<T>::~LinkedListStack()
{
    nukem();
}

template<typename T>
LinkedListStack<T>::LinkedListStack(const LinkedListStack<T> &other)
{
    anchor = new baseNode;
    copy(other);
}

template<typename T>
LinkedListStack<T>& LinkedListStack<T>::operator= (const LinkedListStack<T> &other)
{
    if (this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}
template<typename T>
LinkedListStack<T>& LinkedListStack<T>::operator<<(const T& d) //Push chainable
{
    push(d);
    return *this;
}

template<typename T>
LinkedListStack<T>& LinkedListStack<T>::operator>>(T &d)       //Pop chainable
{
    d = pop();
    return *this;
}

template<typename T>
T LinkedListStack<T>::pop()                      //pops out the first element
{
    if (empty())
        throw STACK_EMPTY;
    baseNode *ptr = anchor->nextNode();
    T data = *(T*)(ptr->getData());
    linkedList::erase(ptr);
    return data;
}

template<typename T>
T LinkedListStack<T>::top()                     //looks at the top element
{
    if (empty())
        throw STACK_EMPTY;
    baseNode *ptr = anchor->nextNode();
    T data = *(T*)(ptr->getData());
    return data;
}

template<typename T>
void LinkedListStack<T>::push(const T& d)        //push elements into the array
{
    if (!(qty-maxQty))
        throw STACK_FULL;
    baseNode* ptr = new baseNode();
    ptr->setData(new T(d));
    linkedList::insertHead(ptr);
}

template<typename T>
bool  LinkedListStack<T>::full()                  //checks if the stack is full
{
    return !(qty-maxQty);
}

template<typename T>
bool  LinkedListStack<T>::empty()                 //check if the stack is empty
{
    return !qty;
}

template<typename T>
void  LinkedListStack<T>::clear()                //clears the stack
{
    nukem();
}

template<typename T>
size_t  LinkedListStack<T>::size()                   //returns the current size of the stack
{
    return qty;
}
template<typename T>
size_t LinkedListStack<T>::max_size()
{
    return maxQty;
}

template<typename T>
void  LinkedListStack<T>::nukem()                //clears the stack
{
    baseNode *ptr = anchor->nextNode(), *bye = NULL;
    while(ptr)
    {
        bye = ptr;
        ptr = ptr->nextNode();
        delete bye;
    }
    anchor->nextNode() = NULL;
    qty = 0;
}

template<typename T>
void LinkedListStack<T>::copy(const LinkedListStack<T>& other)
{
    for(baseNode *ptr = other.anchor->nextNode(); ptr; ptr = ptr->nextNode())
    {
        push(*(T*)(ptr->getData()));
    }
    qty = other.qty;
    maxQty = other.maxQty;
}

//friends
template<typename Y>
ostream& operator<<(ostream &out, const LinkedListStack<Y> &stack)
{
    baseNode *ptr = stack.anchor->nextNode();
    int count = 1;
    while(ptr)
    {
        out<<"["<<count<<"]"<<"="<<*(Y*)(ptr->getData())<<std::endl;
        ptr = ptr->nextNode();
        ++count;
    }
    return out;
}

template<typename Y>
istream& operator>>(istream &in, LinkedListStack<string> &stack)
{
    using namespace std;
    string data;
    getline(in,data);
    stack.push(data);
    return in;
}

template<typename Y>
istream& operator>>(istream &in, LinkedListStack<Y> &stack)
{
    Y data;
    in>>data;
    stack.push(data);
    return in;
}

#endif // LINKEDLISTSTACK_H
