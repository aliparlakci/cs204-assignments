#ifndef _STACK_H
#define _STACK_H

struct node
{
    int value;
    node* next;
    node() : value(0), next(nullptr){};
    node(int val, node* n=nullptr) : value(val), next(n){};
};

class Stack
{
public:
    Stack();
    void push(int value);
    int pop();
    bool isEmpty() const;
private:
    node* head;
};

#endif