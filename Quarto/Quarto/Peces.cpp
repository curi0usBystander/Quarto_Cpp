#include "stdafx.h"
#include "Peces.h"

Peces::Peces() {
	big = false;
	red = false;
	hollow = false;
	circular = false;
	NotEmpty = false;
	peca = "";
}

Peces::Peces(bool g, bool b, bool f, bool r) {
	NotEmpty = true;
	big = g;
	red = b;
	hollow = f;
	circular = r;
	peca = this->drawPiece();
	/*if (big && hollow && red && circular) peca = "(V*)";
	else if (big && hollow && red && !circular) peca = "[V*]";
	else if (big && hollow && !red && circular) peca = "(B*)";
	else if (big && hollow && !red && !circular) peca = "[B*]";
	else if (big && !hollow && red && circular) peca = "(V)";
	else if (big && !hollow && red && !circular) peca = "[V]";
	else if (big && !hollow && !red && circular) peca = "(B)";
	else if (big && !hollow && !red && !circular) peca = "[B]";

	else if (!big && hollow && red && circular) peca = "(v*)";
	else if (!big && hollow && red && !circular) peca = "[v*]";
	else if (!big && hollow && !red && circular) peca = "(b*)";
	else if (!big && hollow && !red && !circular) peca = "[b*]";
	else if (!big && !hollow && red && circular) peca = "(v)";
	else if (!big && !hollow && red && !circular) peca = "[v]";
	else if (!big && !hollow && !red && circular) peca = "(b)";
	else if (!big && !hollow && !red && !circular) peca = "[b]";*/

}

Peces::Peces(const Peces& p) {
	big = p.big;
	red = p.red;
	hollow = p.hollow;
	circular = p.circular;
	NotEmpty = p.NotEmpty;
	peca = p.peca;
}
bool Peces::esGran() {
	return big;
}

bool Peces::esVermell() {
	return red;
}

bool Peces::esForadat() {
	return hollow;
}

bool Peces::esRodo() {
	return circular;
}

bool Peces::hasProperty(Property p)
{
	switch (p)
	{
	case Peces::Color:
		return red;
		break;
	case Peces::Size:
		return big;
		break;
	case Peces::Top:
		return hollow;
		break;
	case Peces::Form:
		return circular;
		break;
	case Peces::EmptyPiece:
		return NotEmpty;
		break;
	default:
		break;
	}
	return false;
}


bool Peces::esPeca() {
	return NotEmpty;
}

string Peces::mostrar() {
	return peca;
}
string Peces::drawPiece()
{
	string piece = "";
	if (hasProperty(Peces::EmptyPiece)) 
	{
		char color =  hasProperty(Peces::Color) ? 'R' : 'W';
		piece = hasProperty(Peces::Size) ? std::toupper(color) : std::tolower(color);
		piece = hasProperty(Peces::Top) ? piece + "*" : piece + "";
		piece = hasProperty(Peces::Form) ? "(" + piece + ")" : "[" + piece + "]";
	}

	return piece;
}
/*
bool Peces::comparteixenCaract(const Peces& p){
return(gran==p.gran || )
}*/
Peces& Peces::operator=(const Peces& p) {
	if (this != &p) {
		big = p.big;
		red = p.red;
		hollow = p.hollow;
		circular = p.circular;
		NotEmpty = p.NotEmpty;
		peca = p.peca;
	}
	return *this;
}