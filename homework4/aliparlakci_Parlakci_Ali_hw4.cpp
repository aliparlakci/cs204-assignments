/*
 * CS204 Spring 2020 - Albert Levi
 * Homework 4
 * 30 March 2021
 * Written by Ali PARLAKCI
 * 28114, aliparlakci@sabanciuniv.edu
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "aliparlakci_Parlakci_Ali_hw4_stack.h"
#include "aliparlakci_Parlakci_Ali_hw4_matrix.h"

using namespace std;

void openFile(ifstream &file);
void importMatrixFromFile(Matrix &matrix, ifstream &file);
void search(const string &query, Matrix &matrix);
void printStackReversed(Stack &stack);

int main()
{
	int rows, cols;
	cout << "Please enter the number of rows: ";
	cin >> rows;

	cout << "Please enter the number of cols: ";
	cin >> cols;

	ifstream inputFileStream;
	openFile(inputFileStream);

	Matrix matrix(rows, cols);
	importMatrixFromFile(matrix, inputFileStream);

	string query;
	cout << "Please enter a string of bits to search (CTRL+Z to quit): ";
	while(cin >> query)
	{
		search(query, matrix);

		cout << "---------------------------------------------------------" << endl;
		cout << "Please enter a string of bits to search (CTRL+Z to quit): ";
	}

	return 0;
}

void openFile(ifstream &file)
{
	string filePath;

	cout << "Please enter the name of the file: ";
	cin >> filePath;
	file.open(filePath.c_str());

	while (file.fail())
	{
		cout << "File cannot be opened." << endl;
		file.clear();
		cout << "Please enter the name of the file again: ";
		cin >> filePath;
		file.open(filePath.c_str());
	}

	cout << endl;
}

void importMatrixFromFile(Matrix &matrix, ifstream &file)
{
	int rows, cols;
	matrix.size(rows, cols);

	string line;
	for (int i = 0; getline(file, line); i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrix.set(i, j, line[j]);
		}
	}
}

void search(const string &query, Matrix &matrix)
{
	Stack stack;
	int rows, cols;
	bool isFound = false;
	matrix.size(rows, cols);

	int x = 0, y = 0, bit = 0;
	while(!isFound || matrix.getFlag(0, 0) == true)
	{
		if (matrix.getFlag(x,y) == false && query[bit] == matrix.getVal(x,y))
		{
			stack.push(x, y);

			if (bit == query.length() - 1)
			{
				isFound = true;
			}
			else if (y+1 < cols && matrix.getFlag(x, y+1) == false)
			{
				y++;
				bit++;
			}
			else if (x+1 < rows && matrix.getFlag(x+1, y) == false)
			{
				x++;
				bit++;
			}
			else
			{
				matrix.setFlag(x, y, true);
				stack.pop(x, y);
			}
		}
		else
		{
			matrix.setFlag(x, y, true);
			stack.pop(x, y);
			bit--;
		}
	}

	cout << "The bit string ";
	if (stack.isEmpty())
	{
		cout << query << " could not be found." << endl;
	}
	else
	{
		cout << query << " is found following these cells:" << endl;
		printStackReversed(stack);
		cout << endl;
	}
}

void printStackReversed(Stack &stack)
{
	if (!stack.isEmpty())
	{
		int x, y;
		stack.pop(x, y);
		printStackReversed(stack);
		cout << "(" << x << "," << y << ") ";
	}
}