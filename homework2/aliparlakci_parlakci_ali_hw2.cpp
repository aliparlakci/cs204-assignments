#include <iostream>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

struct node
{
    int value;
    node* next;
    node() : value(0), next(NULL)
    {};
    node(int _value, node* _next) : value(_value), next(_next)
    {};
};

class LinkedList
{
public:
    int length;
    LinkedList();
    void push(int _value);
    void insert(int _indice, int _value);
    int at(int _indice) const;
    void remove(int _indice);
    bool contains(int _value) const;
    void truncate();
private:
    node* head;
    node* _get(int _indice) const;
    void _truncate(node* _node);
};

char getOrderMode();
istringstream getNumbers();
void removeGreater(int treshold, LinkedList &list);
void removeSmaller(int treshold, LinkedList &list);
void print(LinkedList &list);
int test();

int main()
{
    char orderMode = getOrderMode();
    istringstream numbers = getNumbers();
    cout << endl;

    LinkedList list;

    int number;
    while(numbers >> number)
    {
        cout << "Next number: " << number << endl;

        if (list.contains(number))
        {
            cout << number << " is already in the list!" << endl;
        }
        else
        {
            cout << "Deleted nodes: ";
            if (orderMode == 'A')
            {
                removeGreater(number, list);
            }
            else if (orderMode == 'D')
            {
                removeSmaller(number, list);
            }
            cout << endl;

            list.push(number);
            cout << "Appended: " << number << endl;
        }
        
        cout << "List content: ";
        print(list);
        cout << endl << endl;
    }
    
    if (list.length > 0)
    {
        cout << "All the nodes are deleted at the end of the program: ";
        print(list);
    }
    else
    {
        cout << "The list is empty at the end of the program and nothing is deleted";
    }

    list.truncate();
}

char getOrderMode()
{
    string input;
    
    cout << "Please enter the order mode (A/D): ";
    cin >> input;

    while (input != "A" && input != "D")
    {
        cout << "Please enter the order mode again (A/D): ";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin >> input;
    }

    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    return input == "A" ? 'A' : 'D';
}

istringstream getNumbers()
{
    string input;
    cout << "Please enter the numbers in a line: ";

    getline(cin, input);
    istringstream lineStream(input);

    return lineStream;
}

void removeGreater(int treshold, LinkedList &list)
{
    bool didDeleteAny = false;

    for (int i = 0; i < list.length; i++)
    {
        int value = list.at(i);
        if (value > treshold)
        {
            cout << value << (i == list.length - 1 ? "" : " ");
            list.remove(i);
            i--;    // Since the ith element is removed i+1st element became the ith element
            didDeleteAny = true;
        }
    }

    cout << (didDeleteAny ? "" : "None");
}

void removeSmaller(int treshold, LinkedList &list)
{
    bool didDeleteAny = false;

    for (int i = 0; i < list.length; i++)
    {
        int value = list.at(i);
        if (value < treshold)
        {
            cout << value << (i == list.length - 1 ? "" : " ");
            list.remove(i);
            i--;    // Since the ith element is removed i+1st element became the ith element
            didDeleteAny = true;
        }
    }

    cout << (didDeleteAny ? "" : "None");
}

void print(LinkedList &list)
{
    for (int i = 0; i < list.length; i++)
    {
        cout << list.at(i) << (i == list.length - 1 ? "" : " ");
    }
}

LinkedList::LinkedList() : head(NULL), length(0)
{
}

void LinkedList::push(int _value)
{
    insert(length, _value);
}

void LinkedList::insert(int _indice, int _value)
{
    if (_indice == 0) 
    {
        head = new node(_value, head);
        length++;
    }
    else if (_indice >= 0 && _indice <= length)
    {
        node *ptr = _get(_indice - 1);
        ptr->next = new node(_value, ptr->next);
        length++;
    }
}

int LinkedList::at(int _indice) const
{
    node* ptr = _get(_indice);
    return ptr != NULL ? ptr->value : string::npos;
}

node* LinkedList::_get(int _indice) const
{
    node* ptr = head;

    if (ptr != NULL && _indice >= 0 && _indice < length)
    {
        int counter = 0;
        int value;

        while (ptr != NULL & counter <= _indice)
        {
            if (counter == _indice)
            {
                return ptr;
            }
            
            ptr = ptr->next;
            counter++;
        }
    }

    return NULL;
}

void LinkedList::remove(int _indice)
{
    if (_indice >= 0 && _indice < length)
    {
        node *ptr, *cursor;

        if (_indice == 0)
        {
            ptr = head;
            head = head->next;
            delete ptr;
        }
        else
        {
            cursor = _get(_indice - 1);
            ptr = cursor->next;
            cursor->next = cursor->next != NULL ? cursor->next->next : NULL;
            delete ptr;
        }
        length--;
    }
}

bool LinkedList::contains(int _value) const
{
    bool doesExist = false;

    for (node *ptr = head; ptr != NULL && !doesExist; ptr = ptr->next)
    {
        doesExist = ptr->value == _value ? true : doesExist;
    }

    return doesExist;
}

void LinkedList::truncate()
{
    _truncate(head);
    head = NULL;
    length = 0;
}

void LinkedList::_truncate(node* _node)
{
    if (_node == NULL)
    {
        return;
    }
    
    _truncate(_node->next);
    delete _node;
}