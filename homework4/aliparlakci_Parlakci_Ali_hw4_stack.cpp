#include "aliparlakci_Parlakci_Ali_hw4_stack.h"

Stack::Stack() : head(nullptr)
{
}

Stack::Stack(const Stack &copy)
{
    node* tempHead = new node();
    node* tempHeadPtr = tempHead;

    for (node* ptr = copy.head; ptr != nullptr; ptr = ptr->next)
    {
        tempHeadPtr->next = new node(ptr->x, ptr->y, ptr->next);
        tempHeadPtr = tempHeadPtr->next;
    }
    head = tempHead->next;
}

Stack::~Stack()
{
    while(!isEmpty())
    {
        int x,y;
        pop(x,y);
    }
}

void Stack::push(int x, int y)
{
    // Empty stack condition handled implicitly
    head = new node(x, y, head);
}

void Stack::pop(int &x, int &y)
{
    x = head->x;
    y = head->y;
    node* temp = head;
    head = head->next;
    delete temp;
}

bool Stack::isEmpty() const
{
    return head == nullptr;
}