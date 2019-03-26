#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//Niall Swan 40207307

//board squares
enum { NOUGHTS, CROSSES, BORDER, EMPTY };

//directions
const int directions[4] = {1, 5, 4, 6};

//playable board locations
const int ConvertTo25[9] = 
{	
	6,7,8,
	11,12,13,
	16,17,18
	
};

//get number for direction
int GetNumForDir(int startSq, const int dir, const int *board, const int us) 
{
	int found = 0;
	
	//while it has not hit the border / if it hits the border stop
	while(board[startSq] != BORDER) 
	{	//
		if(board[startSq] != us) 
		{	
			break;
		}
		found++;	
		startSq += dir;
	}	
	return found;
}

//find 3 in a row
int FindThreeInARow(const int *board, const int ourindex, const int us) 
{

	int DirIndex = 0;
	
	//direction
	int Dir = 0;
	
	//count of how many in a row
	int threeCount = 1;
	
	//for each direction check if there is 3 in a row
	for(DirIndex = 0; DirIndex < 4; ++DirIndex) 
	{
		Dir = directions[DirIndex];
		
		threeCount += GetNumForDir(ourindex + Dir, Dir, board, us);
		threeCount += GetNumForDir(ourindex + Dir * -1, Dir * -1, board, us);
		
		//if three found break
		if(threeCount == 3) 
		{
			break;
		}
		
		//reset count to 1
		threeCount = 1;
	}
	
	return threeCount;
}


//set up the board
void InitialiseBoard(int *board) 
{
	int index = 0;
	
	for(index = 0; index < 25; ++index) 
	{		
		board[index] = BORDER;
	}
	
	//get playable locations
	for(index = 0; index < 9; ++index) 
	{
		
		board[ConvertTo25[index]] = EMPTY;
	}	
}

//print the board
void PrintBoard(const int *board) 
{
	int index = 0;
	char pieces[] = "OX|-";
	printf("\n\nBoard:\n\n");
	
	//print squares
	for(index = 0; index < 9; ++index) 
	{
		
		//create a new line after every 3 squares
		if(index!=0 && index%3==0) 
		{
			
			printf("\n\n");
		}
		
		printf("%4c",pieces[board[ConvertTo25[index]]]);
	}
	
	printf("\n");
}

//check to see if board has any empty spaces
int HasEmpty(const int *board) 
{
	int index = 0;
	
	for(index = 0; index < 9; ++index) 
	{
		if( board[ConvertTo25[index]] == EMPTY) return 1;
	}
	return 0;
}


//make move
void MakeMove(int *board, const int sq, const side) 
{
	//place noughts or cross on location
	board[sq] = side;
}


//players move
int GetPlayerMove(const int *board) 
{	
	//user inserted move
	char userInput[4];
	
	int moveOk = 0;
	int move = -1;
	
	//check to see if legal move, if it is change moveOk and return move
	while (moveOk == 0) 
	{
	
		//prompt
		printf("Please enter a move from 1 to 9:");		
		
		//get input
		fgets(userInput, 3, stdin);
		
		//flush removes remaining values if player enters a long string 
		fflush(stdin);
		
		//invalid input
		if(strlen(userInput) != 2) 
		{
			printf("Please insert a number\n");
			continue;			
		}
		
		//if input is not a number error
		if( sscanf(userInput, "%d", &move) != 1) 
		{
			move = -1;
			printf("Please insert a number\n");
			continue;
		}
		
		//if move is not between 1 and 9 error
		if( move < 1 || move > 9) 
		{
			move = -1;
			printf("Please insert a number between 1 and 9\n");
			continue;
		}
		
		move--; //zero indexing
		
		//is the board empty at selected position
		if( board[ConvertTo25[move]]!=EMPTY) 
		{
			move=-1;
			printf("Square not available\n");
			continue;
		}
		
		//if pass move is ok
		moveOk = 1;
	}
	
	//print move
	printf("Making Move...%d\n",(move+1));
	
	//return move
	return ConvertTo25[move];
}

//AI move
int GetCompMove(const int *board)
{
	int index = 0;
	int numFree = 0;
	int availableMoves[9];
	int randMove = 0;
	
	//for all the playable spaces on the board
	for(index = 0; index < 9; ++index)
	{
		//find empty locations on the board
		if(board[ConvertTo25[index]] == EMPTY)
		{
			//add to available moves
			availableMoves[++numFree] = ConvertTo25[index];
		};
	}
	
	//get random move from available moves
	randMove = (rand() % numFree);
	
	//return random move
	return availableMoves[randMove];
}

//run the game
void RunGame() {

	int GameOver = 0;
	int Side = NOUGHTS;
	int LastMoveMade = 0;
	
	//declare board
	int board[25];
	//initialise board
	InitialiseBoard(&board[0]);
	//print board
	PrintBoard(&board[0]);
	
		//while game is not over
		while(!GameOver) 
		{
			//noughts turn
			if(Side==NOUGHTS) 
			{		
				//get player 1 move
				LastMoveMade = GetPlayerMove(&board[0]);
				//make player 1 move
				MakeMove(&board[0], LastMoveMade, Side);
				//change sides
				Side = CROSSES;
				//print board
				PrintBoard(&board[0]);
			} 
			//crosses turn
			else 
			{
				//get player 2 move
				LastMoveMade = GetPlayerMove(&board[0]);
				//make player 2 move
				MakeMove(&board[0], LastMoveMade, Side);
				//change sides
				Side = NOUGHTS;
				//print board
				PrintBoard(&board[0]);
			}
			
			//if three in a row is found game over
			if(FindThreeInARow(board, LastMoveMade, Side^1) == 3)
			{
				//game over
				printf("Game over!\n");
				GameOver = 1;
				
				//if noughts wins 
				if(Side==NOUGHTS) 
				{
					printf("CROSSES Wins!\n");
				} 
				//if crosses wins
				else 
				{
					printf("NOUGHTS Wins!\n");
				}
			}
			
			//draw
			if(!HasEmpty(board))
			{
				printf("Game over! \n");
				GameOver = 1;
				printf("It's a draw\n");
			}
		}	
					
}

//run the game
void RunGameVsAI() {

	int GameOver = 0;
	int Side = NOUGHTS;
	int LastMoveMade = 0;
	
	//declare board
	int board[25];
	//initialise board
	InitialiseBoard(&board[0]);
	//print board
	PrintBoard(&board[0]);
	
		//while game is not over
		while(!GameOver) 
		{
			//noughts turn
			if(Side==NOUGHTS) 
			{		
				//get player 1 move
				LastMoveMade = GetPlayerMove(&board[0]);
				//make player 1 mover
				MakeMove(&board[0], LastMoveMade, Side);
				//change sides
				Side = CROSSES;
				//print board
				PrintBoard(&board[0]);
			} 
			//crosses turn
			else 
			{
				//get player 2 move
				LastMoveMade = GetCompMove(&board[0]);
				//make player 2 move
				MakeMove(&board[0], LastMoveMade, Side);
				//change sides
				Side = NOUGHTS;
				//print board
				PrintBoard(&board[0]);
			}
			
			//if three in a row is found game over
			if(FindThreeInARow(board, LastMoveMade, Side^1) == 3)
			{
				//game over
				printf("Game over!\n");
				GameOver = 1;
				
				//if noughts wins 
				if(Side==NOUGHTS) 
				{
					printf("CROSSES Wins!\n");
				} 
				//if crosses wins
				else 
				{
					printf("NOUGHTS Wins!\n");
				}
			}
			
			//draw
			if(!HasEmpty(board))
			{
				printf("Game over! \n");
				GameOver = 1;
				printf("It's a draw\n");
			}
		}	
					
}

int main() {		
	
	srand(time(NULL));
	
	char selection;
	int selectionMade = 0;
		
	//prompt
	printf("Press 1 to play against a player\n");
	printf("Press 2 to play against AI\n");	
		
	//check to see if legal move, if it is change moveOk and return move
	while (selectionMade == 0) 
	{	
		scanf("%d", &selection); 
				
		selectionMade = 1;
	}
	
	if(selectionMade = 1)
	{
		if(selection = 1)
		{
			RunGame();
		}
		else if(selection = 2)
		{
			RunGameVsAI();
		}
	}
	
	return 0;
}






