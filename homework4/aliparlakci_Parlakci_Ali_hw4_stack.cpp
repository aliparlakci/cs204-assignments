#include "aliparlakci_Parlakci_Ali_hw4_stack.h"

Stack::Stack() : head(nullptr)
{
}

void Stack::push(int value)
{
    // Empty stack condition handled implicitly
    head = new node(value, head);
}

int Stack::pop()
{
    int value = head->value;
    node* temp = head;
    head = head->next;
    delete temp;
    return value;
}

bool Stack::isEmpty() const
{
    return head == nullptr;
}