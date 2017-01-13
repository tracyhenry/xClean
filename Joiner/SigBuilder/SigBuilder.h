//
// Created by Wenbo Tao on 1/3/17.
//

#ifndef XCLEAN_SIGBUILDER_H
#define XCLEAN_SIGBUILDER_H

#include "../../Common.h"
using namespace std;


class SigBuilder
{
public:
	SigBuilder(vector<string> &, vector<t_rule>, umpsi &, umpsi &, double);

	//abstract method for generating signatures
	virtual unordered_set<string> genSignatures() = 0;

	//virtual destructor
	virtual ~SigBuilder() = default;

protected:
	//set of tokens
	vector<string> &tokens;

	//set of applicable rules
	vector<t_rule> applicable_rules;

	//token rankings
	umpsi &token_rankings;

	//expansion set
	umpsi &exp_set;

	//Jaccard threshold
	double JAC_THRESHOLD;
};


#endif //XCLEAN_SIGBUILDER_H
