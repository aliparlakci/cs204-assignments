#include <iostream>
#include "aliparlakci_Parlakci_Ali_hw3_subseqslist.h"

SubSeqsList::SubSeqsList() : hHead(new SubSeqHeadNode), length(1)
{}

void SubSeqsList::add(int entry)
{
    if(!exists(entry))
    {   
        // Iteratate over length instead of pointers
        // to skip the newly added nodes
        SubSeqHeadNode *hPtr = hHead;
        int currLength = length;
        for (int i = 0; i < currLength; i++)
        {
            if (isAllSmaller(entry, hPtr->sHead))
            {
                // SubSeqHeadNode *newSeq = new SubSeqHeadNode();
                // newSeq->size = hPtr->size;
                // newSeq->sHead = duplicate(hPtr->sHead);
                // appendToSeq(newSeq->sHead, entry);
                // newSeq->size++;
                // addNewSeq(newSeq);
                SubSeqHeadNode *newSeq = addNewSeq();
                newSeq->size = hPtr->size;
                newSeq->sHead = duplicate(hPtr->sHead);
                appendToSeq(newSeq->sHead, entry);
                newSeq->size++;
            }
            hPtr = hPtr->next;
        }

        std::cout << "Subsequence(s) containing "
                    << entry 
                    << " has/have been added" << std::endl;
    }
    else
    {
        std::cout << entry << " is already in the list!" << std::endl;
    }
}

void SubSeqsList::remove(int entry)
{

}

void SubSeqsList::print() const
{
    int size = 1;
    for (int i = 0; i < length - 1;)
    {
        for (SubSeqHeadNode *ptr = hHead; ptr != nullptr; ptr=ptr->next)
        {
            if (ptr->size == size)
            {
                std::cout << size << " | ";
                printSeq(ptr->sHead);
                std::cout << std::endl;
                i++;
            }
        }
        size++;
    }
}

void SubSeqsList::printUnordered() const
{
    for (SubSeqHeadNode *ptr = hHead; ptr != nullptr; ptr=ptr->next)
    {
        printSeq(ptr->sHead);
        std::cout << std::endl;
    }
}

void SubSeqsList::destroy()
{
    truncateSeqList(hHead);
    hHead = new SubSeqHeadNode;
    length = 0;
}

// postcondition: appends a new sequence head to the end of the heads list
// and returns the pointer to it
void SubSeqsList::addNewSeq(SubSeqHeadNode *node)
{
    bool isAdded = false;
    SubSeqHeadNode *hPtr = hHead;

    if (hPtr->next != nullptr)
    {
        while(hPtr != nullptr && !isAdded)
        {
            if (hPtr->next == nullptr)
            {
                hPtr->next = node;
                isAdded = true;
            }
            else
            {
                if (smallerThan(node->sHead, hPtr->next->sHead))
                {
                    SubSeqHeadNode *temp = hPtr->next;
                    hPtr->next = node;
                    node->next = temp;
                    isAdded = true;
                }
            }

            hPtr = hPtr->next;
        }
    }
    else
    {
        hPtr->next = node;
    }
    length++;
}

SubSeqHeadNode* SubSeqsList::addNewSeq()
{
    bool isAdded = false;
    SubSeqHeadNode *hPtr = hHead;

    while(hPtr->next != nullptr)
    {
        hPtr = hPtr->next;
    }
    hPtr->next = new SubSeqHeadNode();
    length++;
    return hPtr->next;
}

// postcondition: appends a new node with the given value to the given list
void SubSeqsList::appendToSeq(SubSeqNode *&head, int value)
{
    bool isFinished = false;
    if (head == nullptr)
    {
        head = new SubSeqNode(value);
    }
    else
    {
        for (SubSeqNode *ptr = head; ptr != nullptr && !isFinished; ptr = ptr->next)
        {
            if (ptr->next == nullptr)
            {
                ptr->next = new SubSeqNode(value);
                isFinished = true;
            }
        }
    }
}

// postcondition: return true if value exists in SubSeqList object
bool SubSeqsList::exists(int value) const
{
    bool isFound = false;
    for (SubSeqHeadNode *ptr = hHead; ptr != nullptr && !isFound; ptr=ptr->next)
    {
        isFound = existsInSeq(value, ptr->sHead) ? true : isFound;
    }

    return isFound;
}

// postcondition: returns true if value exists in the sequence whose head is given
bool SubSeqsList::existsInSeq(int value, SubSeqNode *head) const
{
    bool isFound = false;
    for (SubSeqNode *ptr = head; ptr != nullptr && !isFound; ptr=ptr->next)
    {
        isFound = value == ptr->value ? true : isFound; 
    }

    return isFound;
}

// postcondition: returns true if all the entries are smaller than value in the given sequence
bool SubSeqsList::isAllSmaller(int value, SubSeqNode *head) const
{
    bool flag = true;
    for (SubSeqNode *ptr = head; ptr != nullptr && !flag; ptr=ptr->next)
    {
        flag = value > ptr->value ? false : flag;
    }

    return flag;
}

// postcondition: deep copies a given linked list
// and returns the pointer to the head of the copy
SubSeqNode* SubSeqsList::duplicate(SubSeqNode *original) const
{
    SubSeqNode *newHead = nullptr;
    SubSeqNode *ptrN = nullptr; // cursor for new list

    if (original != nullptr)
    {
        newHead = new SubSeqNode(original->value);
        ptrN = newHead;

        for (SubSeqNode *ptr = original->next; ptr != nullptr; ptr = ptr->next)
        {
            ptrN->next = new SubSeqNode(ptr->value);
            ptrN = ptrN->next;
        }
    }

    return newHead;
}

// postcondition: prints given linked list to console
void SubSeqsList::printSeq(SubSeqNode *head) const
{
    for (SubSeqNode *ptr = head; ptr != nullptr; ptr = ptr->next)
    {
        std::cout << ptr->value;
        if (ptr->next != nullptr)
        {
            std::cout << " --> ";
        }
    }
}

bool SubSeqsList::smallerThan(SubSeqNode *first, SubSeqNode *second) const
{

    if (second == nullptr)
    {
        return false;
    }

    if (first == nullptr)
    {
        return true;
    }

    if (first->value < second->value)
    {
        return true;
    }
    else if (first->value > second->value)
    {
        return false;
    }
    else
    {
        return smallerThan(first->next, second->next);
    }
}

void SubSeqsList::truncateSeq(SubSeqNode* ptr)
{
    if (ptr == nullptr)
    {
        return;
    }

    truncateSeq(ptr->next);
    delete ptr;
}

void SubSeqsList::truncateSeqList(SubSeqHeadNode* ptr)
{
    if (ptr == nullptr)
    {
        return;
    }

    truncateSeq(ptr->sHead);
    truncateSeqList(ptr->next);
    delete ptr;
}