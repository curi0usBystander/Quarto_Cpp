#pragma once
#ifndef SOLUCIO_H
#define SOLUCIO_H
#include "Estat.h"
#include <climits>

#define gran 0;
#define vermell 1;
#define foradat 2;
#define rodo 3;

class Solucio {
public:
	Solucio(const Estat &);
	int minimax(const Estat&, int);
	int alfaBeta(const Estat&, int, int, int);
	int heuristica(Estat, bool, int);
	Estat getMillor();
	bool obtEmpat();

private:
	bool empat;
	Estat e;
	Estat millorE;
	vector<Estat> generarFills(const Estat&);
	bool haGuanyat(const vector<int>&);
	int comparteixenCarac(const Estat&, int, int, int, int, vector<int>&);

};

#endif

