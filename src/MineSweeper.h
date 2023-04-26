#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <ctype.h>
#include <vector>
#include <windows.h>
#include <mmsystem.h>
#pragma comment (lib,"Winmm.lib")

#define MAX_VALUE 100

using namespace std;

class MineSweeper
{
private:
	char inputboard[MAX_VALUE][MAX_VALUE];
	char gameBoard[MAX_VALUE][MAX_VALUE];
	char answerBoard[MAX_VALUE][MAX_VALUE];
	bool loadPerfect = false;
	int row, col; //the row and column amount of gameboard
	int gameState = 0; // StandBy = 0, Playing = 1, GameOver = 2
	int bombCount = 0;
	int flagCount = 0;
	int openBlankCount = 0;
	int remainBlankCount;

public:
	MineSweeper();
	~MineSweeper();
	void Load(vector<string> inputString);
	void StartGame();
	void Print(vector<string> inputString);
	void LeftClick(vector<string> inputString);
	void RightClick(vector<string> inputString);
	void Replay();
	void Quit();
	void spaceMaker(int a, int b, int count);
};


MineSweeper::MineSweeper()
{

}

MineSweeper::~MineSweeper()
{

}

// Intent: To run command file
// Pre: 2D vector
// Post: void
void MineSweeper::Load(vector<string> inputString)
{
	if (gameState == 0) // standby
	{
		string command = inputString[2];
		char board[MAX_VALUE][MAX_VALUE];

		// Load board file
		if (command == "BoardFile")
		{
			string filePath = inputString[3];

			//int row, col;
			ifstream input;

			input.open(filePath);

			input >> row >> col;

			//read the file
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					input >> board[i][j];
				}
			}
		}
		else if (command == "RandomCount" || command == "RandomRate")
		{
			this->row = atoi(inputString[3].c_str());
			this->col = atoi(inputString[4].c_str());
			double appointMine = stod(inputString[5]);
			if (this->row == 0 || this->col == 0 || appointMine == 0) {
				cout << "<" << inputString[0] << "> : Failed" << endl;
				return;
			}
			int mineRand[2]; //隨機炸彈的位置

			//初始
			for (int i = 0; i < this->row; i++)
			{
				for (int j = 0; j < this->col; j++)
				{
					board[i][j] = 'O';
				}
			}

			//計算炸彈數
			if (command == "RandomRate")
			{
				appointMine = appointMine * this->row * this->col;
			}
			//隨機產生炸彈
			for (int i = 0; i < (int)appointMine; i++)
			{
				int tempY = rand() % this->row;
				int tempX = rand() % this->col;
				if (board[tempY][tempX] == 'X')
				{
					i--;
				}
				else
				{
					board[tempY][tempX] = 'X';
				}
			}
		}

		//產生answer board
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (board[i][j] == 'O')
				{
					int count = 0;
					for (int m = i - 1; m <= i + 1; m++) //row
					{
						for (int n = j - 1; n <= j + 1; n++) //col
						{
							if (board[m][n] == 'X' && m >= 0 && m < this->row && n >= 0 && n < this->col)
							{
								count++;
							}
						}
					}
					answerBoard[i][j] = '0' + count;
				}
				else if (board[i][j] == 'X')
				{
					answerBoard[i][j] = 'X';
					bombCount++;
				}
			}
		}

		//產生game board
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				gameBoard[i][j] = '#';
			}
		}

		this->loadPerfect = true;
		cout << "<" << inputString[0] << "> : Success" << endl;
	}
	else
	{
		cout << "<" << inputString[0] << "> : Failed" << endl;
	}
}

// Intent: To run command file
// Pre: void
// Post: void
void MineSweeper::StartGame()
{
	if (gameState == 0 && this->loadPerfect)
	{
		this->gameState = 1; //變成遊玩狀態
		cout << "<StartGame> : Success" << endl;
	}
	else
	{
		cout << "<StartGame> : Failed" << endl;
	}
}

// Intent: To run command file
// Pre: 2D vector
// Post: void
void MineSweeper::Print(vector<string> inputString)
{
	string infor = inputString[2];

	if (infor == "GameBoard")
	{
		cout << "<Print " << infor << "> : " << endl;
		for (int i = 0; i < this->row; i++)
		{
			for (int j = 0; j < this->col; j++)
			{
				cout << gameBoard[i][j] << " ";
			}
			cout << endl;
		}
	}
	else if (infor == "GameState")
	{
		switch (this->gameState)
		{
		case 0:

			cout << "<Print " << infor << "> : " << "Standby" << endl;
			break;
		case 1:
			cout << "<Print " << infor << "> : " << "Playing" << endl;
			break;
		case 2:
			cout << "<Print " << infor << "> : " << "GameOver" << endl;
			break;
		}
	}
	else if (infor == "GameAnswer")
	{
		cout << "<Print " << infor << "> : " << endl;

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				cout << answerBoard[i][j] << " ";
			}
			cout << endl;

		}
	}
	else if (infor == "BombCount")
	{
		cout << "<Print " << infor << "> : " << bombCount << endl;
	}
	else if (infor == "FlagCount")
	{
		cout << "<Print " << infor << "> : " << flagCount << endl;
	}
	else if (infor == "OpenBlankCount")
	{
		cout << "<Print " << infor << "> : " << openBlankCount << endl;
	}
	else if (infor == "RemainBlankCount")  //未改
	{
		cout << "<Print " << infor << "> : " << remainBlankCount << endl;
	}
}

// Intent: To run command file
// Pre: 2D vector
// Post: void
void MineSweeper::LeftClick(vector<string> inputString)
{
	if (this->gameState == 1) // Playing
	{
		int input1 = stoi(inputString[2]); // row
		int input2 = stoi(inputString[3]); // col

		// Judge if input is out of range, if there is '?', 'f', and gameBoard is number
		if (input1 > this->row - 1 || input2 > this->col - 1 || input1 < 0 || input2 < 0 || gameBoard[input1][input2] == 'f' || isdigit(gameBoard[input1][input2]))
		{
			cout << "<" << inputString[0] << "> : Failed" << endl;
			return;
		}

		// Judge if there is a bomb in the answer position, lose
		if (answerBoard[input1][input2] == 'X')
		{
			cout << "<" << inputString[0] << "> : Success" << endl;
			cout << "You lose the game" << endl;
			this->gameState = 2;
			return;
		}
		// If it is a space, open the space
		else
		{
			spaceMaker(input1, input2, 0);
		}

		cout << "<" << inputString[0] << "> : Success" << endl;

		// Calculate the number of rest grids
		int countRemainBlank = 0;

		for (int i = 0; i < this->row; i++)
		{
			for (int j = 0; j < this->col; j++)
			{
				// not a bomb but a number
				if (answerBoard[i][j] != 'X' && !isdigit(gameBoard[i][j]))
				{
					countRemainBlank++;
				}
			}
		}

		this->remainBlankCount = countRemainBlank;

		// Finished
		if (this->remainBlankCount == 0)
		{
			cout << "You win the game" << endl;
			this->gameState = 2;
		}
	}
	else
	{
		cout << "<" << inputString[0] << "> : Failed" << endl;
	}
}

// Intent: space maker
// Pre: Three int
// Post: void
void MineSweeper::spaceMaker(int intput1, int intput2, int count)
{
	gameBoard[intput1][intput2] = answerBoard[intput1][intput2]; // open grid
	openBlankCount += 1; // Open the number of grids + 1

	// first call
	if (answerBoard[intput1][intput2] != '0' && count == 0)
	{
		return;
	}
	else
	{
		for (int i = intput1 - 1; i <= intput1 + 1; i++)
		{
			for (int j = intput2 - 1; j <= intput2 + 1; j++)
			{
				// Out of range
				if (i < 0 || i >= row || j < 0 || j >= col)
				{
					continue;
				}

				// open unopened
				if (gameBoard[i][j] == '#')
				{
					// Recursion 
					if (answerBoard[i][j] == '0')
					{
						spaceMaker(i, j, count + 1);
					}
					// not 0 just open
					else if (answerBoard[i][j] != 'X')
					{
						gameBoard[i][j] = answerBoard[i][j];
						openBlankCount += 1;
					}
				}
			}
		}
	}
}

// Intent: RightClick(flag)
// Pre: vector
// Post: void
void MineSweeper::RightClick(vector<string> inputString)
{
	int input1 = stoi(inputString[2]), input2 = stoi(inputString[3]);

	// Judge the symbols of game Board[input1][input2] and make corresponding actions
	if (gameState == 1 && !isdigit(gameBoard[input1][input2])) // playing && if gameBoard is 0 ~ 9
	{
		// 'f' next is '?'
		if (gameBoard[input1][input2] == 'f')
		{
			gameBoard[input1][input2] = '?';
			flagCount -= 1;
		}
		// '?' next is '#'
		else if (gameBoard[input1][input2] == '?')
		{
			gameBoard[input1][input2] = '#';
		}
		// '#' next is 'f'
		else if (gameBoard[input1][input2] == '#')
		{
			gameBoard[input1][input2] = 'f';
			flagCount += 1;
		}

		cout << "<" << inputString[0] << "> : Success" << endl;
	}
	else
	{
		cout << "<" << inputString[0] << "> : Failed" << endl;
	}
}

// Intent: Replay
// Pre: void
// Post: void
void MineSweeper::Replay()
{
	// GameOver
	if (gameState == 2)
	{
		this->inputboard[MAX_VALUE][MAX_VALUE] = { 0 };
		this->gameBoard[MAX_VALUE][MAX_VALUE] = { 0 };
		this->answerBoard[MAX_VALUE][MAX_VALUE] = { 0 };
		this->loadPerfect = false;
		this->row = 0;
		this->col = 0;
		this->gameState = 0;
		this->bombCount = 0;
		this->flagCount = 0;
		this->openBlankCount = 0;
		cout << "<Replay> : Success" << endl;
	}
	else
	{
		cout << "<Replay> : Failed" << endl;
	}
}

// Intent: Quit
// Pre: void
// Post: void
void MineSweeper::Quit()
{
	if (gameState == 2) // playing
	{
		cout << "<Quit> : Success" << endl;
		PlaySound(NULL, NULL, SND_ASYNC | SND_PURGE);
		exit(0);
	}
	else
	{
		cout << "<Quit> : Failed" << endl;
	}
}
