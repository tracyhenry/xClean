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
		for (int st = 0; st < (int) tokens[i].size(); st ++)
			for (int en = st; en < (int) tokens[i].size(); en ++)
			{
				string t = "";
				for (int k = st; k <= en; k ++)
					t += tokens[i][k] + (k == en ? "" :  " ");
				g_token_map[t] += weights[i];
			}

	vector<pair<int, string>> sort_array;
	for (auto cp : g_token_map)
		sort_array.emplace_back(cp.second, cp.first);
	sort(sort_array.begin(), sort_array.end());

	for (int i = 0; i < (int) sort_array.size(); i ++)
	{
		global_list.push_back(sort_array[i].second);
		token_rankings[sort_array[i].second] = i;
	}

	//build o_signatures
	o_sigs.clear();
	o_large_sigs.clear();
	for (int i = 0; i < n; i ++)
	{
		o_sigs.push_back(buildOriginalSigs(i));
		o_large_sigs.push_back(buildOriginalLargeTokenSigs(i));
	}

	//build t_signatures
	t_sigs.clear();
	t_large_sigs.clear();
	for (int i = 0; i < n; i ++)
	{
		//construct a different set of applicable rules
		vector<t_rule> applicable_rules;
		for (int rule_id : applicable_rule_ids[i])
			applicable_rules.push_back(rules[rule_id]);

		for (auto cp : matchable_tokens[i])
		{
			vector<string> t;
			for (int j = cp.first; j <= cp.second; j ++)
				t.push_back(tokens[i][j]);
			applicable_rules.push_back(make_pair(t, t));
		}

		t_sigs.push_back(buildDpSigs(tokens[i], applicable_rules));
		t_large_sigs.push_back(buildDpLargeTokenSigs(tokens[i], applicable_rules));
	}
	cerr << "Signature built." << endl;
}

vector<pair<string, string>> PolynomialJoiner::getJoinedStringPairs()
{
	vector<pair<string, string>> ans;
	unordered_set<pair<int, int>, pairii_hash> candidates;

	//build inverted lists
	unordered_map<string, vector<int>> inv_list;
	for (int i = 0; i < n; i ++)
		for (string t : t_large_sigs[i])
			inv_list[t].push_back(i);

	//generate candidates
	for (int i = 0; i < n; i ++)
	{
		unordered_set<int> cur_set;
		for (string t : o_large_sigs[i])
			for (int v : inv_list[t])
				if (v != i)
					cur_set.insert(v);
		for (int v : cur_set)
		{
			pair<int, int> cur_cp = make_pair(min(i, v), max(i, v));
			candidates.insert(cur_cp);
		}
	}
	cout << candidates.size() << endl;

	//calculate similarity for candidate pairs
	best_rule_count.clear();
	for (auto cp : candidates)
	{
		double sim = greedy_get_similarity(cp.first, cp.second);
		if (sim >= JAC_THRESHOLD)
			ans.emplace_back(cells[cp.first], cells[cp.second]);
	}

	//sort the rules
	vector<pair<int, t_rule>> sort_array;
	for (auto cp : best_rule_count)
		sort_array.emplace_back(cp.second, cp.first);
	sort(sort_array.begin(), sort_array.end());
	for (auto cp : sort_array)
	{
		Common::print_rule(cp.second);
		cout << "\t" << cp.first << endl;
	}
	return ans;
}
