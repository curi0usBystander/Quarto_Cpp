#include "stdafx.h"
#include "Solution.h"

Solution::Solution(const State& es)
{
	e = es;
	draw = false;
}

bool Solution::getDraw()
{
	return draw;
}
int Solution::minimax(const State& es, int level) 
{
	int best, value;
	bool max = (level % 2 == 0);

	draw = false;
	// In early fases there's no point in exploring the whole tree.
	if (es.getUsedPieces()>8 && level == 6) return heuristic(es, !max, level); 
	else if (es.getUsedPieces()>6 && level == 4) return heuristic(es, !max, level);
	if (level == 2)return heuristic(es, !max, level);

	vector<State> descendants = generateDescendant(es);
	if (descendants.size() == 0) return heuristic(es, !max, level);

	if (!max) {// min level
		best = INT_MAX;
		for (unsigned int i = 0; i<descendants.size(); i++) {
			//fills[i].mostrarTaula();
			value = minimax(descendants[i], level + 1);
			if (value<best) {
				best = value;
				if (level == 0)bestState = descendants[i]; 
			}
		}
	}
	else {//max
		best = INT_MIN;
		for (unsigned int i = 0; i<descendants.size(); i++) {
			value = minimax(descendants[i], level + 1);
			if (value>best) {
				best = value;
				if (level == 0)bestState = descendants[i];
			}
		}
	}
	return best;
}




int Solution::heuristic(State es, bool max, int level)
{
	int score = 0;
	int ocupied = 0;
	draw = false;
	//check rows
	for (int row = 0; row<4; row++) {
		for (int column = 0; column<3; column++) {
			if (es.occupied(row, column)) {
				vector<int> winner;
				winner.resize(4);
				winner[0] = 0; winner[1] = 0; winner[2] = 0; winner[3] = 0;
				ocupied = 0;
				for (int adjacent = column + 1; adjacent<4; adjacent++) {
					if (es.occupied(row, adjacent)) {
						score += shareCharacteristics(es, row, column, row, adjacent, winner);
						ocupied++;
					}
				}
				if (hasWon(winner) && max) return 100000 - level * 10000;
				else if (hasWon(winner) && !max) return -100000 + (10000 * level);
				if (ocupied == 4 - column) score = score - winner[0] - winner[1] - winner[2] - winner[3];//everything is occupied and yet we cannot win
																												   //else return -10000;
			}
		}
	}

	//check columns
	for (int column = 0; column<4; column++) {
		for (int row = 0; row<3; row++) {
			if (es.occupied(row, column)) {
				vector<int> winner;
				winner.resize(4);
				winner[0] = 0; winner[1] = 0; winner[2] = 0; winner[3] = 0;
				ocupied = 0;
				for (int adjacent = row + 1; adjacent<4; adjacent++) {
					if (es.occupied(adjacent, column)) {
						score += shareCharacteristics(es, row, column, adjacent, column, winner);
						ocupied++;
					}
				}
				if (hasWon(winner) && max) return 100000 - level * 10000;
				else if (hasWon(winner) && !max) return -100000 + (10000 * level);
				if (ocupied == 4 - row) score = score - winner[0] - winner[1] - winner[2] - winner[3];//everything is occupied and yet we cannot win
																												//else return -10000;
			}
		}
	}

	//diagonal 1 left to right
	for (int column = 0; column<3; column++) {
		if (es.occupied(column, column)) {
			vector<int> winner;
			winner.resize(4);
			winner[0] = 0; winner[1] = 0; winner[2] = 0; winner[3] = 0;
			ocupied = 0;
			for (int adjacent = column + 1; adjacent<4; adjacent++) { 
				//if (adjacent == 4) cout << "HERE!" << endl;
				if (es.occupied(adjacent, adjacent)) {
					score += shareCharacteristics(es, column, column, adjacent, adjacent, winner);
					ocupied++;
				}
			}
			if (hasWon(winner) && max) return 100000 - level * 10000;
			else if (hasWon(winner) && !max) return -100000 + (10000 * level);
			if (ocupied == 3 - column) score = score - winner[0] - winner[1] - winner[2] - winner[3];
																											   //else return -10000;
		}
	}

	//right ->left diagonal
	for (int column = 3; column>0; column--) {
		int row = 3 - column;
		if (es.occupied(row, column)) {
			vector<int> winner;
			winner.resize(4);
			winner[0] = 0; winner[1] = 0; winner[2] = 0; winner[3] = 0;
			for (int adjacent = column - 1; adjacent >= 0; adjacent--) {
				int rowadj = 3 - adjacent;
				//if (adjacent==0) cout<<"AQUI!"<<endl;
				if (es.occupied(rowadj, adjacent)) {
					score += shareCharacteristics(es, row, column, rowadj, adjacent, winner);
					ocupied++;
				}
			}
			if (hasWon(winner) && max) return 100000 - level * 10000;
			else if (hasWon(winner) && !max) return -100000 + (10000 * level);
			if (ocupied == 3 - column) score = score - winner[0] - winner[1] - winner[2] - winner[3];

		}
	}

	if (es.getUsedPieces() == 16) {
		if (level == 0)draw = true; 
		return 100000 - level * 10000;
	}
	return score;
}



int Solution::shareCharacteristics(const State& es, int rowp1, int columnp1, int rowp2, int columnp2, vector<int>& winner) {
	int score = 0;
	if (es.getPiece(rowp1, columnp1).hasProperty(Piece::Size) == es.getPiece(rowp2, columnp2).hasProperty(Piece::Size)) {
		score++;
		winner[0]++;

	}
	if (es.getPiece(rowp1, columnp1).hasProperty(Piece::Color) == es.getPiece(rowp2, columnp2).hasProperty(Piece::Color)) {
		score++;
		winner[1]++;

	}
	if (es.getPiece(rowp1, columnp1).hasProperty(Piece::Top) == es.getPiece(rowp2, columnp2).hasProperty(Piece::Top)) {
		score++;
		winner[2]++;

	}
	if (es.getPiece(rowp1, columnp1).hasProperty(Piece::Form) == es.getPiece(rowp2, columnp2).hasProperty(Piece::Form)) {
		score++;
		winner[3]++;

	}
	return score;
}

vector<State> Solution::generateDescendant(const State& es) 
{
	vector<State> aux;
	for (int row = 0; row<4; row++) {
		for (int column = 0; column<4; column++) {
			State auxiliar = es;
			if (!auxiliar.occupied(row, column)) {
				auxiliar.positionPiece(row, column);
				for (int i = 0; i<16; i++) {
					if (auxiliar.getFromPieceList(i).hasProperty(Piece::EmptyPiece)) {
						State auxiliar2 = auxiliar;
						auxiliar2.selectPiece(i);
						aux.push_back(auxiliar2);
					}
				}
			}
		}
	}
	return aux;
}

State Solution::getBest()
{
	return bestState;
}

int Solution::alfaBeta(const State& es, int alfa, int Beta, int level) 
{
	int value;
	bool max = (level % 2 == 0);

	draw = false;
	if (es.getUsedPieces()>3 && heuristic(es, !max, level) >= 10000) return 100000 - (10000 * level);//max o !max
	else if (es.getUsedPieces()>3 && heuristic(es, !max, level) <= -10000) return -100000 + (level * 10000);//??


	if (es.getUsedPieces()>8 && level == 8)return heuristic(es, !max, level); 
	else if (es.getUsedPieces()>6 && level == 5) return heuristic(es, !max, level);
	else if (level == 2)return heuristic(es, !max, level); 

	vector<State> fills = generateDescendant(es);
	if (fills.size() == 0) return heuristic(es, !max, level);

	if (!max) {// min level
		for (unsigned int i = 0; i<fills.size(); i++) {
			value = alfaBeta(fills[i], alfa, Beta, level + 1);
			if (value<Beta) {
				Beta = value;
				if (level == 0)bestState = fills[i];
			}
			if (alfa >= Beta) return Beta;
		}
		return Beta;
	}
	else {//max
		for (unsigned int i = 0; i<fills.size(); i++) {
			value = alfaBeta(fills[i], alfa, Beta, level + 1);
			if (value>alfa) {
				alfa = value;
				if (level == 0)bestState = fills[i];
			}
			if (alfa >= Beta) return alfa;
		}
		return alfa;
	}
}

bool Solution::hasWon(const vector<int>& winner) 
{
	return(winner[0] == 3 || winner[1] == 3 || winner[2] == 3 || winner[3] == 3);

}
