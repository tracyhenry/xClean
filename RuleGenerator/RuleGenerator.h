//
// Created by Wenbo Tao on 12/26/16.
//

#ifndef XCLEAN_RULEGENERATOR_H
#define XCLEAN_RULEGENERATOR_H
#include "../Common.h"
using namespace std;


//hash function for rules
struct rule_hash
{
	std::size_t operator () (const std::pair<vector<string>, vector<string>> &p) const
	{
		size_t a = 1;
		for (string s : p.first)
			a = (size_t) ((long long) a * (long long) std::hash<string>{}(s) % 9999997LL);
		for (string s : p.second)
			a = (size_t) ((long long) a * (long long) std::hash<string>{}(s) % 9999997LL);

		return a;
	}
};


class RuleGenerator
{
public:
	//constructor
	RuleGenerator() {}
	RuleGenerator(vector<string>, vector<int>);

	//abstract method for generating rules
	virtual vector<t_rule> gen_rules() = 0;

	//virtual destructor
	virtual ~RuleGenerator() = default;

protected:
	//cells
	vector<string> cells;

	//weights of cells
	vector<int> weights;

	//number of cells
	int n;

	//token sets and maps
	vector<vector<string>> tokens;
	vector<umpsi> token_maps;

	//lhs size limit
	const int LHS_SIZE_LIM = 1;

	//stop words
	const unordered_set<string> stop_words =
			unordered_set<string>({"the", "for", "to", "in", "and", "of", "on"});
};


#endif //XCLEAN_RULEGENERATOR_H
