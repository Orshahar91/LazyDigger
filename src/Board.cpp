#include "Board.h"

/* constructor*/
Board::Board()
	: m_ROWSCOLS(0), m_Life(life), m_Stones(0), m_Diamonds(0), m_Score(0),  m_num_of_monsters(0), m_Digger() {}

/* finction that recive file and size and stones and read the file*/
void Board::Read(ifstream &myfile, int RowsCols, int stones)
{
	/*reset num of stines in each level*/
	m_Stones = stones;
	/* reset size of each level*/
	m_ROWSCOLS = RowsCols;
	char c;

	m_Screen.clear();
	/*reset diamond in each level*/
	m_Diamonds = 0;
	m_monsters.clear();
	/*reset monster in each level*/
	m_num_of_monsters = 0;
	/*define the size of each level*/
	m_Screen.resize(m_ROWSCOLS);
	/*for the empty line between levels*/
	//myfile.get();
	/*loop that run on the board*/
	for (int i = 0; i < m_ROWSCOLS; i++)
	{
		m_Screen[i].resize(m_ROWSCOLS);

		for (int j = 0; j < m_ROWSCOLS; j++)
		{
			myfile.get(c);

			if (c == 10)
			{
				myfile.get(c);
			}
			m_Screen[i][j].push_back(c);
			/* thats how we know where the location of the digger in start each level and save him*/
			if (m_Screen[i][j] == "/")
			{
				Location temp(i, j);
				Digger digg(temp);
				m_Digger = digg;
			}

			/* count the num of monsters that incluse in each level and save the start location of each of them*/
			if (m_Screen[i][j] == "!")
			{
				m_num_of_monsters++;
				Location temp(i, j);
				Monster monster(temp);
				m_monsters.push_back(monster);
				m_monsters.resize(m_num_of_monsters);
			}
			
			/*thats how we know how much diamond we have in each level*/
			if (m_Screen[i][j] == "D")
			{
				m_Diamonds++;
			}
		}	
	}
}

//-----------------------------------------------------------------------------
/*function that recive x,y and tell if move its ok*/
bool Board::isValid(int row, int col)
{
	Location digger = m_Digger.getLocation();

	int Row = row + digger.row;
	int Col = col + digger.col;
	/*that terms check if the location is in the range of the board and if we move to wall*/
	if (Row < m_Screen.size() && Col < m_Screen.size() && m_Screen[Row][Col] != "#")
	{
		Location next_move(Row, Col);

		move_digger(next_move);
	
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
/*function that manage what happend with the stat members*/
void Board::move_digger(Location move)
{	
	bool valid_move = false;
	bool hit = false;
	Location digger = m_Digger.getLocation();
	
	/* if we tuch monster the life = life -1*/
	if (m_Screen[move.row][move.col] == "!")
	{
		m_Life = m_Life-1;
		hit = true;
	}
	/*if we eat diamond */
	if (m_Screen[move.row][move.col] == "D")
	{
		m_Diamonds--;
		m_Score += 15;
		valid_move = true;
	}
	/* if the digger eat stone*/
	if (m_Screen[move.row][move.col] == "@")
	{
		m_Stones--;
		valid_move = true;
	}
	/* if there is nothing in the next cell its ok*/
	if (m_Screen[move.row][move.col] == " ")
	{
		valid_move = true;
	}
	/* check  if the move was valid and update the digger location*/
	if (valid_move)
	{
		m_Screen[digger.row][digger.col] = " ";
		m_Digger.set__Location(move);
		m_Screen[move.row][move.col] = "/";
	}
	/* if we hit monster the digger ruturn to the start location that he was in the start stage*/
	if (hit)
	{
		reset_digger();
		reset_monsters();
	}

	
}
/*function that manage the monsters moves*/
bool Board::AI_monster(int index)
{
	
	bool hit = false;
	bool move = false;

	Location digger = m_Digger.getLocation();
	Location curr_monster = m_monsters[index].getLocation();

	/*terms that make the algorithm of monsters and moved them*/
	if ((!move) && digger.row > curr_monster.row && is_valid_monster(curr_monster.row +1, curr_monster.col, index))
	{
		Location next(curr_monster.row + 1, curr_monster.col);
		hit = move_monster(curr_monster, next, index);
		move = true;
	}

	if ((!move) && digger.row < curr_monster.row && is_valid_monster(curr_monster.row - 1, curr_monster.col, index))
	{
		Location next(curr_monster.row - 1, curr_monster.col);
		hit = move_monster(curr_monster, next, index);
		move = true;
	}

	if ((!move) && digger.col > curr_monster.col && is_valid_monster(curr_monster.row, curr_monster.col+1, index))
	{
		Location next(curr_monster.row, curr_monster.col+1);
		hit = move_monster(curr_monster, next, index);
		move = true;
	}

	if ((!move) && digger.col < curr_monster.col && is_valid_monster(curr_monster.row, curr_monster.col-1, index))
	{
		Location next(curr_monster.row, curr_monster.col -1);
		hit = move_monster(curr_monster, next, index);
		move = true;
	}

	if (!move) // Reached an obstacle
	{
		obstacle(curr_monster, index); // find a way around. 
	}


		/* terms that say if the monster tuch the digger life= life-1*/


		/*if the monster tuch the digger we update both location to the start of stage*/
		if (hit)
		{
			reset_monsters();
			reset_digger();
			
			return true;
		}

		
		 if (!hit)
		{
			Location curr = m_monsters[index].getLocation();
			m_Screen[curr.row][curr.col] = "!";
			return false;
		}

		 return false;
}

//-----------------------------------------------------------------------------

bool Board::move_monster(Location curr,Location move, int index)
{
	if (!m_monsters[index].get_diamond())
		m_Screen[curr.row][curr.col] = " ";
	
	if (m_monsters[index].get_diamond())
		m_Screen[curr.row][curr.col] = "D";

	m_monsters[index].set_diamond(false);

	m_monsters[index].setLocation(move);

	if (m_Screen[move.row][move.col] == "/")
	{
		m_Life = m_Life - 1;
		return true;
	}

	if (m_Screen[move.row][move.col] == "D")
	{
		m_monsters[index].set_diamond(true);
	}

	return false;
}


void Board::obstacle(Location monster, int index)
{
	if (!is_valid_monster(monster.row + 1, monster.col,index) || !is_valid_monster(monster.row - 1, monster.col, index))
	{
		if (is_valid_monster(monster.row, monster.col - 1, index))
		{
			Location next(monster.row, monster.col - 1);
				move_monster(monster, next, index);
		}

		else if (is_valid_monster(monster.row, monster.col + 1, index))
		{
			Location next(monster.row, monster.col + 1);
				move_monster(monster, next, index);
		}
	}

	else if (!is_valid_monster(monster.row, monster.col + 1, index) || !is_valid_monster(monster.row, monster.col - 1, index))
	{
		if (is_valid_monster(monster.row + 1, monster.col, index))
		{
			Location next(monster.row + 1, monster.col);
			move_monster(monster, next, index);
		}

		else if (is_valid_monster(monster.row - 1, monster.col,index))
		{
			Location next(monster.row - 1, monster.col);
			move_monster(monster, next, index);
		}
	}
}


void Board::reset_monsters()
{
	for (int i = 0; i < m_monsters.size(); i++)
	{
		Location monster = m_monsters[i].getLocation();
		m_Screen[monster.row][monster.col] = " ";

		Location start_monster = m_monsters[i].getOriginalLocation();
		m_monsters[i].setLocation(start_monster);


		m_Screen[start_monster.row][start_monster.col] = "!";

	}
}

void Board::reset_digger()
{
	Location digger = m_Digger.getLocation();
	Location start_digger = m_Digger.getOriginalLocation();

	m_Screen[digger.row][digger.col] = " ";
	m_Digger.set__Location(start_digger);
	m_Screen[start_digger.row][start_digger.col] = "/";

}


/*check if the monster move was valid*/
bool Board :: is_valid_monster(int row, int col, int index)
{
	if (row < m_Screen.size() && col < m_Screen.size() && m_Screen[row][col] != "#"
		&& m_Screen[row][col] != "@" && m_Screen[row][col] != "!")
	{

		return true;
	}

	return false;
}

/* return num of monsters*/
int Board::get_num_monsters()
{
	return m_num_of_monsters;
}

//-----------------------------------------------------------------------------
/*return amount of life*/
int Board::get_life()
{
	return m_Life;
	
}

//-----------------------------------------------------------------------------
/* return num of stones*/
int Board::get_stones()
{
	return m_Stones;
}

//-----------------------------------------------------------------------------
/* return the player score*/
int Board::get_score()
{
	return m_Score;
}

void Board::setScore(int num)
{
	m_Score += num;
}

/* set the num of life*/
void Board::setLife(int num)
{
	m_Life += num;
}
/* return num of diamond*/
int Board::get_diamonds()
{
	return m_Diamonds;
}

//-----------------------------------------------------------------------------
/* finction that print the board*/
void Board::printBoard()
{
	for (int i = 0; i < m_Screen.size(); i++)
	{
		for (int j = 0; j < m_Screen[i].size(); j++)
		{
			cout << m_Screen[i][j];
		}
		cout << endl;
	}
}

//-----------------------------------------------------------------------------
/*function that ckear the board*/
void Board::clearBoard()
{
	std::system("cls");
}
