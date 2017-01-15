//
// Created by Wenbo Tao on 12/30/16.
//

#ifndef XCLEAN_POLYNOMIALJOINER_H
#define XCLEAN_POLYNOMIALJOINER_H
#include "Joiner.h"
using namespace std;


class PolynomialJoiner : public Joiner
{
public:
	//constructors
	PolynomialJoiner() {}
	PolynomialJoiner(vector<t_rule>, vector<string>, vector<int>);

	//overwrite the virtual method
	vector<pair<string, string>> getJoinedStringPairs();

private:
	//global token rank list
	vector<string> global_list;
	umpsi token_rankings;

	//signatures
	vector<unordered_set<string>> signatures;

	//best rule counting
	unordered_map<t_rule, int, rule_hash> best_rule_count;

	//SIGMOD 13 - similarity
	double get_similarity(int, int);
	double rule_gain(t_rule, umpsi, int);

	//Sig builders
	unordered_set<string> buildLargeTokenDpSigs(vector<string>, vector<t_rule>);
	unordered_set<string> buildDpSigs(vector<string>, vector<t_rule>);
};


#endif //XCLEAN_POLYNOMIALJOINER_H
