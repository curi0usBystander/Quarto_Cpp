#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Piece.h"
#include <iostream>
#include <cstdlib>
using namespace std;

class Board {
public:
	Board();
	void setPiece(int, int, Piece);
	void removePiece(int, int);
	void show();
	Piece getPiece(int, int)const;
private:
	vector<vector<Piece> > gameBoard;
};

#endif
