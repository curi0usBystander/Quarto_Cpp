#include "stdafx.h"
#include "Estat.h"

Estat::Estat() {
	//Taula ja queda inicialitzada taula=Taule();
	pecesdisponibles = inicialitzarPeces();
	pecesConsumides = 0;
}

Estat::Estat(const Estat& e) {
	taula = e.taula;
	pecesdisponibles = e.pecesdisponibles;
	peca = e.peca;
	pecesConsumides = e.pecesConsumides;
}

void Estat::pecesDisponibles() {
	for (unsigned int i = 0; i<pecesdisponibles.size(); i++) {
		if (pecesdisponibles[i].esPeca()) cout << setfill('0') << std::setw(2) << i << ": " << pecesdisponibles[i].mostrar() << endl;
	}
}

void Estat::mostrarTaula() {
	taula.mostrar();
}

void Estat::pecaAmoure(int i) {
	while (i>16) {
		cout << "No existeix tal peca trian un aaltra" << endl;
		cin >> i;
	}
	if (pecesdisponibles[i].esPeca()) {
		peca = pecesdisponibles[i];
		pecesdisponibles[i] = Peces();
		pecesConsumides++;
	}
	else {
		cout << "No existeix tal peca, vols tornar-ho a provar-->Introdueix un idex valid" << endl;
		cin >> i;
		pecaAmoure(i);

	}
}

Peces Estat::contingut(int i, int j)const {
	return taula.getPeca(i, j);
}
bool Estat::ocupat(int i, int j) {
	if (i>3 || i<0 || j>3 || j<0) return false;//cout<<j<<" "<<i<<endl;
	return (taula.getPeca(i, j).esPeca());
}

void Estat::posicioPeca(int i, int j) {
	if (!taula.getPeca(i, j).esPeca()) {
		taula.setTaulerPeca(i, j, peca);
		peca = Peces();
	}
	else {
		cout << "Hi ha una peca, posicio correcte¿[Y]" << endl;
		string s;
		cin >> s;
		if (s == "Y") {
			cout << "Index??" << endl;
			int x, y;
			cin >> x;
			cin >> y;
			posicioPeca(x, y);
		}


	}
}

Peces Estat::obtPeca() {
	return peca;
}

Peces Estat::disponible(int i) {
	return pecesdisponibles[i];
}
vector<Peces> Estat::inicialitzarPeces() {
	vector<Peces> aux;
	//foradades
	aux.push_back(Peces(true, true, true, true));
	aux.push_back(Peces(true, true, true, false));
	aux.push_back(Peces(true, true, false, true));
	aux.push_back(Peces(true, true, false, false));
	aux.push_back(Peces(true, false, true, true));
	aux.push_back(Peces(true, false, true, false));
	aux.push_back(Peces(true, false, false, true));
	aux.push_back(Peces(true, false, false, false));

	aux.push_back(Peces(false, true, true, true));
	aux.push_back(Peces(false, true, true, false));
	aux.push_back(Peces(false, true, false, true));
	aux.push_back(Peces(false, true, false, false));
	aux.push_back(Peces(false, false, true, true));
	aux.push_back(Peces(false, false, true, false));
	aux.push_back(Peces(false, false, false, true));
	aux.push_back(Peces(false, false, false, false));

	return aux;
}

int Estat::obtPecesCons()const {
	return pecesConsumides;
}
Estat& Estat::operator=(const Estat &e) {
	if (this != &e) {
		taula = e.taula;
		pecesdisponibles = e.pecesdisponibles;
		peca = e.peca;
		pecesConsumides = e.pecesConsumides;
	}
	return *this;
}
