// Quarto.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "Solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <climits>
#define human 0
#define machine 1

#define mm 0
#define aB 1

int main() {
	State match;
	cout << "Welcome to Quarto!!" << endl;

	cout << "Which algorithm do you wish to use? [0-Minimax, 1-AlfaBeta] " << endl;
	int algorisme;
	cin >> algorisme;

	match.showBoard();
	cout << "Who starts the game ?[0-Human, 1-Machine]" << endl;
	int jugador;
	cin >> jugador;
	if (jugador == machine) { 
		srand(time(NULL));
		int p = rand() % 16;
		match.selectPiece(p);
	}
	jugador = (jugador + 1) % 2; 
	bool fi = false;
	while (!fi) {
		if (jugador == human) {
			cout << "You have to put this piece: " << match.getCurrentPiece().show() << endl;
			cout << "Where do you want to put it? [row]" << endl;
			int fila;
			cin >> fila;
			cout << "Where do you want to put it? [Column]" << endl;
			int columna;
			cin >> columna;
			match.positionPiece(fila, columna);
			//	cout<<string(50,'\n');
			match.showBoard();

			Solution s = Solution(match);

			if (s.heuristic(match, true, 0) >= 10000 && !s.getDraw()) {
				cout << "YOU WON" << endl;
				fi = true;
			}
			else if (match.getUsedPieces() == 16 && !match.getCurrentPiece().hasProperty(Piece::EmptyPiece)) {
				fi = true;
				cout << "DRAW" << endl;
			}

		}
		else {
			cout << "Which piece do you want the openent to use?" << endl;
			match.showAvailablePieces();
			int pes;
			cin >> pes;
			match.selectPiece(pes);
			Solution Sol = Solution(match);

			if (algorisme == aB) Sol.alfaBeta(match, INT_MIN, INT_MAX, 0);
			else Sol.minimax(match, 0);
			match = Sol.getBest();

			match.showBoard();

			if (Sol.heuristic(match, true, 0) >= 10000 && !Sol.getDraw()) {
				cout << "YOU LOSE" << endl;
				fi = true;
			}
			else if (match.getUsedPieces() == 16 && !match.getCurrentPiece().hasProperty(Piece::EmptyPiece)) {
				fi = true;
				cout << "DRAW" << endl;
			}
		}
		jugador = (jugador + 1) % 2;
	}
	cout << "End of the match" << endl;
	cout << "Pres any key to end" << endl;
	string line;
	getline(cin, line);
	getline(cin, line);

}
