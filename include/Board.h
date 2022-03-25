#pragma once
#include "io.h"
#include "Location.h"
#include "Digger.h"
#include <fstream>
#include <vector>
#include <iostream>
#include "Monster.h"
#include <string>
using std::ifstream;
using std::vector;
using std::string;
using std::cout;
using std::endl;
const int life = 3;

class Board
{
public:
	/*constructor*/
	Board();
	/*function that read al the txt.board and print it*/
	void Read(ifstream &, int, int) ;
	/*finction that check if the move its ok*/
	bool isValid(int, int);
	/* funcion that check terms about movment of digger*/
	void move_digger(Location);
	/* function that containe a algorithm that makes the monsters to move*/
	bool AI_monster(int);
	/* function that check if a monster move its ok*/
	bool is_valid_monster(int, int, int);
	void reset_monsters();
	void reset_digger();
	bool move_monster(Location,Location,int);
	/* functions of set and get */
	void setLife(int);
	int get_life();
	int get_stones();
	int get_score();
	void setScore(int);
	int get_diamonds();
	int get_num_monsters();
	/* function that print the board*/
	void printBoard();
	/*function that clear the board*/
	void clearBoard();
	void obstacle(Location, int);

private:
	/*dust of vector of strings to save the board in 2d array*/
	vector<vector<string>> m_Screen;
	/* dust of vector of monster to save each monster in a cell*/
	vector<Monster> m_monsters;

	int m_ROWSCOLS,
		m_Stones,
		m_Life,
		m_num_of_monsters,
		m_Score;

	//Location m_start_monster;
	//Monster m_Monster;
	//Location m_mons;
	int m_Diamonds;
	Digger m_Digger;
	//Monster m_monster;

};