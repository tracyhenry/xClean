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

	//SIGMOD 13 - similarity
	double get_similarity(int, int);
	double rule_gain(t_rule, umpsi, int);
};


#endif //XCLEAN_POLYNOMIALJOINER_H
