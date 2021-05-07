#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

#include "aliparlakci_Parlakci_ali_hw6_board.h"

template<class T>
Board<T>::Board() {}

template<class T>
Board<T>::Board(Board &copy) {}

template<class T>
Board<T>::Board(int rows, int columns) : rows(rows), columns(columns) 
{
	matrix = new cell<T>* [rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new cell<T> [columns];
	}
}

template<class T>
Board<T>::~Board()
{
	for (int i = 0; i < rows; i++)
	{
		delete matrix[i];
	}
	delete[] matrix;

	matrix = nullptr;
}

template<class T>
void Board<T>::readBoardFromFile(std::ifstream &file)
{
	string line;
	int i = 0;
	while(i < rows && getline(file, line))
	{
		istringstream ss(line);

		T item;
		int j = 0;
		while(j < columns && ss >> item)
		{
			matrix[i][j].value = item;
			j++;
		}
		i++;
	}
}

template<class T>
void Board<T>::displayBoard() 
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (matrix[i][j].closed)
			{
				cout << '-';
			}
			else
			{
				cout << matrix[i][j].value;
			}
			cout << ' ';
		}
		cout << endl;
	}
}

template<class T>
void Board<T>::openCard(int i, int j)
{
	if (   0 <= i && i <= rows
		&& 0 <= j && j <= columns)
	{
		matrix[i][j].closed = false;
	}

}

template<class T>
void Board<T>::closeCard(int i, int j)
{
	if (   0 <= i && i <= rows
		&& 0 <= j && j <= columns)
	{
		matrix[i][j].closed = true;
	}

}

template<class T>
T Board<T>::getCard(int i, int j)
{
	if (   0 <= i && i <= rows
		&& 0 <= j && j <= columns)
	{
		return matrix[i][j].value;
	}

}

template<class T>
bool Board<T>::isClosed(int i, int j)
{
	if (   0 <= i && i <= rows
		&& 0 <= j && j <= columns)
	{
		return matrix[i][j].closed;
	}
}

template<class T>
int Board<T>::getRow()
{
	return rows;
}

template<class T>
int Board<T>::getColumn()
{
	return columns;
}