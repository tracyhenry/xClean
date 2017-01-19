//
// Created by Wenbo Tao on 1/18/17.
//

#include "BadBoy.h"
#include "SimpleNLP.h"
using namespace std;

BadBoy::BadBoy(vector<string> s, vector<int> w)
	:RuleGenerator(s, w)
{
}

vector<t_rule> BadBoy::gen_rules()
{
	RuleGenerator *simpleNLP = new SimpleNLP(cells, weights);
	vector<t_rule> initial_rule_set = simpleNLP->gen_rules();
	delete simpleNLP;

	//make neighbors
	unordered_map<vector<string>, unordered_set<string>, vectorstr_hash> neighbors;
	for (int i = 0; i < n; i ++)
	{
		int len = (int) tokens[i].size();
		for (int st = 0; st < len; st ++)
		{
			vector<string> cur;
			for (int en = st; en < len; en ++)
			{
				cur.push_back(tokens[i][en]);
				string nb;
				//st - 1
				nb = (st > 0 ? tokens[i][st - 1] : "");
				neighbors[cur].insert(nb);
				//en + 1
				nb = (st < len - 1 ? tokens[i][en + 1] : "");
				neighbors[cur].insert(nb);
			}
		}
	}
/*
	cout << "-----" << endl;
	for (auto i = 0; i < n; i ++)
		if (token_maps[i].count("d"))
			cout << cells[i] << endl;
	cout << "-----" << endl;
*/
	for (auto& cp : neighbors)
		if (cp.second.size() > 1)
			cp.second.erase("");

	//calculate lhs frequency
	unordered_map<string, int> lhs_freq;
	for (t_rule rule : initial_rule_set)
		if ((rule.first.size() < rule.second.size()) ||
			(rule.first.size() == 1 && rule.first[0].size() < rule.second[0].size()))
				lhs_freq[rule.first[0]] ++;

	//check rules
	vector<t_rule> rules;
	for (t_rule rule : initial_rule_set)
	{
		bool ok = false;
		if (lhs_freq[rule.first[0]] < Common::BAD_THRESHOLD)
			ok = true;
		else
			for (string t1 : neighbors[rule.first])
			{
				for (string t2 : neighbors[rule.second])
					if (Common::is_subseq_greedy(t1, t2))
					{
						ok = true;
						break;
					}
				if (ok)
					break;
			}
		if (ok)
			rules.push_back(rule);
	}

/*	cout << "-----" << endl;
	for (t_rule rule : rules)
		if (rule.first[0] == "d")
			Common::print_rule(rule);
	cout << "-----" << endl;
*/
	return rules;
}
