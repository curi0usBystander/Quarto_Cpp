#include "stdafx.h"
#ifndef PECES_H
#define PECES_H
#include <string>
#include <iostream>
#include <cctype>
#include <clocale>
using namespace std;
class Peces {
public:
	enum Property
	{
		Color,
		Size,
		Top,
		Form,
		EmptyPiece
	};
	Peces();
	Peces(bool, bool, bool, bool);
	Peces(const Peces&);
	//Peces(Peces p);
	bool esGran();
	bool esVermell();
	bool esForadat();
	bool esRodo();
	bool hasProperty(Property p);
	bool comparteixenCaract(const Peces& p);
	Peces& operator=(const Peces& p);

	bool esPeca();//indica si hi ha una peca
	string mostrar();

private:
	string drawPiece();
	bool big;
	bool red;
	bool hollow; //* te forat
	bool circular; //()[]
	bool NotEmpty; // Empty Piece
	string peca;
};

#endif

