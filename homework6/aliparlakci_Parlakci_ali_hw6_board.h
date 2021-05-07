#ifndef _BOARD_H
#define _BOARD_H

#include <fstream>

template<class T>
struct cell
{
	bool closed;
	T value;
	cell() : closed(true) {};
};

template<class T>
class Board
{
public:
	Board();
	Board(Board &copy);
	Board(int rows, int columns);
	~Board();
	void readBoardFromFile(std::ifstream &file);
	void displayBoard();
	void openCard(int i, int j);
	void closeCard(int i, int j);
	T getCard(int i, int j);
	bool isClosed(int i, int j);
	int getRow();
	int getColumn();

private:
	cell<T> ** matrix;
	int rows;
	int columns;
};

#include "aliparlakci_Parlakci_ali_hw6_board.cpp"
#endif