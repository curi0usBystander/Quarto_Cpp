#include "stdafx.h"
#include "Piece.h"

Piece::Piece() {
	big = false;
	red = false;
	hollow = false;
	circular = false;
	NotEmpty = false;
	representation = "";
}

Piece::Piece(bool g, bool b, bool f, bool r) {
	NotEmpty = true;
	big = g;
	red = b;
	hollow = f;
	circular = r;
	representation = this->drawPiece();

}

Piece::Piece(const Piece& p) {
	big = p.big;
	red = p.red;
	hollow = p.hollow;
	circular = p.circular;
	NotEmpty = p.NotEmpty;
	representation = p.representation;
}


bool Piece::hasProperty(Property p)
{
	switch (p)
	{
	case Piece::Color:
		return red;
		break;
	case Piece::Size:
		return big;
		break;
	case Piece::Top:
		return hollow;
		break;
	case Piece::Form:
		return circular;
		break;
	case Piece::EmptyPiece:
		return NotEmpty;
		break;
	default:
		break;
	}
	return false;
}



string Piece::show()
{
	return representation;
}

string Piece::drawPiece()
{
	string piece = "";
	if (hasProperty(Piece::EmptyPiece)) 
	{
		char color =  hasProperty(Piece::Color) ? 'R' : 'W';
		piece = hasProperty(Piece::Size) ? std::toupper(color) : std::tolower(color);
		piece = hasProperty(Piece::Top) ? piece + "*" : piece + "";
		piece = hasProperty(Piece::Form) ? "(" + piece + ")" : "[" + piece + "]";
	}

	return piece;
}

Piece& Piece::operator=(const Piece& p) {
	if (this != &p) {
		big = p.big;
		red = p.red;
		hollow = p.hollow;
		circular = p.circular;
		NotEmpty = p.NotEmpty;
		representation = p.representation;
	}
	return *this;
}