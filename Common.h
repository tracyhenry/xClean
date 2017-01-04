//
// Created by Wenbo Tao on 12/26/16.
//

#ifndef XCLEAN_COMMON_H
#define XCLEAN_COMMON_H
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;
typedef unordered_map<string, int> umpsi;
typedef pair<vector<string>, vector<string>> t_rule;


struct pair_hash
{
	std::size_t operator () (const std::pair<int, int> &p) const
	{
		return (size_t) ((long long) p.first * (long long) p.second % 9999997LL);
	}
};

class Common
{
public:

	//split a string into tokens
	static vector<string> get_tokens(string);

	//check whether lhs is a subsequece of rhs
	static bool is_subseq_greedy(string lhs, string rhs);

	//use dp to check whether lhs is a constrained-subsequence of rhs
	static bool is_subseq_dp(string lhs, string rhs);

	//print a rule
	static void print_rule(t_rule rule);

	//the jaccard similarity between to unordered maps
	static double jaccard(umpsi a, umpsi b);

};


#endif //XCLEAN_COMMON_H
