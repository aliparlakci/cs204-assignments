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
        list.add(num);
    }
    cout << endl;

    cout << "FINAL CONTENT" << endl;
    list.print();
    cout << endl;
    list.printUnordered();
    list.destroy();

    return 0;
}