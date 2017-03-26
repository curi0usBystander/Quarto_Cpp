#include "stdafx.h"
#include "State.h"

State::State() 
{
	//Taula ja queda inicialitzada taula=Taule();
	availablePieces = initializePieces();
	usedPieces = 0;
}

State::State(const State& e) {
	board = e.board;
	availablePieces = e.availablePieces;
	piece = e.piece;
	usedPieces = e.usedPieces;
}

void State::showAvailablePieces() 
{
	for (unsigned int i = 0; i<availablePieces.size(); i++) {
		if (availablePieces[i].hasProperty(Piece::EmptyPiece)) cout << setfill('0') << std::setw(2) << i << ": " << availablePieces[i].show() << endl;
	}
}

void State::showBoard() {
	board.show();
}

void State::selectPiece(int i) {
	while (i>16) {
		cout << "Piece not available, please select another one." << endl;
		cin >> i;
	}
	if (availablePieces[i].hasProperty(Piece::EmptyPiece)) {
		piece = availablePieces[i];
		availablePieces[i] = Piece();
		usedPieces++;
	}
	else {
		cout << "This piece has already been used. Please select a valid index." << endl;
		cin >> i;
		selectPiece(i);

	}
}

Piece State::getPiece(int i, int j)const 
{
	return board.getPiece(i, j);
}

bool State::occupied(int i, int j) {
	if (i>3 || i<0 || j>3 || j<0) return false;//cout<<j<<" "<<i<<endl;
	return (board.getPiece(i, j).hasProperty(Piece::EmptyPiece));
}

void State::positionPiece(int i, int j) 
{
	if (!board.getPiece(i, j).hasProperty(Piece::EmptyPiece)) {
		board.setPiece(i, j, piece);
		piece = Piece();
	}
	else {
		// TO 
		cout << "Hi ha una peca, posicio correcte¿[Y]" << endl;
		string s;
		cin >> s;
		if (s == "Y") {
			cout << "Index??" << endl;
			int x, y;
			cin >> x;
			cin >> y;
			positionPiece(x, y);
		}


	}
}

Piece State::getCurrentPiece()
{
	return piece;
}

Piece State::getFromPieceList(int i)
{
	return availablePieces[i];
}
vector<Piece> State::initializePieces() 
{
	vector<Piece> aux;
	//foradades
	aux.push_back(Piece(true, true, true, true));
	aux.push_back(Piece(true, true, true, false));
	aux.push_back(Piece(true, true, false, true));
	aux.push_back(Piece(true, true, false, false));
	aux.push_back(Piece(true, false, true, true));
	aux.push_back(Piece(true, false, true, false));
	aux.push_back(Piece(true, false, false, true));
	aux.push_back(Piece(true, false, false, false));

	aux.push_back(Piece(false, true, true, true));
	aux.push_back(Piece(false, true, true, false));
	aux.push_back(Piece(false, true, false, true));
	aux.push_back(Piece(false, true, false, false));
	aux.push_back(Piece(false, false, true, true));
	aux.push_back(Piece(false, false, true, false));
	aux.push_back(Piece(false, false, false, true));
	aux.push_back(Piece(false, false, false, false));

	return aux;
}

int State::getUsedPieces()const
{
	return usedPieces;
}
State& State::operator=(const State &e) 
{
	if (this != &e) {
		board = e.board;
		availablePieces = e.availablePieces;
		piece = e.piece;
		usedPieces = e.usedPieces;
	}
	return *this;
}
