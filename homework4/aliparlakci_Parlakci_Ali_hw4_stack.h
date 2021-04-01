#ifndef _STACK_H
#define _STACK_H

struct node
{
    int x, y;
    node *next;
    node() : x(0), y(0), next(nullptr){};
    node(int xx, int yy, node *n = nullptr) : x(xx), y(yy), next(n){};
};

class Stack
{
public:
    Stack();
    Stack(const Stack &copy);
    ~Stack();
    void push(int x, int y);
    void pop(int &x, int &y);
    bool isEmpty() const;

private:
    node *head;
};

#endif