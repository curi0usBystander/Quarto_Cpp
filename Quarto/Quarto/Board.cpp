#include "stdafx.h"
#include "Board.h"

Board::Board() 
{
	gameBoard.resize(4);
	for (int i = 0; i<4; i++) {
		gameBoard[i].resize(4);
		for (int j = 0; j <4; j++)gameBoard[i][j] = Piece();
	}
}

Piece Board::getPiece(int i, int j)const 
{
	return gameBoard[i][j];
}

void Board::setPiece(int i, int j, Piece p) 
{
	gameBoard[i][j] = p;
}

void Board::removePiece(int i, int j) 
{
	gameBoard[i][j] = Piece();
}


void Board::show() 
{
	//cout<<"_____________"<<endl;
	cout << "---------------------" << endl;
	for (int i = 0; i < 4; ++i) {
		cout << "|";
		for (int j = 0; j < 4; ++j) {
			if (gameBoard[i][j].hasProperty(Piece::EmptyPiece)) {
				cout << gameBoard[i][j].show();
				if (gameBoard[i][j].hasProperty(Piece::Top))cout << "|";
				else cout << " |";
			}
			else cout << "    |";
		}
		cout << i << endl;
		//	cout<<"_____________"<<endl;
		cout << "---------------------" << endl;
	}
	cout << "  0    1    2    3" << endl;
}




