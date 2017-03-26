#include "stdafx.h"
#include "Solucio.h"

Solucio::Solucio(const Estat& es) {
	e = es;
	empat = false;
}

bool Solucio::obtEmpat() {
	return empat;
}
int Solucio::minimax(const Estat& es, int nivell) {
	int millor, valor;
	bool max = (nivell % 2 == 0);

	empat = false;
	if (es.obtPecesCons()>8 && nivell == 6)return heuristica(es, !max, nivell); //nous per provar eficiencia
	else if (es.obtPecesCons()>6 && nivell == 4) return heuristica(es, !max, nivell);
	if (nivell == 2)return heuristica(es, !max, nivell); //es execiu 10 baixarho//ho estat final)

	vector<Estat> fills = generarFills(es);
	if (fills.size() == 0) return heuristica(es, !max, nivell);

	if (!max) {//nivell es min
		millor = INT_MAX;
		for (unsigned int i = 0; i<fills.size(); i++) {
			//fills[i].mostrarTaula();
			valor = minimax(fills[i], nivell + 1);
			if (valor<millor) {
				millor = valor;
				if (nivell == 0)millorE = fills[i]; //com guardar l'estat correcte
			}
		}
	}
	else {//max
		millor = INT_MIN;
		for (unsigned int i = 0; i<fills.size(); i++) {
			valor = minimax(fills[i], nivell + 1);
			if (valor>millor) {
				millor = valor;
				if (nivell == 0)millorE = fills[i];//Nivell correcte??
			}
		}
	}
	return millor;
}




int Solucio::heuristica(Estat es, bool max, int nivell) {
	int puntuacio = 0;
	int ocupades = 0;
	empat = false;
	//comprovem les files
	for (int fila = 0; fila<4; fila++) {
		for (int columna = 0; columna<3; columna++) {
			if (es.ocupat(fila, columna)) {
				vector<int> winner;
				winner.resize(4);
				winner[0] = 0; winner[1] = 0; winner[2] = 0; winner[3] = 0;
				ocupades = 0;
				for (int adjacent = columna + 1; adjacent<4; adjacent++) {
					if (es.ocupat(fila, adjacent)) {
						puntuacio += comparteixenCarac(es, fila, columna, fila, adjacent, winner);
						ocupades++;
					}
				}
				if (haGuanyat(winner) && max) return 100000 - nivell * 10000;
				else if (haGuanyat(winner) && !max) return -100000 + (10000 * nivell);
				if (ocupades == 4 - columna) puntuacio = puntuacio - winner[0] - winner[1] - winner[2] - winner[3];//estava tot ocupat i encara i aixi no podem guanyar
																												   //else return -10000;
			}
		}
	}

	//avaluacio per columnes
	for (int columna = 0; columna<4; columna++) {
		for (int fila = 0; fila<3; fila++) {
			if (es.ocupat(fila, columna)) {
				vector<int> winner;
				winner.resize(4);
				winner[0] = 0; winner[1] = 0; winner[2] = 0; winner[3] = 0;
				ocupades = 0;
				for (int adjacent = fila + 1; adjacent<4; adjacent++) {
					if (es.ocupat(adjacent, columna)) {
						puntuacio += comparteixenCarac(es, fila, columna, adjacent, columna, winner);
						ocupades++;
					}
				}
				if (haGuanyat(winner) && max) return 100000 - nivell * 10000;
				else if (haGuanyat(winner) && !max) return -100000 + (10000 * nivell);
				if (ocupades == 4 - fila) puntuacio = puntuacio - winner[0] - winner[1] - winner[2] - winner[3];//estava tot ocupat i encara i aixi no podem guanyar
																												//else return -10000;
			}
		}
	}

	//diagonal 1 esquerra a dreta
	for (int columna = 0; columna<3; columna++) {
		if (es.ocupat(columna, columna)) {
			vector<int> winner;
			winner.resize(4);
			winner[0] = 0; winner[1] = 0; winner[2] = 0; winner[3] = 0;
			ocupades = 0;
			for (int adjacent = columna + 1; adjacent<4; adjacent++) { //falla aquest o l'altre
				if (adjacent == 4) cout << "AQUI!" << endl;
				if (es.ocupat(adjacent, adjacent)) {
					puntuacio += comparteixenCarac(es, columna, columna, adjacent, adjacent, winner);//feia ocupat de(clum+1,adjacent) per tant agafava comparacions per defecte
					ocupades++;
				}
			}
			if (haGuanyat(winner) && max) return 100000 - nivell * 10000;
			else if (haGuanyat(winner) && !max) return -100000 + (10000 * nivell);
			if (ocupades == 3 - columna) puntuacio = puntuacio - winner[0] - winner[1] - winner[2] - winner[3];//estava tot ocupat i encara i aixi no podem guanyar
																											   //else return -10000;
		}
	}

	//dre-esq
	for (int columna = 3; columna>0; columna--) {
		int fila = 3 - columna;
		if (es.ocupat(fila, columna)) {
			vector<int> winner;
			winner.resize(4);
			winner[0] = 0; winner[1] = 0; winner[2] = 0; winner[3] = 0;
			for (int adjacent = columna - 1; adjacent >= 0; adjacent--) {
				int filaadj = 3 - adjacent;
				//if (adjacent==0) cout<<"AQUI!"<<endl;
				if (es.ocupat(filaadj, adjacent)) {
					puntuacio += comparteixenCarac(es, fila, columna, filaadj, adjacent, winner);
					ocupades++;
				}
			}
			if (haGuanyat(winner) && max) return 100000 - nivell * 10000;
			else if (haGuanyat(winner) && !max) return -100000 + (10000 * nivell);
			if (ocupades == 3 - columna) puntuacio = puntuacio - winner[0] - winner[1] - winner[2] - winner[3];//estava tot ocupat i encara i aixi no podem guanyar

		}
	}
	//if(!max)puntuacio*=-1;//??
	if (es.obtPecesCons() == 16) {
		if (nivell == 0)empat = true; // si nivell==0 vol dir que s'ha acabat i per tant era la ultima peca posada
		return 100000 - nivell * 10000;//???1funciona??
	}
	return puntuacio;
}



int Solucio::comparteixenCarac(const Estat& es, int filap1, int columnap1, int filap2, int columnap2, vector<int>& guanyador) {
	int puntuacio = 0;
	if (es.contingut(filap1, columnap1).esGran() == es.contingut(filap2, columnap2).esGran()) {
		puntuacio++;
		guanyador[0]++;

	}
	if (es.contingut(filap1, columnap1).esVermell() == es.contingut(filap2, columnap2).esVermell()) {
		puntuacio++;
		guanyador[1]++;

	}
	if (es.contingut(filap1, columnap1).esForadat() == es.contingut(filap2, columnap2).esForadat()) {
		puntuacio++;
		guanyador[2]++;

	}
	if (es.contingut(filap1, columnap1).esRodo() == es.contingut(filap2, columnap2).esRodo()) {
		puntuacio++;
		guanyador[3]++;

	}
	return puntuacio;
}

vector<Estat> Solucio::generarFills(const Estat& es) {
	vector<Estat> aux;
	for (int fila = 0; fila<4; fila++) {
		for (int columna = 0; columna<4; columna++) {//la comparacio arribava fins a columna<0 per aixo no anava
			Estat auxiliar = es;
			if (!auxiliar.ocupat(fila, columna)) {
				auxiliar.posicioPeca(fila, columna);
				for (int i = 0; i<16; i++) {
					if (auxiliar.disponible(i).esPeca()) {
						Estat auxiliar2 = auxiliar;
						auxiliar2.pecaAmoure(i);
						aux.push_back(auxiliar2);
					}
				}
			}
		}
	}
	return aux;
}

Estat Solucio::getMillor() {
	return millorE;
}

int Solucio::alfaBeta(const Estat& es, int alfa, int Beta, int nivell) {
	int valor;
	bool max = (nivell % 2 == 0);

	empat = false;
	if (es.obtPecesCons()>3 && heuristica(es, !max, nivell) >= 10000) return 100000 - (10000 * nivell);//max o !max
	else if (es.obtPecesCons()>3 && heuristica(es, !max, nivell) <= -10000) return -100000 + (nivell * 10000);//??

																											  //if(nivell==10) return heuristica (es,!max);

	if (es.obtPecesCons()>8 && nivell == 8)return heuristica(es, !max, nivell); //nous per provar eficiencia
	else if (es.obtPecesCons()>6 && nivell == 5) return heuristica(es, !max, nivell);
	else if (nivell == 2)return heuristica(es, !max, nivell); //es execiu 10 baixarho//ho estat final)*/

	vector<Estat> fills = generarFills(es);
	if (fills.size() == 0) return heuristica(es, !max, nivell);

	if (!max) {//nivell es min
		for (unsigned int i = 0; i<fills.size(); i++) {
			valor = alfaBeta(fills[i], alfa, Beta, nivell + 1);
			if (valor<Beta) {
				Beta = valor;
				if (nivell == 0)millorE = fills[i];
			}
			if (alfa >= Beta) return Beta;
		}
		return Beta;
	}
	else {//max
		for (unsigned int i = 0; i<fills.size(); i++) {
			valor = alfaBeta(fills[i], alfa, Beta, nivell + 1);
			if (valor>alfa) {
				alfa = valor;
				if (nivell == 0)millorE = fills[i];//Nivell correcte??
			}
			if (alfa >= Beta) return alfa;
		}
		return alfa;
	}
}

bool Solucio::haGuanyat(const vector<int>& winner) {
	return(winner[0] == 3 || winner[1] == 3 || winner[2] == 3 || winner[3] == 3);

}
