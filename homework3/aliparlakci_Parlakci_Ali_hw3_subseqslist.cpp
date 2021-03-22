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
        SubSeqHeadNode *newHeadsList = new SubSeqHeadNode();
        SubSeqHeadNode *nPtr = newHeadsList;
        SubSeqHeadNode *hPtr = hHead;

        for (SubSeqHeadNode *hPtr = hHead; hPtr != nullptr; hPtr = hPtr->next)
        {
            if (isAllSmaller(entry, hPtr->sHead))
            {
                SubSeqHeadNode *newSeq = new SubSeqHeadNode(duplicate(hPtr->sHead), hPtr->size);
                appendToSeq(newSeq->sHead, entry);
                newSeq->size++;
                nPtr->next = newSeq;
                nPtr = nPtr->next;
                length++;
            }
        }

        hHead = mergeTwoHeadsLists(hHead, newHeadsList->next);

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

    if (exists(entry))
    {
        SubSeqHeadNode *head = new SubSeqHeadNode();
        SubSeqHeadNode *temp = nullptr;
        head->next = hHead;

        for (SubSeqHeadNode *hPtr = head; hPtr->next != nullptr;)
        {
            if (existsInSeq(entry, hPtr->next->sHead))
            {
                temp = hPtr->next;
                hPtr->next = hPtr->next->next;
                delete temp;
                temp = nullptr;
                length--;
            }
            else
            {
                hPtr = hPtr->next;
            }
        }

        std::cout << "All subsequence(s) containing "
            << entry 
            << " has/have been deleted" << std::endl;
    }
    else
    {
        std::cout << "There is no subsequence that contains "
            << entry 
            << " to be deleted" << std::endl;
    }
}

void SubSeqsList::print() const
{
    if (length > 1)
    {
        for (SubSeqHeadNode *ptr = hHead->next; ptr != nullptr; ptr=ptr->next)
        {
            std::cout << ptr->size << " | ";
            printSeq(ptr->sHead);
            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "List is empty!" << std::endl;
    }
}

void SubSeqsList::destroy()
{
    truncateSeqList(hHead);
    hHead = new SubSeqHeadNode;
    length = 1;
}

// postcondition: appends a new sequence head to the end of the heads list
// and returns the pointer to it
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
    for (SubSeqNode *ptr = head; ptr != nullptr && flag; ptr=ptr->next)
    {
        flag = ptr->value < value;
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

// precondition: first and second are two sorted linked lists with different or same lengths
// postcondition: returns a pointer to the first element of the sorted merged linked list
SubSeqHeadNode* SubSeqsList::mergeTwoHeadsLists(SubSeqHeadNode *first, SubSeqHeadNode *second) const
{
    SubSeqHeadNode *head = new SubSeqHeadNode();
    SubSeqHeadNode *ptr = head;
    SubSeqHeadNode *temp;

    while(first != nullptr || second != nullptr)
    {
        if (first == nullptr)
        {
            ptr->next = second;
            second = nullptr;
        }
        else if (second == nullptr)
        {
            ptr->next = first;
            first = nullptr;
        }
        else
        {
            if (first->size < second->size)
            {
                ptr->next = first;
                first = first->next;
            }
            else if (first->size == second->size && smallerThan(first->sHead, second->sHead))
            {
                ptr->next = first;
                first = first->next;
            }
            else
            {
                ptr->next = second;
                second = second->next;
            }
        }

        ptr = ptr->next;
    }

    return head->next;
}

// precondition: first and second are two sorted linked lists with same length
// postcondition: returns true if first is strictly smaller
bool SubSeqsList::smallerThan(SubSeqNode *first, SubSeqNode *second) const
{

    if (first == nullptr || second == nullptr)
    {
        return false;
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