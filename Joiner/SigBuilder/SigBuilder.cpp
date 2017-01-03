//
// Created by Wenbo Tao on 1/3/17.
//

#include "SigBuilder.h"
using namespace std;

SigBuilder::SigBuilder(vector<string> &tks, vector<t_rule> &rules, umpsi &rankings, umpsi &e_set, double th)
	: tokens(tks), applicable_rules(rules), token_rankings(rankings), exp_set(e_set), JAC_THRESHOLD(th)
{}
