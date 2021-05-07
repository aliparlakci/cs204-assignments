#ifndef _PLAYER_H
#define _PLAYER_H

#include "aliparlakci_Parlakci_ali_hw6_board.h"

template<class T>
class Player
{
public:
	Player(Board<T> &board_);
	T openCard(int i, int j);
	bool validMove(int i, int j);
	void increaseNumberOfSuccess();
	int getNumberOfSuccess();
private:
	int score;
	Board<T> &board;
};

#include "aliparlakci_Parlakci_ali_hw6_player.cpp"
#endif