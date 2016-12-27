//
// Created by Wenbo Tao on 12/27/16.
//

#ifndef XCLEAN_JOINER_H
#define XCLEAN_JOINER_H
#include "Common.h"
using namespace std;

class Joiner
{
public:
	//constructors
	Joiner() {}
	Joiner(vector<t_rule>, vector<string>, vector<int>);

	//join
	virtual vector<pair<string, string>> getJoinedStringPairs() = 0;

protected:
	//set of rules
	vector<t_rule> rules;

	//cells
	vector<string> cells;

	//weights of cells
	vector<int> weights;

	//number of cells
	int n;

	//number of rules
	int r;
};

class BruteForceJoiner : public Joiner
{
public:
	//constructors
	BruteForceJoiner() {}
	BruteForceJoiner(vector<t_rule>, vector<string>, vector<int>);

	//overwrite the virtual method
	vector<pair<string, string>> getJoinedStringPairs();

private:
	//token maps of each cell
	vector<umpsi> token_maps;

	//thresholds
	const double JAC_THRESHOLD = 0.7;
	const int APPLICABLE_THRESHOLD = 15;
};


#endif //XCLEAN_JOINER_H
