#ifndef ESTAT_H
#define ESTAT_H
#include "Tauler.h"
#include <iomanip>

class Estat {
public:
	Estat();
	Estat(const Estat&);
	//Tauler obtTauler();
	void pecesDisponibles();
	void mostrarTaula();
	void pecaAmoure(int);
	void posicioPeca(int, int);
	Peces contingut(int, int)const;
	Peces disponible(int);
	bool ocupat(int, int);
	int obtPecesCons()const;
	Estat& operator=(const Estat&);

	Peces obtPeca();
private:
	Tauler taula;
	vector<Peces> pecesdisponibles;
	Peces peca;//peca per colocar
	vector<Peces> inicialitzarPeces();
	int pecesConsumides;

};

#endif

