/************************************************************************************************************
Purpose: This program is a simplified version of the game that is known as a minesweeper in the game history.
Author: Taner Giray Sonmez
Date: 10/10/2021
*************************************************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include "randgen.h"
#include <iomanip> // for using setw()


using namespace std;

/***************************
This function prints matrix.
****************************/
void matrixPrinter(const vector<vector<char>> & matrixForPrinting);

/***********************************************************************************
This function takes a specific cell and uncompleted matrix(as a reference parameter)
and fills necessary parts with the numbers of adjacent bombs.
************************************************************************************/
void adjacentNumbersCalculator(vector<vector<char>> & matrixForCalculating,int rowNum,int colNum);

/****************************************************************
This function creates matrix for the debugging purposes,
by explicitly indicating each line (for example in B 2 0... format).
*****************************************************************/
vector<vector<char>> debugMatrixCreator(int row,int column,int bombs);

/********************************************
This function runs when option 1 is selected.
*********************************************/
void optionOne(const vector<vector<char>> & debugMatrix,int row,int col,vector<vector<char>> showingMatrix);

/********************************************
This function runs when option 2 is selected.
*********************************************/
void optionTwo(const vector<vector<char>> & debugMatrix,int row,int col,vector<vector<char>> & showingMatrix,int & gameStatus,const vector<vector<char>> & winnerOne);

/*******************************************************************************
This function provides the vector that the user needs to create to win the game.
********************************************************************************/
vector<vector<char>> winningVector(vector<vector<char>> debugMatrix,int row,int col);


int main(){
	cout << "Give the dimensions of the matrix: ";
	int row,column;
	cin >> row >> column;
	int bombs;
	cout << "How many bombs: ";
	cin >>bombs;
	while (!(bombs >0 && bombs<row*column))//input check for number of bombs
	{
		if (!(bombs<row*column))
		{
			cout << "The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
			cin >>bombs;
		}
		else if (!(bombs >0))
		{
			cout << "The number of bombs could not be less than one. Please give the number of bombs again: ";
			cin >>bombs;
		}
	}
	vector<vector<char>> gameMatrix(row,vector<char>(column,'X'));//This is a matrix for the game (i.e in X X X... format).
	matrixPrinter(gameMatrix);
	cout << endl;
	vector<vector<char>> debugMatrix = debugMatrixCreator(row,column,bombs);
	vector<vector<char>> winnerVectorForGame = winningVector(debugMatrix,row,column);
	//matrixPrinter(debugMatrix); I used that matrix while i was debugging.
	cout << endl;
	int gameStatus=1;//When it becomes 0, game will be over.
	while (gameStatus!=0)
	{
		cout << "Press:"<<endl;
		cout << "1. If you want to find out the surrounding of a cell"<<endl;
		cout << "2. If you want to open the cell"<<endl;
		cout<< "3. If you want to exit."<<endl;
		string optionSelect;
		cin >>optionSelect;
		while (!(optionSelect =="1" || optionSelect=="2" || optionSelect =="3"))
		{
			cout << "Your input is wrong. Please select one of the options: 1, 2 or 3." << endl;
			cin>>optionSelect;
		}
		if (optionSelect=="1")
		{
			optionOne(debugMatrix,row,column,gameMatrix);
		}
		else if (optionSelect=="2")
		{
			optionTwo(debugMatrix,row,column,gameMatrix,gameStatus,winnerVectorForGame);
		}
		else if (optionSelect=="3")
		{
			cout << "Program exiting ..." << endl;
			gameStatus=0;
		}
		cout <<endl;
	}
return 0;
}

void matrixPrinter(const vector<vector<char>> & matrixForPrinting){
	for (int k = 0; k < matrixForPrinting.size(); k++)
	{
		for (int j = 0; j < matrixForPrinting[0].size(); j++)
		{
			cout << setw(4) << matrixForPrinting[k][j];
		}
		cout << endl;
	}
}

vector<vector<char>> debugMatrixCreator(int row,int column,int bombs){
	vector<vector<char>> debugMatrix(row,vector<char>(column,'X'));
	RandGen rand;
	/********************************************************************************
	Bomb Counter:
	The variable I create to add as many bombs as the user wants, increases in value
	for each correctly placed bomb(only one bomb for one cell)
	until it reaches the desired number of bombs.
	*********************************************************************************/
	int bombCounter=0;
	while (bombCounter!=bombs)
	{
		int bombRowNum = rand.RandInt(0,row-1);
		int bombColNum= rand.RandInt(0,column-1);
		if (debugMatrix[bombRowNum][bombColNum] != 'B')
		{
			debugMatrix[bombRowNum][bombColNum] = 'B';
			bombCounter++;
		}
	}
	for (int k = 0; k < debugMatrix.size(); k++)
	{
		for (int j = 0; j < debugMatrix[0].size(); j++)
		{
			adjacentNumbersCalculator(debugMatrix,k,j);
		}
	}
	return debugMatrix;
}


void adjacentNumbersCalculator(vector<vector<char>> & matrixForCalculating,int rowNum,int colNum){
	char numbersOfAdjacent='0';//variable that holds the number of neighboring cells contain mines.
	if (matrixForCalculating[rowNum][colNum] != 'B')
	{
		if (rowNum-1>=0 && matrixForCalculating[rowNum-1][colNum]=='B')//for upper side
		{
			numbersOfAdjacent++;
		}
		if (rowNum+1<=matrixForCalculating.size()-1 && matrixForCalculating[rowNum+1][colNum]=='B')//for lower side
		{
			numbersOfAdjacent++;
		}
		if (colNum+1<=matrixForCalculating[0].size()-1 && matrixForCalculating[rowNum][colNum+1]=='B' )//for right side
		{
			numbersOfAdjacent++;
		}
		if (colNum-1>=0 && matrixForCalculating[rowNum][colNum-1]=='B')//for left side
		{
			numbersOfAdjacent++;
		}
		if (rowNum-1>=0 && colNum+1<=matrixForCalculating[0].size()-1 && matrixForCalculating[rowNum-1][colNum+1]=='B' )//for upper right side
		{
			numbersOfAdjacent++;
		}
		if (rowNum-1>=0 && colNum-1>=0 && matrixForCalculating[rowNum-1][colNum-1]=='B')//for upper left side
		{
			numbersOfAdjacent++;
		}
		if (rowNum+1<=matrixForCalculating.size()-1 && colNum+1<=matrixForCalculating[0].size()-1 &&  matrixForCalculating[rowNum+1][colNum+1]=='B')//for lower right side
		{
			numbersOfAdjacent++;
		}
		if (rowNum+1<=matrixForCalculating.size()-1 && colNum-1>=0 &&  matrixForCalculating[rowNum+1][colNum-1]=='B' )//for lower left side
		{
			numbersOfAdjacent++;
		}
		matrixForCalculating[rowNum][colNum]= numbersOfAdjacent;
		}
}


void optionOne(const vector<vector<char>> & debugMatrix,int row,int col,vector<vector<char>> showingMatrix){
	cout << "Give the coordinates: ";
	int userSelectedRow,userSelectedCol;
	cin >> userSelectedRow >> userSelectedCol;
	while (!((userSelectedRow>=0 && userSelectedRow<=row-1) && (userSelectedCol>=0 && userSelectedCol<=col-1)))
	{
		cout << "It is out of range. Please give a valid coordinates: ";
		cin >> userSelectedRow >> userSelectedCol;
	}
	if (debugMatrix[userSelectedRow][userSelectedCol] != 'B')
	{
		cout << "Displaying the surrounding of (" << userSelectedRow <<","<<userSelectedCol << "):"<<endl;
		showingMatrix[userSelectedRow][userSelectedCol] = debugMatrix[userSelectedRow][userSelectedCol];
		matrixPrinter(showingMatrix);
		cout << "Around ("<< userSelectedRow <<","<<userSelectedCol << ") you have " << showingMatrix[userSelectedRow][userSelectedCol] << " bomb(s)"<<endl;
	}
	else
	{
		cout << "Displaying the surrounding of (" << userSelectedRow <<","<<userSelectedCol << "):"<<endl;
		char numbersOfAdjacent='0';
		if (userSelectedRow-1>=0 && debugMatrix[userSelectedRow-1][userSelectedCol]=='B')//for upper side
		{
			numbersOfAdjacent++;
		}
		if (userSelectedRow+1<=debugMatrix.size()-1 && debugMatrix[userSelectedRow+1][userSelectedCol]=='B')//for lower side
		{
			numbersOfAdjacent++;
		}
		if (userSelectedCol+1<=debugMatrix[0].size()-1 && debugMatrix[userSelectedRow][userSelectedCol+1]=='B' )//for right side
		{
			numbersOfAdjacent++;
		}
		if (userSelectedCol-1>=0 && debugMatrix[userSelectedRow][userSelectedCol-1]=='B')//for left side
		{
			numbersOfAdjacent++;
		}
		if (userSelectedRow-1>=0 && userSelectedCol+1<=debugMatrix[0].size()-1 && debugMatrix[userSelectedRow-1][userSelectedCol+1]=='B' )//for upper right side
		{
			numbersOfAdjacent++;
		}
		if (userSelectedRow-1>=0 && userSelectedCol-1>=0 && debugMatrix[userSelectedRow-1][userSelectedCol-1]=='B')//for upper left side
		{
			numbersOfAdjacent++;
		}
		if (userSelectedRow+1<=debugMatrix.size()-1 && userSelectedCol+1<=debugMatrix[0].size()-1 &&  debugMatrix[userSelectedRow+1][userSelectedCol+1]=='B')//for lower right side
		{
			numbersOfAdjacent++;
		}
		if (userSelectedRow+1<=debugMatrix.size()-1 && userSelectedCol-1>=0 &&  debugMatrix[userSelectedRow+1][userSelectedCol-1]=='B' )//for lower left side
		{
			numbersOfAdjacent++;
		}
		showingMatrix[userSelectedRow][userSelectedCol]= numbersOfAdjacent;
		matrixPrinter(showingMatrix);
		cout << "Around ("<< userSelectedRow <<","<<userSelectedCol << ") you have " << showingMatrix[userSelectedRow][userSelectedCol] << " bomb(s)"<<endl;
	}
}


void optionTwo(const vector<vector<char>> & debugMatrix,int row,int col,vector<vector<char>> & showingMatrix,int & gameStatus,const vector<vector<char>> & winnerOne){
	cout << "Give the coordinates: ";
	int userSelectedRow,userSelectedCol;
	cin >> userSelectedRow >> userSelectedCol;
	while (!((userSelectedRow>=0 && userSelectedRow<=row-1) && (userSelectedCol>=0 && userSelectedCol<=col-1)))
	{
		cout << "It is out of range. Please give a valid coordinates: ";
		cin >> userSelectedRow >> userSelectedCol;
	}
	cout << endl<< endl;
	if (debugMatrix[userSelectedRow][userSelectedCol] == 'B')
	{
		cout <<"Opening cell ("<< userSelectedRow <<","<<userSelectedCol << ") :"<<endl;
		cout <<endl;
		showingMatrix[userSelectedRow][userSelectedCol]= 'B';
		matrixPrinter(showingMatrix);
		cout << endl << endl;
		cout << "Unfortunately, you stepped on a mine"<<endl;
		cout <<endl;
		cout << "Arrangement of mines:"<<endl;
		cout <<endl;
		matrixPrinter(debugMatrix);
		cout << endl<< endl;
		cout << ">>>>> Game Over! <<<<<"<<endl;
		gameStatus=0;
	}
	else
	{
		cout <<endl<<endl;
		cout <<"Opening cell ("<< userSelectedRow <<","<<userSelectedCol << ") :"<<endl;
		showingMatrix[userSelectedRow][userSelectedCol]= debugMatrix[userSelectedRow][userSelectedCol];
		matrixPrinter(showingMatrix);
		cout <<endl<<endl;
		if (winnerOne==showingMatrix)
		{
			cout << "Congratulations! All the non-mined cells opened successfully"<<endl;
			cout <<endl;
			cout << "You won!"<<endl;
			cout << endl;
			cout << ">>>>> Game Over! <<<<<"<<endl;
			gameStatus=0;
		}

	}
}


vector<vector<char>> winningVector(vector<vector<char>> debugMatrix,int row,int col){
	vector<vector<char>> winnerVector(row,vector<char>(col,'X'));
	for (int k = 0; k < debugMatrix.size(); k++)
	{
		for (int j = 0; j < debugMatrix[0].size(); j++)
		{
			if (debugMatrix[k][j] !='B')
			{
				winnerVector[k][j] = debugMatrix[k][j];
			}
		}
	}
	return winnerVector;
}