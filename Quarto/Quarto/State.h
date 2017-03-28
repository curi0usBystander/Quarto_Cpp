#ifndef STATE_H
#define STATE_H
#include "Board.h"
#include <iomanip>

class State {
public:
	State();
	State(const State&);
	//Tauler obtTauler();
	void showAvailablePieces();
	void showBoard();
	void selectPiece(int);
	void positionPiece(int, int);
	bool isPieceAvailable(int);
	Piece getPiece(int, int)const;
	Piece getFromPieceList(int);
	bool occupied(int, int);
	int getUsedPieces()const;
	State& operator=(const State&);

	Piece getCurrentPiece();
private:
	Board board;
	vector<Piece> availablePieces;
	Piece piece;//current piece
	vector<Piece> initializePieces();
	int usedPieces;

};

#endif

