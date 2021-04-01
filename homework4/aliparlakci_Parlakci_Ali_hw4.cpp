/*
 * CS204 Spring 2020 - Albert Levi
 * Homework 4
 * 30 March 2021
 * Written by Ali PARLAKCI
 * 28114, aliparlakci@sabanciuniv.edu
 */

#include <iostream>
#include <sstream>
#include <string>

#include "aliparlakci_Parlakci_Ali_hw4_stack.h"

using namespace std;

int main()
{
	Stack myStack;

	cout << "Enter nums: ";

	int entry;
	while (cin >> entry)
	{
		myStack.push(entry);
	}

	cout << "List of nums: " << endl;

	while (!myStack.isEmpty())
	{
		cout << myStack.pop() << endl;
	}

	return 0;
}