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
	unordered_set<t_rule, rule_hash> rule_hash_table;

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
	vector<vector<pair<int, int>>> matchable_tokens;

	//applicable rules
	vector<vector<int>> applicable_rule_ids;

	//expansion sets
	vector<umpsi> expansion_set;

	//thresholds
	const double JAC_THRESHOLD = 0.8;
	const int APPLICABLE_THRESHOLD = 15;

	//functions
	void gen_applicable_rules();
	void gen_expansion_set();
};


#endif //XCLEAN_JOINER_H
