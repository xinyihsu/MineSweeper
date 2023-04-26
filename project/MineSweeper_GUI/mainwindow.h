#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

void openBlank(int row,int col);

#define MAX_VALUE 100

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <ctype.h>
#include <vector>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_type_Play_currentIndexChanged(int index);

    void on_choose_play1_widgetRemoved(int index);

    void on_input_Board_2_textChanged(const QString &arg1);

    void on_Rows_count_6_valueChanged(int arg1);

    void on_Cows_count_6_valueChanged(int arg1);

    void on_Bomb_count_6_valueChanged(int arg1);

    void on_Rows_count_7_valueChanged(int arg1);

    void on_Cows_count_7_valueChanged(int arg1);

    void on_bomb_count_valueChanged(double arg1);

    void on_button_Load_2_clicked();

    void on_button_Load_8_clicked();

    void on_button_Load_9_clicked();

    void on_button_Print_GameBoard_clicked();

    void on_button_Print_GameAnswer_clicked();

    void on_button_Print_GameState_clicked();

    void on_button_Start_Game_clicked();

    void on_Print_gameboard_clicked();

    void on_Print_gameanswer_clicked();

    void on_Print_gamestate_clicked();

    void setButton();

    void setClick(int i,int j);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

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
    vector<string> inputString{" ", "Load", "BoardFile", "./boards/board1.txt", " ", " "};
    bool checkClicked = 1;

public:
    MineSweeper(){}
    ~MineSweeper(){}

    void setTheFinalString(){
        this->inputString[0] = "";

        for (int var = 1; var <= 5; ++var) {
            if(inputString[var]!=" ")
            {
                inputString[0]+=inputString[var];
                if(var != 5 &&inputString[var+1]!=" ")
                {
                    inputString[0]+=" ";
                }
            }
            else
            {
                break;
            }
        }
    }

    void setTypeOfIt(string input){this->inputString[1] = input;}

    void setPlayingOfIt(int index)
    {
        if(index==0)
        {
            this->inputString[2] = "BoardFile";
        }
        else if(index==1)
        {
            this->inputString[2] = "RandomRate";
        }
        else if(index==2)
        {
            this->inputString[2] = "RandomCount";
        }
    }

    void setSomething(string input){this->inputString[2] = input;}

    void setBoardName(string input){this->inputString[3] = input;}

    void setRows(int input){this->inputString[3] = to_string(input);}

    void setCols(int input){this->inputString[4] = to_string(input);}

    void setBomb(int input){this->inputString[5] = to_string(input);}

    void setBomb(double input)
    {
        string save= to_string(input);
        while(save[save.length()-1]=='0'&&save.length()>4)
        {
            save.erase(save.length() - 1, 1);
        }

        this->inputString[5] = save;
    }

    int GameState(){return this->gameState;}

    vector<string> theVauleOfInputs(){return inputString;}

    string BombCount(){return to_string(this->bombCount);}

    string FlagCount(){return to_string(this->flagCount);}

    string OpenBlankCount(){return to_string(this->openBlankCount);}

    string RemainBlankCount(){return to_string(this->remainBlankCount);}

    int Rows(){return this->row;}

    int Cols(){return this->col;}

    void changeClick()
    {
        if(checkClicked==0)
        {
            checkClicked = 1;
        }
        else if(checkClicked==1)
        {
            checkClicked = 0;
        }
    }

    int checkCilck(){return checkClicked;}

    string whatIsInside(int rowA,int colA)
    {
        string s(1,this->answerBoard[rowA][colA]);
        return s;
    }

    // Intent: To run command file
    // Pre: 2D vector
    // Post: void
    void Load(vector<string> inputString)
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

                this->remainBlankCount = row*col;
            }
            // RandomCount or RandomRate
            else if (command == "RandomCount" || command == "RandomRate")
            {
                this->row = atoi(inputString[3].c_str());
                this->col = atoi(inputString[4].c_str());
                double appointMine = stod(inputString[5]);
                int mineRand[2]; // random bomb location

                // initialization
                for (int i = 0; i < this->row; i++)
                {
                    for (int j = 0; j < this->col; j++)
                    {
                        board[i][j] = 'O';
                    }
                }

                this->remainBlankCount = row*col;

                // count bombs
                if (command == "RandomRate")
                {
                    appointMine = appointMine * this->row * this->col;
                }

                // randomly spawn bombs
                for (int i = 0; i < (int)appointMine; i++)
                {
                    int tempY = rand() % this->row;
                    int tempX = rand() % this->col;

                    // Solve the problem of repeated spawning of bombs
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

            // generate answer board
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    // no bomb
                    if (board[i][j] == 'O')
                    {
                        int count = 0;
                        for (int m = i - 1; m <= i + 1; m++) // row
                        {
                            for (int n = j - 1; n <= j + 1; n++) // col
                            {
                                // count Surrounding bomb
                                if (board[m][n] == 'X' && m >= 0 && m < this->row && n >= 0 && n < this->col)
                                {
                                    count++;
                                }
                            }
                        }
                        answerBoard[i][j] = '0' + count;
                    }
                    // answerBoard, bombCount
                    else if (board[i][j] == 'X')
                    {
                        answerBoard[i][j] = 'X';
                        bombCount++;
                    }
                }
            }

            // generate game board
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
    void StartGame()
    {
        // StandBy && finished loading
        if (gameState == 0 && this->loadPerfect)
        {
            this->gameState = 1; // playing

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
    void Print(vector<string> inputString)
    {
        string infor = inputString[2];

        // if infor is "GameBoard"
        if (infor == "GameBoard")
        {
            cout << "<Print " << infor << "> : " << endl;

            // print
            for (int i = 0; i < this->row; i++)
            {
                for (int j = 0; j < this->col; j++)
                {
                    cout << gameBoard[i][j] << " ";
                }
                cout << endl;
            }
        }
        // if infor is "GameState"
        else if (infor == "GameState")
        {
            switch (this->gameState)
            {
            case 0: // Standby
                cout << "<Print " << infor << "> : " << "Standby" << endl;
                break;
            case 1: // Playing
                cout << "<Print " << infor << "> : " << "Playing" << endl;
                break;
            case 2: // GameOver
                cout << "<Print " << infor << "> : " << "GameOver" << endl;
                break;
            }
        }
        // if infor is "GameAnswer"
        else if (infor == "GameAnswer")
        {
            cout << "<Print " << infor << "> : " << endl;

            // print
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    cout << answerBoard[i][j] << " ";
                }
                cout << endl;

            }
        }

        // if infor is "BombCount"
        else if (infor == "BombCount")
        {
            cout << "<Print " << infor << "> : " << bombCount << endl;
        }
        // if infor is "FlagCount"
        else if (infor == "FlagCount")
        {
            cout << "<Print " << infor << "> : " << flagCount << endl;
        }
        // if infor is "OpenBlankCount"
        else if (infor == "OpenBlankCount")
        {
            cout << "<Print " << infor << "> : " << openBlankCount << endl;
        }
        // if infor is "RemainBlankCount"
        else if (infor == "RemainBlankCount")  //未改
        {
            cout << "<Print " << infor << "> : " << remainBlankCount << endl;
        }
    }

    // Intent: To run command file
    // Pre: 2D vector
    // Post: void
    void LeftClick(vector<string> inputString)
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

    // Intent: RightClick(flag)
    // Pre: vector
    // Post: void
    void RightClick(vector<string> inputString)
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
    void Replay()
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
    void Quit()
    {
        if (gameState == 2) // playing
        {
            cout << "<Quit> : Success" << endl;
            exit(0);
        }
        else
        {
            cout << "<Quit> : Failed" << endl;
        }
    }

    // Intent: space maker
    // Pre: Three int
    // Post: void
    void spaceMaker(int intput1, int intput2, int count)
    {
        gameBoard[intput1][intput2] = answerBoard[intput1][intput2]; // open grid
        openBlankCount += 1; // Open the number of grids + 1

        openBlank(intput1,intput2);

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

                            openBlank(i,j);
                        }
                    }
                }
            }
        }
    }
};
