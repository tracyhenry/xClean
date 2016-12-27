//
// Created by Wenbo Tao on 12/26/16.
//

#include "RuleGenerator.h"

RuleGenerator::RuleGenerator(vector<string> s, vector<int> w)
{
	cells = s;
	weights = w;
	n = cells.size();
}
