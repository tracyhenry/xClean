//
// Created by Wenbo Tao on 12/27/16.
//

#ifndef XCLEAN_FASTLCSRULEGENERATOR_H
#define XCLEAN_FASTLCSRULEGENERATOR_H

#endif //XCLEAN_FASTLCSRULEGENERATOR_H

#include "RuleGenerator.h"
using namespace std;

class FastLCSRuleGenerator : public RuleGenerator
{
public:
	//constructor
	FastLCSRuleGenerator(vector<string>, vector<int>);

	//overwrite the virtual method
	vector<t_rule> gen_rules();

private:
	//trie
	vector<unordered_map<char, int>> trie;
	vector<string> contain_word;
};
