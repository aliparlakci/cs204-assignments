/*
 * CS204 Spring 2020 - Albert Levi
 * Homework 2
 * 13 March 2021
 * Written by Ali PARLAKCI
 * 28114, aliparlakci@sabanciuniv.edu
 */

#include "aliparlakci_Parlakci_Ali_hw2_linkedlist.h"

LinkedList::LinkedList() : head(NULL), length(0)
{
}

// postcondition: appends a new item to the end of the list
void LinkedList::push_back(int value)
{
    insert(length, value);
}

// precondition: indice is non-negative and smaller than or equal to length
// postcondition: ith element of the list is value, elements after that are shifted by one
// exception: nothing happens if indice is negative or bigger than the length
void LinkedList::insert(int indice, int value)
{
    if (indice == 0) 
    {
        head = new node(value, head);
        length++;
    }
    else if (indice >= 0 && indice <= length)
    {
        node *ptr = getNode(indice - 1);
        ptr->next = new node(value, ptr->next);
        length++;
    }
}

// postcondition: returns the ith element in the list
// exception: returns string::npos if no element exists at the indice
int LinkedList::at(int indice) const
{
    node* ptr = getNode(indice);
    return ptr != NULL ? ptr->value : std::string::npos;
}

// precondition: indice is non-negative and lower than length
// postcondition: returns pointer to node at the indice
node* LinkedList::getNode(int indice) const
{
    node* ptr = head;

    if (ptr != NULL && indice >= 0 && indice < length)
    {
        int counter = 0;
        int value;

        while (ptr != NULL & counter <= indice)
        {
            if (counter == indice)
            {
                return ptr;
            }
            
            ptr = ptr->next;
            counter++;
        }
    }

    return NULL;
}

// precondition: indice is non-negative and lower than length
// postcondition: removes the ith element from the list, length is decreased by one
void LinkedList::remove(int indice)
{
    if (indice >= 0 && indice < length)
    {
        node *ptr, *cursor;

        if (indice == 0)
        {
            ptr = head;
            head = head->next;
            delete ptr;
        }
        else
        {
            cursor = getNode(indice - 1);
            ptr = cursor->next;
            cursor->next = cursor->next != NULL ? cursor->next->next : NULL;
            delete ptr;
        }
        length--;
    }
}

// postcondition: returns true if list contains given value
bool LinkedList::contains(int value) const
{
    bool doesExist = false;

    for (node *ptr = head; ptr != NULL && !doesExist; ptr = ptr->next)
    {
        doesExist = ptr->value == value ? true : doesExist;
    }

    return doesExist;
}

// postcondition: deallocates all the elements in the list, head is NULL and length is 0
void LinkedList::destroy()
{
    truncate(head);
    head = NULL;
    length = 0;
}

// postcondition: given node and nodes after it is deallocated
void LinkedList::truncate(node* nodeptr)
{
    if (nodeptr == NULL)
    {
        return;
    }

    truncate(nodeptr->next);
    delete nodeptr;
}