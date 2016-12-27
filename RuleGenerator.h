//
// Created by Wenbo Tao on 12/26/16.
//

#ifndef XCLEAN_RULEGENERATOR_H
#define XCLEAN_RULEGENERATOR_H
#include "Common.h"
using namespace std;

class RuleGenerator
{
public:
	//constructor
	RuleGenerator() {}
	RuleGenerator(vector<string>, vector<int>);

	//abstract method for generating rules
	virtual vector<t_rule> gen_rules() = 0;

protected:
	vector<string> cells;
	vector<int> weights;
	int n;
};

class SlowLCSRuleGenerator : public RuleGenerator
{
public:
	//constructor
	SlowLCSRuleGenerator(vector<string>, vector<int>);

	//overwrite the virtual method
	vector<t_rule> gen_rules();

private:
	//tokens of each cell
	vector<vector<string>> tokens;

	//token maps of each cell
	vector<umpsi> token_maps;

	//occurances
	unordered_map<string, int> occurrence;
};

#endif //XCLEAN_RULEGENERATOR_H
