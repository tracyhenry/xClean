//
// Created by Wenbo Tao on 12/27/16.
//

#ifndef XCLEAN_SLOWRULEGENERATOR_H
#define XCLEAN_SLOWRULEGENERATOR_H
#include "RuleGenerator.h"
using namespace std;


class SlowLCSRuleGenerator : public RuleGenerator
{
public:
	//constructor
	SlowLCSRuleGenerator(vector<string>, vector<int>);

	//overwrite the virtual method
	vector<t_rule> gen_rules();

private:
	//occurrence
	unordered_map<string, int> occurrence;
};


#endif //XCLEAN_SLOWRULEGENERATOR_H
