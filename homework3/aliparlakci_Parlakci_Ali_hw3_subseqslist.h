/*
 * CS204 Spring 2020 - Albert Levi
 * Homework 3
 * 22 March 2021
 * Written by Ali PARLAKCI
 * 28114, aliparlakci@sabanciuniv.edu
 */

#ifndef _SUB_SEQS_LIST_H
#define _SUB_SEQS_LIST_H

struct SubSeqNode
{
    int value;
    SubSeqNode * next;
    SubSeqNode() : value(0), next(nullptr)
    {};
    SubSeqNode(int val) : value(val), next(nullptr)
    {};
    SubSeqNode(int val, SubSeqNode * next) : value(val), next(next)
    {};
};

struct SubSeqHeadNode
{
    int size;
    SubSeqNode * sHead;
    SubSeqHeadNode * next;
    SubSeqHeadNode() : size(0), sHead(nullptr), next(nullptr)
    {}; 
    SubSeqHeadNode(SubSeqNode *sHead, int size) : size(size), sHead(sHead), next(nullptr)
    {}; 
};


class SubSeqsList
{
public:
    SubSeqsList();
    void add(int entry);
    void remove(int entry);
    void print() const;
    void destroy();
private:
    SubSeqHeadNode *hHead;
    int length;
    void appendToSeq(SubSeqNode *&head, int value) const;
    bool exists(int value) const;
    bool existsInSeq(int value, SubSeqNode *head) const;
    bool isAllSmaller(int value, SubSeqNode *head) const;
    SubSeqNode* duplicate(SubSeqNode *original) const;
    void printSeq(SubSeqNode *head) const;
    SubSeqHeadNode* mergeTwoHeadsLists(SubSeqHeadNode *first, SubSeqHeadNode *second) const;
    bool smallerThan(SubSeqNode *first, SubSeqNode *second) const;
    void truncateSeq(SubSeqNode *ptr) const;
    void truncateSeqList(SubSeqHeadNode *ptr) const;
};  

#endif