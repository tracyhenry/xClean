//
// Created by Wenbo Tao on 12/27/16.
//

#ifndef XCLEAN_JOINER_H
#define XCLEAN_JOINER_H
#include "../Common.h"
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

	//token sets and maps
	vector<vector<string>> tokens;
	vector<umpsi> token_maps;

	//applicable rules
	vector<vector<int>> applicable_rule_ids;

	//thresholds
	const double JAC_THRESHOLD = 0.7;
	const int APPLICABLE_THRESHOLD = 15;

	//functions
	void gen_applicable_rules();
};


#endif //XCLEAN_JOINER_H
