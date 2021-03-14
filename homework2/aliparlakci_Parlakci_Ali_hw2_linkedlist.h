/*
 * CS204 Spring 2020 - Albert Levi
 * Homework 2
 * 13 March 2021
 * Written by Ali PARLAKCI
 * 28114, aliparlakci@sabanciuniv.edu
 */

#ifndef _LINKED_LIST
#define _LINKED_LIST

#include <string>

struct node
{
    int value;
    node* next;
    node() : value(0), next(NULL)
    {};
    node(int value, node* next) : value(value), next(next)
    {};
};

class LinkedList
{
public:
    int length;
    LinkedList();
    void push_back(int value);
    void insert(int indice, int value);
    int at(int indice) const;
    void remove(int indice);
    bool contains(int value) const;
    void reverse();
    void destroy();
private:
    node* head;
    node* getNode(int indice) const;
    void truncate(node* nodeptr);
};

#endif