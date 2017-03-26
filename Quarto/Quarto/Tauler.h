#pragma once
#ifndef TAULER_H
#define TAULER_H

#include <vector>
#include "Peces.h"
#include <iostream>
#include <cstdlib>
using namespace std;

class Tauler {
public:
	Tauler();
	void setTaulerPeca(int, int, Peces);
	void removeTaulerPeca(int, int);
	void mostrar();
	Peces getPeca(int, int)const;
private:
	vector<vector<Peces> > Taula;
};

#endif
