#ifndef _SUB_SEQS_LIST
#define _SUB_SEQS_LIST

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
};


class SubSeqsList
{
public:
    SubSeqsList();
    void add(int entry);
    void remove(int entry);
    void print() const;
    void printUnordered() const;
    void destroy();
private:
    SubSeqHeadNode *hHead;
    int length;
    void addNewSeq(SubSeqHeadNode *head);
    SubSeqHeadNode* addNewSeq();
    void appendToSeq(SubSeqNode *&head, int value);
    bool exists(int value) const;
    bool existsInSeq(int value, SubSeqNode *head) const;
    bool isAllSmaller(int value, SubSeqNode *head) const;
    SubSeqNode* duplicate(SubSeqNode *original) const;
    void printSeq(SubSeqNode *head) const;
    bool smallerThan(SubSeqNode *first, SubSeqNode *second) const;
    void truncateSeq(SubSeqNode *ptr);
    void truncateSeqList(SubSeqHeadNode *ptr);
};  

#endif