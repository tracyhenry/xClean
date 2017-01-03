//
// Created by Wenbo Tao on 12/30/16.
//

#include "PolynomialJoiner.h"
#include "SigBuilder/DpSigBuilder.h"

PolynomialJoiner::PolynomialJoiner(vector<t_rule> r, vector<string> s, vector<int> w)
	: Joiner(r, s, w)
{
	//make global token ranked list
	umpsi g_token_map;
	for (int i = 0; i < n; i ++)
		for (string t : tokens[i])
			g_token_map[t] ++;

	vector<pair<int, string>> sort_array;
	for (auto cp : g_token_map)
		sort_array.emplace_back(cp.second, cp.first);
	sort(sort_array.begin(), sort_array.end());

	for (int i = 0; i < (int) sort_array.size(); i ++)
	{
		global_list.push_back(sort_array[i].second);
		token_rankings[sort_array[i].second] = i;
	}

	//build signatures
	signatures.clear();
	for (int i = 0; i < n; i ++)
	{
		vector<t_rule> applicable_rules;
		for (int rule_id : applicable_rule_ids[i])
			applicable_rules.push_back(rules[rule_id]);
		SigBuilder *sigBuilder = new DpSigBuilder(tokens[i], applicable_rules, token_rankings, JAC_THRESHOLD);
		signatures.push_back(sigBuilder->genSignatures());
		delete sigBuilder;
	}
}

vector<pair<string, string>> PolynomialJoiner::getJoinedStringPairs()
{
	return vector<pair<string, string>>();
}
