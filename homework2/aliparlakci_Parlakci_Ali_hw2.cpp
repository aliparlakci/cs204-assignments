/*
 * CS204 Spring 2020 - Albert Levi
 * Homework 2
 * 13 March 2021
 * Written by Ali PARLAKCI
 * 28114, aliparlakci@sabanciuniv.edu
 */

#include <iostream>
#include <string>
#include <sstream>
#include <limits>

#include "aliparlakci_Parlakci_Ali_hw2_linkedlist.h"

using namespace std;

char getOrderMode();
istringstream getNumbers();
void prune(int treshold, LinkedList &list, char mode);
void print(LinkedList &list);

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
            prune(number, list, orderMode);
            cout << endl;

            cout << "Appended: " << number << endl;
            list.push_back(number);
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
    
    list.destroy();
    cout << endl;
}

// postcondition: returns A for ascending and D for descending
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

// postcondition: returns a stream of given numbers
istringstream getNumbers()
{
    string input;
    cout << "Please enter the numbers in a line: ";

    getline(cin, input);
    istringstream lineStream(input);

    return lineStream;
}

// precondition: mode is either A or D
// postcondition: removes values bigger than treshold if mode is A, lower than treshold if mode is D
void prune(int treshold, LinkedList &list, char mode)
{
    bool didDeleteAny = false;

    for (int i = 0; i < list.length; i++)
    {
        int value = list.at(i);
        if ( (mode == 'A' && value > treshold) || (mode == 'D' && value < treshold) )
        {
            cout << value << (i == list.length - 1 ? "" : " ");
            list.remove(i);
            i--;    // Since the ith element is removed, i+1st element became the ith element
            didDeleteAny = true;
        }
    }

    cout << (didDeleteAny ? "" : "None");
}

// postcondition: prints the list to console separated by spaces
void print(LinkedList &list)
{
    for (int i = 0; i < list.length; i++)
    {
        cout << list.at(i) << (i == list.length - 1 ? "" : " ");
    }
}