#include "stdafx.h"
#ifndef Piece_H
#define Piece_H
#include <string>
#include <iostream>
#include <cctype>
#include <clocale>
using namespace std;
class Piece {
public:
	enum Property
	{
		Color,
		Size,
		Top,
		Form,
		EmptyPiece
	};
	Piece();
	Piece(bool, bool, bool, bool);
	Piece(const Piece&);
	bool hasProperty(Property p);
	Piece& operator=(const Piece& p);
	string show();

private:
	string drawPiece();
	bool big;
	bool red;
	bool hollow; //* has a hollow top
	bool circular; //()[]
	bool NotEmpty; // Empty Piece
	string representation;
};

#endif

