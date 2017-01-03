//
// Created by Wenbo Tao on 1/3/17.
//

#include "DpSigBuilder.h"
using namespace std;

DpSigBuilder::DpSigBuilder(vector<string> &tks, vector<t_rule> &rules, umpsi &rankings, umpsi &e_set, double th)
		: SigBuilder(tks, rules, rankings, e_set, th)
{
}

unordered_set<string> DpSigBuilder::genSignatures()
{
	//generate for each starting point, an inverted list of applicable rules
	vector<vector<t_rule>> rule_inv(tokens.size());
	for (t_rule rule : applicable_rules)
		for (int st = 0; st + (int) rule.first.size() - 1 < (int) tokens.size(); st ++)
		{
			bool ok = true;
			for (int j = 0; j < (int) rule.first.size(); j ++)
				if (rule.first[j] != tokens[st + j])
				{
					ok = false;
					break;
				}
			if (ok)
				rule_inv[st].push_back(rule);
		}

	//limit on the number of tokens in the transformed string
	int LIM = 20;

	//enumerate all tokens in the full expansion set
	unordered_set<string> signatures;
	for (auto cp : exp_set)
	{
		int cur_ranking = token_rankings[cp.first];
		int tot_len = (int) tokens.size();

		//dp
		vector<vector<int>> opt(tot_len + 1, vector<int>(LIM + 1, LIM));
		opt[0][0] = 0;
		for (int cur = 0; cur < tot_len; cur ++)
			for (int len = 0; len <= LIM; len ++)
			{
				if (opt[cur][len] >= (int) LIM - ceil(LIM * JAC_THRESHOLD) + 1)
					continue;

				int wt;
				//no transformation
				wt = (token_rankings[tokens[cur]] < cur_ranking ? 1 : 0);
				if (len < LIM && opt[cur][len] + wt < opt[cur + 1][len + 1])
					opt[cur + 1][len + 1] = opt[cur][len] + wt;

				//using transformations starting at cur
				for (t_rule rule : rule_inv[cur])
				{
					wt = 0;
					for (string t : rule.second)
						if (token_rankings[t] < cur_ranking)
							wt ++;
					int next_cur = cur + (int) rule.first.size();
					int next_len = len + (int) rule.second.size();
					if (next_len <= LIM && opt[cur][len] + wt < opt[next_cur][next_len])
						opt[next_cur][next_len] = opt[cur][len] + wt;
				}
			}

		//check
		bool in_prefix = false;
		for (int len = 1; len <= LIM; len ++)
			if (opt[tot_len][len] + 1 <= tot_len - ceil(len * JAC_THRESHOLD) + 1)
			{
				in_prefix = true;
				break;
			}
		if (in_prefix)
			signatures.insert(cp.first);
	}
	return signatures;
}
