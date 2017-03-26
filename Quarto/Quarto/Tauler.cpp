#include "stdafx.h"
#include "Tauler.h"

Tauler::Tauler() {
	Taula.resize(4);
	for (int i = 0; i<4; i++) {
		Taula[i].resize(4);
		for (int j = 0; j<4; j++)Taula[i][j] = Peces();
	}
}

Peces Tauler::getPeca(int i, int j)const {
	return Taula[i][j];
}

void Tauler::setTaulerPeca(int i, int j, Peces p) {
	Taula[i][j] = p;
	//	cout<<"posada peca"<<p.mostrar()<<endl;
	//cout<<"posada peca"<<Taula[i][j].mostrar()<<endl;
}

void Tauler::removeTaulerPeca(int i, int j) {
	Taula[i][j] = Peces();
}


void Tauler::mostrar() {
	//cout<<"_____________"<<endl;
	cout << "---------------------" << endl;
	for (int i = 0; i<4; ++i) {
		cout << "|";
		for (int j = 0; j<4; ++j) {
			if (Taula[i][j].esPeca()) {
				cout << Taula[i][j].mostrar();
				if (Taula[i][j].esForadat())cout << "|";
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




