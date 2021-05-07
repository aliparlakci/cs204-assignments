#include "aliparlakci_Parlakci_ali_hw6_player.h"

template<class T>
Player<T>::Player(Board<T> &board_) : board(board_), score(0) {}

template<class T>
T Player<T>::openCard(int i, int j)
{
	board.openCard(i, j);
	return board.getCard(i, j);
}

template<class T>
bool Player<T>::validMove(int i, int j)
{
	int rows = board.getRow();
	int columns = board.getColumn();

	return (i < 0 || i > rows) || (j < 0 || j > columns) || board.isClosed(i, j); 
}

template<class T>
void Player<T>::increaseNumberOfSuccess()
{
	score++;
}

template<class T>
int Player<T>::getNumberOfSuccess()
{
	return score;
}