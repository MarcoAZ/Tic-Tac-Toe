/***************************************************
* Author:			Marco Zamora
* Date Created:		11/14/2014
* Last Modified: 	11/14/2014
* Filename:			ticTacToe.cpp
*
* Overview: the classic game of tic-tac-toe!
*	
* Input: 
*		Command line argument of number of games to play.
*	Other inputs are squares to take.
*	
* Output:
*	Displays visual board and announces victories.
*	
****************************************************/
#include <iostream>
#include <cstdlib>		//for atoi

const int boardSize = 3;

//starts board with '.' in each square
void initBoard( char array[][boardSize] );

//draws the current state of the game board
void drawBoard( char array[][boardSize], int boardSize);

//gets a move, checks if open, sets player piece in square
void getMove( char array[][boardSize], int boardSize, char &mark);

//checks if the game board is full
bool checkFullBoard( char array[][boardSize], int boardSize);

//checks if a player has won
bool checkForVictory( char array[][boardSize], int boardSize);

//clears cin buffer
void clear_cin();


int main ( int argc, char *argv[] )
{
	int games = 1;				//total games to play

	//if a number of games to play was passed in, change games
	if ( argc > 1)
	{
		if( atoi( argv[1]) > 0)
			games = atoi( argv[1]);
	}

	int score[2];		//keeps scores for each player in arrays
	score[0] = 0;		//0 == X player
	score[1] = 0;		//1 = Y player; start at 0 score

	int first = 1; 		//helps switch first player

	char player = 'X';	//the current player

	while ( games > 0 )
	{
		bool victory = false;			//changed to true when victory confirmed
		bool tie = false;				//change to true when board is full
										//but no winner declared

		char board[boardSize][boardSize];//prepare board array

		//fill board with '.'
		initBoard( board );

		//set up first player
		if (first == 1)
			player = 'X';
		else
			player = 'O';

		//run this game
			do
			{
				drawBoard( board, boardSize );

				getMove( board, boardSize, player );
			
				victory = checkForVictory( board, boardSize );

				//if player wins and happens to fill the final square
				//checking for a tie would evaluate true but we know its not a tie
				if( !victory)
					tie = checkFullBoard( board, boardSize );

			} while( !tie && !victory);

		//draw final board one more time
		drawBoard( board, boardSize );
		
		if ( tie )
		{
			std::cout << "No winner\n";
		}
		else
		{
			//the last person to have moved must have set off the victory condition
			//so I'll have to reset the player switch at the end of getMove()
			if ( player == 'X')
				player = 'O';
			else
				player = 'X';

			std::cout << "Player " << player << " has won this game!\n";
			
			//if X won,increment there score, otherwise increment O's score
			if ( player == 'X' )
				score[0]++;
			else
				score[1]++;
		}
		
		//switch player by flipping first value
		first *= -1;

		//finish this game
		games--;
	}

	//all games are done, show final scores
	std::cout << "Player X won " << score[0] << " games.\n";
	std::cout << "Player O won " << score[1] << " games.\n";

	//compare scores to anounce final winner
	if( score[0] > score[1])
		std::cout << "Player X wins the tournament!\n";
	else if( score[1] > score[0] )
		std::cout << "Player O wins the tournament!\n";
	else
		std::cout << "The players have tied!\n";

	//game over
	return 0;
}
/**************************************************************
* Entry: An array
*
* Exit: none
*
* Purpose: Prepares a fresh game board
*
***************************************************************/
void initBoard( char array[][boardSize] )
{
	//rows
	for(int i = 0; i < boardSize; i++)
	{
		//columns
		for(int j = 0; j < boardSize; j++)
		{
			array[i][j] = '.';
		}
	}
}

/**************************************************************
* Entry: An array and an int for the size of the array
*
* Exit: none
*
* Purpose: draws the current state of the board
***************************************************************/
void drawBoard( char array[][boardSize], int boardSize)
{
	// print column coordinates
	std::cout << "\n  0  1  2\n";

	//rows
	for(int i = 0; i < boardSize; i++)
	{
		//print row coordinates
		std::cout << i << " ";

		//columns
		for(int j = 0; j < boardSize; j++)
		{
			//print square with spaces
			std::cout << array[i][j] << "  ";
		}
	
		//space for next row
		std::cout << std::endl;
	}

	//some space underneath
	std::cout << std::endl;
}

/**************************************************************
* Entry: An array and an int for the size of the array and the player
*
* Exit: none
*
* Purpose: gets a square form the player, checks if it is a valid
*		move, puts player's char in the space
*
***************************************************************/
void getMove( char array[][boardSize], int boardSize, char &mark)
{
	//pointer to player marker
	char *ptr = &mark;

	std::cout << "Player " << *ptr << ": please enter your move.\n";

	//movement storage initialized to too high a value
	unsigned int row = boardSize;
	unsigned int column = boardSize;

	while( (row < 0 || row > 2) || (column < 0 || column > 2) )
	{
		//get the square coordinates separated by a space
		std::cin >> row;
		std::cin >> column;
		clear_cin();
	}

	//is this square taken?
	if ( array[row][column] != '.')
	{
		std::cout << "That square is already taken.\n";
		//get move again
		getMove( array, boardSize, mark);
	}
	else
	{
		//put the players piece in the square
		array[row][column] = *ptr;

		//switch player
		if ( *ptr == 'X')
			*ptr = 'O';
		else
			*ptr = 'X';
	}


}

/**************************************************************
* Entry: An array and an int for the size of the array
*
* Exit: Returns true if the board is full
*
* Purpose: to determine if the game ends in a tie
*
***************************************************************/
bool checkFullBoard( char array[][boardSize], int boardSize)
{
	//rows
	for(int i = 0; i < boardSize; i++)
	{
		//columns
		for(int j = 0; j < boardSize; j++)
		{
			//if there is still at least one open square, there is no tie.
			if (array[i][j] == '.')
			{
				return false;
			}
		}
	}

	//if we make it past loops, there must be a full board
	return true;

}
/**************************************************************
* Entry: An array and an int for the size of the array
*
* Exit: Returns true if a player has won
*
* Purpose: to determine if a player has three in a row
*
***************************************************************/
bool checkForVictory( char array[][boardSize], int boardSize)
{
	//keep count of owned squares
	unsigned int countX = 0;
	unsigned int countO = 0;

	//first we check rows for victory
	for(int i = 0; i < boardSize; i++)
	{
		//make sure each row count is reset
		countX = 0;
		countO = 0;

		//columns
		for(int j = 0; j < boardSize; j++)
		{
			//increment which ever marker is found
			//or if empty space, forget checking the rest
			if( array[i][j] == '.')
				break;
			else if (array[i][j] == 'O')
				countO++;
			else if (array[i][j] == 'X')
				countX++;
		}
		
		//did we find a winner?
		if(countX == 3 || countO == 3)
			return true;
	}

	//if not, check columns for victory
	for(int j = 0; j < boardSize; j++)
	{
		//make sure each column count is reset
		countX = 0;
		countO = 0;	

		//loop through rows
		for(int i = 0; i < boardSize; i++)
		{
			//increment which ever marker is found
			//or if empty space, forget checking the rest
			if( array[i][j] == '.')
				break;
			else if (array[i][j] == 'O')
				countO++;
			else if (array[i][j] == 'X')
				countX++;
		}

		//did we find a winner?
		if(countX == 3 || countO == 3)
			return true;
	}

	//if not, check left to right diagonal
	//make sure count is reset outside of the loop
	countX = 0;
	countO = 0;	
	for(int i = 0; i < boardSize; i++)
	{
		//increment which ever marker is found
		//or if empty space, forget checking the rest
		if( array[i][i] == '.')
			break;
		else if (array[i][i] == 'O')
			countO++;
		else if (array[i][i] == 'X')
			countX++;
	}
	
	//did we find a winner?
	if(countX == 3 || countO == 3)
		return true;

	//if not, check last diagonal right to left
	//make sure count is reset outside of the loop
	countX = 0;
	countO = 0;	
	for(int i = 0, j = (boardSize - 1); i < boardSize; i++, j--)
	{
		//increment which ever marker is found
		//or if empty space, forget checking the rest
		if( array[i][j] == '.')
			break;
		else if (array[i][j] == 'O')
			countO++;
		else if (array[i][j] == 'X')
			countX++;
	}

	//did we find a winner?
	if(countX == 3 || countO == 3)
		return true;

	//if we found no winning conditions
	return false;

}

/**************************************************************
* Entry: none
*
* Exit: none
*
* Purpose: clears cin buffer
*
***************************************************************/
void clear_cin()
{
    std::cin.clear();
    std::cin.ignore(1000, '\n');
}
