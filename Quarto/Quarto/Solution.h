#pragma once
#ifndef SOLUCIO_H
#define SOLUCIO_H
#include "State.h"
#include <climits>

#define gran 0;
#define vermell 1;
#define foradat 2;
#define rodo 3;

class Solution {
public:
	Solution(const State &);
	int minimax(const State&, int);
	int alfaBeta(const State&, int, int, int);
	int heuristic(State, bool, int);
	State getBest();
	bool getDraw();

private:
	bool draw;
	State e;
	State bestState;
	vector<State> generateDescendant(const State&);
	bool hasWon(const vector<int>&);
	int shareCharacteristics(const State&, int, int, int, int, vector<int>&);

};

#endif

