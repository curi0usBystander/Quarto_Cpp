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

int parseInput(string msg)
{ 
	int input;
	cin >> input;
	while (/*!(cin >> pes)*/cin.fail())
	{
		std::cout  << msg << endl;
		cin.clear(); // reset failbit
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> input;
	}
	return input;
}
int main() {
	State match;
	std::cout << "Welcome to Quarto!!" << endl;
	
	int algorithm;
	do {
		std::cout << "Which algorithm do you wish to use? [0-Minimax, 1-AlfaBeta] " << endl;
		algorithm = parseInput("[Wrong Input] Which algorithm do you wish to use? [0-Minimax, 1-AlfaBeta]");
	} while (algorithm < 0 || algorithm > 1);
	match.showBoard();

	int player;
	do {
		std::cout << "Who starts the game ?[0-Human, 1-Machine]" << endl;
		player = parseInput("[Wrong Input] Who starts the game ?[0-Human, 1-Machine]");
	} while (player < 0 || player > 1);
	if (player == machine) { 
		srand(time(NULL));
		int p = rand() % 16;
		match.selectPiece(p);
	}
	player = (player + 1) % 2; 
	bool end = false;
	while (!end) {
		if (player == human) {
			std::cout << "You have to put this piece: " << match.getCurrentPiece().show() << endl;
			
			int row, column;
			do {
				std::cout << "Where do you want to put it? [row]" << endl;
				row = parseInput("[Wrong Input] Which row do you want to use?");
				std::cout << "Where do you want to put it? [column]" << endl;
				column = parseInput("[Wrong Input] Which column do you want to use?");
				if (match.occupied(row, column))
					std::cout << "[Wrong Input]";
			} while (match.occupied(row, column));
			match.positionPiece(row, column);
			match.showBoard();

			Solution s = Solution(match);

			if (s.heuristic(match, true, 0) >= 10000 && !s.getDraw()) {
				std::cout << "YOU WON" << endl;
				end = true;
			}
			else if (match.getUsedPieces() == 16 && !match.getCurrentPiece().hasProperty(Piece::EmptyPiece)) {
				end = true;
				std::cout << "DRAW" << endl;
			}

		}
		else {
			std::cout << "Which piece do you want the openent to use?" << endl;
			match.showAvailablePieces();
			int pes;
			cin >> pes;
			while (/*!(cin >> pes)*/cin.fail() || !match.isPieceAvailable(pes)) 
			{
				
				//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "[Wrong Input] Which piece do you want the openent to use?" << endl;
				cin.clear(); // reset failbit
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> pes;
			}
			match.selectPiece(pes);
			Solution Sol = Solution(match);

			if (algorithm == aB) Sol.alfaBeta(match, INT_MIN, INT_MAX, 0);
			else Sol.minimax(match, 0);
			match = Sol.getBest();

			match.showBoard();

			if (Sol.heuristic(match, true, 0) >= 10000 && !Sol.getDraw()) {
				std::cout << "YOU LOSE" << endl;
				end = true;
			}
			else if (match.getUsedPieces() == 16 && !match.getCurrentPiece().hasProperty(Piece::EmptyPiece)) {
				end = true;
				std::cout << "DRAW" << endl;
			}
		}
		player = (player + 1) % 2;
	}
	std::cout << "End of the match" << endl;
	std::cout << "Pres any key to end" << endl;
	string line;
	getline(cin, line);
	getline(cin, line);

}
