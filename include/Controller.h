#pragma once
#include "Board.h"


const int SPACE = 32;

class Controller
{
public:
	/**** Controller conastructor****/
	Controller();
	/*function that control the player moves and condition*/
	void player(Board&);
	/*function that control the monster moves and condtuion*/
	void monster(Board&);
	/*function that run the board and levels and reset the game*/
	void run();


private:
	/*num of rows cols of the board*/
	int m_ROWS_COLS;
	/*num of stones that have in any level*/
	int m_Stones;
	/* member that resposnsible the levels*/
	int m_Level;
	/* member that responsible the score*/
	int m_Point;
	/* member that responsible the life*/
	int m_Life;
	/* member that save the amount of diamond in any level*/
	int m_Diamonds;
};

