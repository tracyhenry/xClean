//
// Created by Wenbo Tao on 12/30/16.
//

#include "PolynomialJoiner.h"

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

	//limit on the number of tokens of transformed strings
	int LIM_NoT = 0;
	for (int i = 0; i < n; i ++)
		LIM_NoT = max(LIM_NoT, (int) tokens[i].size());
	LIM_NoT *= 2;
//	cout << "LIM_NoT : " << LIM_NoT << endl;

	//build signatures
	signatures.clear();
	for (int i = 0; i < n; i ++)
	{
		//generate for each starting point, an inverted list of applicable rules
		vector<vector<int>> rule_inv(tokens[i].size());
		for (int rule_id : applicable_rule_ids[i])
		{
			t_rule rule = rules[rule_id];
			for (int st = 0; st + (int) rule.first.size() - 1 < (int) tokens[i].size(); st ++)
			{
				bool ok = true;
				for (int j = 0; j < (int) rule.first.size(); j ++)
					if (rule.first[j] != tokens[i][st + j])
					{
						ok = false;
						break;
					}
				if (ok)
					rule_inv[st].push_back(rule_id);
			}
		}

//		cout << i << "\t: " << expansion_set[i].size() << " " << applicable_rule_ids[i].size() << " " << tokens[i].size();
		//enumerate all tokens in the full expansion set
		signatures.push_back(unordered_set<string>());
		for (auto cp : expansion_set[i])
		{
			int cur_ranking = token_rankings[cp.first];
			int tot_len = (int) tokens[i].size();

			//dp
			vector<vector<int>> opt(tot_len + 1, vector<int>(LIM_NoT + 1, LIM_NoT));
			opt[0][0] = 0;
			for (int cur = 0; cur < tot_len; cur ++)
				for (int len = 0; len <= LIM_NoT; len ++)
				{
					if (opt[cur][len] >= (int) LIM_NoT - ceil(LIM_NoT * JAC_THRESHOLD) + 1)
						continue;

					int wt;
					//no transformation
					wt = (token_rankings[tokens[i][cur]] < cur_ranking ? 1 : 0);
					if (opt[cur][len] + wt < opt[cur + 1][len + 1])
						opt[cur + 1][len + 1] = opt[cur][len] + wt;

					//using transformations starting at cur
					for (int rule_id : rule_inv[cur])
					{
						t_rule rule = rules[rule_id];
						wt = 0;
						for (string t : rule.second)
							if (token_rankings[t] < cur_ranking)
								wt ++;
						int next_cur = cur + (int) rule.first.size();
						int next_len = len + (int) rule.second.size();
						if (opt[cur][len] + wt < opt[next_cur][next_len])
							opt[next_cur][next_len] = opt[cur][len] + wt;
					}
				}

			//check
			bool in_prefix = false;
			for (int len = 1; len <= LIM_NoT; len ++)
				if (opt[tot_len][len] + 1 <= (int) tot_len - ceil(len * JAC_THRESHOLD) + 1)
				{
					in_prefix = true;
					break;
				}
			if (in_prefix)
				signatures.back().insert(cp.first);
		}
//		cout << " " << signatures.back().size() << endl;
	}
}

vector<pair<string, string>> PolynomialJoiner::getJoinedStringPairs()
{
	return vector<pair<string, string>>();
}
