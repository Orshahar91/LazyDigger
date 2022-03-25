#include "Controller.h"
/* controller constructor*/
Controller::Controller() : m_ROWS_COLS(0), m_Level(1), m_Life(0), m_Point(0), m_Stones(0), m_Diamonds(0)
{

}
/* function that run the game*/
void Controller::run()
{
	bool reset = false;
	bool level = false;

	/* read from board txt file*/
	ifstream myfile("Board.txt");

	Board board;
	/* run untile the board txt file is end*/
	while (!myfile.eof())
	{
		
		fpos_t save = myfile.tellg();
		string c;
		/*count the size of each level*/
		myfile >> c;
		m_ROWS_COLS = stoi(c);
		/*count the num of stones that have in each level*/
		myfile >> c;
		m_Stones = stoi(c) ;

		board.Read(myfile, m_ROWS_COLS, m_Stones);
		board.clearBoard();
		board.printBoard();
		/*if is level so we go to next level*/
		if (level)
		{
			board.setScore(20);
			m_Level++;
			level = false;
		}
		/*if is reset the digger return to his first place*/
		if (reset)
		{
			board.clearBoard();
			reset = false;
			board.printBoard();
		}
		/* this while is run until we finish each level*/
		while (!level)
		{
			m_Life = board.get_life();
			m_Stones = board.get_stones();
			m_Point = board.get_score();
			m_Diamonds = board.get_diamonds();
			cout << "Level: " << m_Level << endl << "Life : " << m_Life << endl << "Score: " << m_Point << endl << "Stones: " << m_Stones << endl;

			if (m_Life < 1)
			{
				cout << "GAME OVER!";
				//myfile.close();
				return;
			}
			/* if the digger eat al of diamond in the curr level -> level is true*/
			if (m_Diamonds == 0)
			{
				board.clearBoard();
				myfile.get();
				level = true;
				break;
			}
			/*if the digger eat stone more than possible int curr level -> reset is true*/
			if (m_Stones < 0)
			{
				board.setLife(-1);
				reset = true;
				myfile.seekg(save);
				break;
			}


			player(board);
			board.clearBoard();
			board.printBoard();

			monster(board);
			board.clearBoard();
			board.printBoard();

		}
	}

	cout << "You Win!" << endl;
	//myfile.close();
}

//-----------------------------------------------------------------------------

void Controller::monster(Board& board )
{

	bool move = false;
	/*count the num of monster that have in each level*/
	int size = board.get_num_monsters();

	/*run in array of monsters and send each monster to function that control the momster*/
	for (int i = 0; i < size && (!move); i++)
	{
		move = board.AI_monster(i);
	}

}
/*function that control the movement of digger*/
void Controller::player(Board& board)
{
	int input;
	bool game = false;
	/* while game = false, we click on each of the keyboard*/
	while (!game)
	{
		input = Keyboard::getch();
		switch (input)
		{
			/*click left and check if the move is valid */
		case KB_LEFT:
			if (board.isValid(0, -1))
				game = true;

			break;

			/*click up and check if the move is valid */
		case KB_UP:
			if (board.isValid(-1, 0))
				game = true;

			break;

			/*click right and check if the move is valid */
		case KB_RIGHT:
			if (board.isValid(0, 1))
				game = true;

			break;
			/*click down and check if the move is valid */
		case KB_DOWN:
			if (board.isValid(1, 0))
				game = true;
			break;
			/*if the player click on space the digger lost a turn*/
		case SPACE:
			return;
		}
		
	}
}