// Quarto.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "Solucio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <climits>
#define Huma 0
#define maquina 1

#define mm 0
#define aB 1

int main() {
	/*Tauler t;
	Peces p=Peces(false,false,true,false);
	cout<<p.mostrar()<<endl;
	t.setTaulerPeca(2,1,Peces(false,false,false,false));//filaxcolumna
	t.mostrar();*/
	//cout<<string(50,'\n');
	Estat partida;
	cout << "Benvingut al Quarto!!" << endl;

	cout << "Quin algorisme desitges utilitzar? [0-Minimax, 1-AlfaBeta] " << endl;
	int algorisme;
	cin >> algorisme;

	partida.mostrarTaula();
	cout << "Qui iniciara el joc?[0-Huma, 1-Maquina]" << endl;
	int jugador;
	cin >> jugador;
	if (jugador == maquina) { //aixo es maquina si funciona al reves del qeu entenc
		srand(time(NULL));
		int p = rand() % 16;
		partida.pecaAmoure(p);
	}
	jugador = (jugador + 1) % 2; //sobra si el joc funciona alreves (per la jugada inicial)
	bool fi = false;
	while (!fi) {
		if (jugador == Huma) {
			cout << "Has de posar la seguent Peca: " << partida.obtPeca().mostrar() << endl;
			cout << "On desitjes posar-la? [Fila]" << endl;
			int fila;
			cin >> fila;
			cout << "On desitjes posar-la?[Columna]" << endl;
			int columna;
			cin >> columna;
			partida.posicioPeca(fila, columna);
			//	cout<<string(50,'\n');
			partida.mostrarTaula();

			//evalua si has guanyat
			Solucio s = Solucio(partida);

			if (s.heuristica(partida, true, 0) >= 10000 && !s.obtEmpat()) {
				cout << "has guanyat!!!!!!" << endl;
				fi = true;
			}
			else if (partida.obtPecesCons() == 16 && !partida.obtPeca().esPeca()) {
				fi = true;
				cout << "EMPAT" << endl;
			}
			//fi evalua

		}
		else {
			cout << "Quina peca desitges que el contrincant posi?" << endl;
			partida.pecesDisponibles();
			int pes;
			cin >> pes;
			partida.pecaAmoure(pes);
			Solucio Sol = Solucio(partida);
			//int puntuacio;
			if (algorisme == aB) /*puntuacio=*/Sol.alfaBeta(partida, INT_MIN, INT_MAX, 0);
			else /*puntuacio=*/Sol.minimax(partida, 0);
			partida = Sol.getMillor();
			//cout<<string(50,'\n');
			partida.mostrarTaula();

			if (Sol.heuristica(partida, true, 0) >= 10000 && !Sol.obtEmpat()) {
				cout << "La maquina ha guanyat" << endl;
				fi = true;
			}
			else if (partida.obtPecesCons() == 16 && !partida.obtPeca().esPeca()) {
				fi = true;
				cout << "EMPAT" << endl;
			}
		}
		jugador = (jugador + 1) % 2;
	}
	cout << "FI de la partida" << endl;
	cout << "Prem enter per a acabar" << endl;
	string line;
	getline(cin, line);
	getline(cin, line);
	//string s;
	//cin>>s;



}
