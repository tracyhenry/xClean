//
// Created by Wenbo Tao on 1/28/17.
//

#include "NLPRule.h"
#include "WildLCS.h"
using namespace std;

NLPRule::NLPRule(vector<string> s, vector<int> w) :
	RuleGenerator(s, w)
{
}

vector<t_rule> NLPRule::gen_rules()
{
	RuleGenerator *wildLCS = new WildLCS(cells, weights);
	vector<t_rule> initial_rule_set = wildLCS->gen_rules();
	delete wildLCS;

	vector<t_rule> ans;
	for (t_rule rule : initial_rule_set)
	{
		int abbr_len = rule.first[0].size();
		if (rule.second.size() > min(abbr_len + 5, abbr_len * 2))
			continue;
		if (stop_words.count(rule.first[0]))
			continue;
		if (rule.first[0][0] != rule.second[0][0])
			continue;
		ans.push_back(rule);
	}
	return ans;
}