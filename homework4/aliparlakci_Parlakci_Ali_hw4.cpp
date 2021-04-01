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
void search(const string &query, const Matrix &matrix);

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
}

void search(const string &query, const Matrix &matrix)
{

}