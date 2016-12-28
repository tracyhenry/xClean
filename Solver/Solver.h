//
// Created by Wenbo Tao on 12/26/16.
//

#ifndef XCLEAN_SOLVER_H
#define XCLEAN_SOLVER_H
#include "../Common.h"
#include "../RuleGenerator/RuleGenerator.h"
#include "../Joiner/Joiner.h"
using namespace std;


class Solver
{
public:
	Solver(string, string);

protected:
	//strings
	vector<string> cells;

	//weights
	vector<int> weights;

	//number of cells
	int n;
};


#endif //XCLEAN_SOLVER_H
