//
// Created by Wenbo Tao on 12/27/16.
//

#include "FastLCSRuleGenerator.h"

FastLCSRuleGenerator::FastLCSRuleGenerator(vector<string> s, vector<int> w)
		: RuleGenerator(s, w)
{
	//build trie
	trie.clear(), trie.resize(1);
	contain_word.clear(), contain_word.push_back("");

	for (int i = 0; i < n; i ++)
		for (string s : tokens[i])
		{
			if (s.size() < LHS_SIZE_LIM)
				continue;

			//insert s into trie
			int cur_node = 0;
			for (int j = 0; j < (int) s.size(); j ++)
			{
				if (! trie[cur_node].count(s[j]))
				{
					trie[cur_node][s[j]] = (int) trie.size();
					trie.push_back(unordered_map<char, int>());
					contain_word.push_back("");
				}
				cur_node = trie[cur_node][s[j]];
			}
			contain_word[cur_node] = s;
		}
}

vector<t_rule> FastLCSRuleGenerator::gen_rules()
{
	unordered_set<t_rule, rule_hash> rules;
	for (int i = 0; i < n; i ++)
		for (int st = 0; st < (int) tokens[i].size(); st ++)
		{
			string cur_string = "";
			vector<int> start_token;
			for (int j = st; j < (int) tokens[i].size(); j ++)
				for (int k = 0; k < (int) tokens[i][j].size(); k ++)
				{
					cur_string += tokens[i][j][k];
					if (k == 0)
						start_token.push_back(j);
					else
						start_token.push_back(-1);
				}
			//dp
			unordered_set<int> nodes[2];
			int cur_iter = 0;
			nodes[0].clear(), nodes[0].insert(0);

			for (int j = 0; j < cur_string.size(); j ++)
			{
				//current iteration
				cur_iter = 1 - cur_iter;
				nodes[cur_iter].clear();

				for (int node : nodes[cur_iter ^ 1])
				{
					//not include current character
					if (start_token[j] == -1)
						nodes[cur_iter].insert(node);

					//include current character
					if (trie[node].count(cur_string[j]))
						nodes[cur_iter].insert(trie[node][cur_string[j]]);
				}

				//make rules
				if (j + 1 == (int) cur_string.size() || start_token[j + 1] != -1)
				{
					//make rhs
					vector<string> rhs;
					int en = (int) tokens[i].size() - 1;
					if (j + 1 < (int) cur_string.size())
						en = start_token[j + 1] - 1;
					for (int k = st; k <= en; k ++)
						rhs.push_back(tokens[i][k]);

					//for every node in the previous iteration
					for (int node : nodes[cur_iter])
						if (contain_word[node].size())
						{
							vector<string> lhs;
							lhs.push_back(contain_word[node]);

							//get rid of identity rules
							if (rhs.size() == 1 && lhs[0] == rhs[0])
								continue;
							rules.insert(make_pair(lhs, rhs));
						}
				}
			}
		}

	//add reverse rules
	vector<t_rule> rules_vector = vector<t_rule>(rules.begin(), rules.end());
	for (int i = 0, n = (int) rules_vector.size(); i < n; i ++)
		rules_vector.push_back(make_pair(rules_vector[i].second, rules_vector[i].first));

	return vector<t_rule>(rules.begin(), rules.end());
}
