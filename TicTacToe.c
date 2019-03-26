#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//Niall Swan 40207307

//board squares
const NOUGHTS = 1;
const CROSSES = 2;
const BORDER = 3;
const EMPTY = 0;

//playable board locations
const int ConvertTo25[9] = {	
	6,7,8
	11,12,13
	16,17,18	
}

//set up the board
void InitialiseBoard(int *board)
{
	int index= 0;
	
	for(index = 0; index < 25; index++)
	{
		board[index] == BORDER;
	}
	
	//get playable locations
		for(index = 0; index < 9; index++)
	{
		board[ConvertTo25[index]] == EMPTY;
	}
}

void PrintBoard(const int *board)
{
	int index = 0;
	printf("\nBoard:\n);
	
	//print squares
	for(index= 0; index < 25; index++)
	{
		//create a new line after every 5 squares
		if(index!=0 && index%5==0)
		{
			printf("%4d", board[index]);
		}
	}
	
	printf("\n");
}

void RunGame()
{
	//declare board
	int board[25];
	
	//initialise board
	InitialiseBoard(&board[0]);
		
	//print board
	PrintBoard(&board[0]);
}
int main()
{
	RunGame();
	
	return 0;
}