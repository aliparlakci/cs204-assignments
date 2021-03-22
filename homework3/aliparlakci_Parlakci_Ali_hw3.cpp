/*
 * CS204 Spring 2020 - Albert Levi
 * Homework 3
 * 22 March 2021
 * Written by Ali PARLAKCI
 * 28114, aliparlakci@sabanciuniv.edu
 */

#include <iostream>
#include <sstream>
#include <string>

#include "aliparlakci_Parlakci_Ali_hw3_subseqslist.h"

using namespace std;

int main()
{
    string line;

    cout << "Please enter the numbers in a line: ";
    getline(cin, line);
    istringstream numStream(line);
    cout << endl;

    SubSeqsList list;

    int num;
    while(numStream >> num)
    {
        if (num >= 0) list.add(num);
        else if (num < 0) list.remove(-num);
    }
    cout << endl;

    cout << "FINAL CONTENT" << endl;
    list.print();
    // cout << endl;
    list.destroy();

    return 0;
}