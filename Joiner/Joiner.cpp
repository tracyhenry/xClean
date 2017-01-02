//
// Created by Wenbo Tao on 12/27/16.
//

#include "Joiner.h"

Joiner::Joiner(vector<t_rule> r, vector<string> s, vector<int> w)
		: rules(r), cells(s), weights(w)
{
	this->r = (int) r.size();
	this->n = (int) s.size();

	//build token sets and token maps
	tokens.clear();
	token_maps.clear();
	for (int i = 0; i < n; i ++)
	{
		tokens.push_back(Common::get_tokens(cells[i]));
		token_maps.push_back(umpsi());
		for (string s : tokens[i])
			token_maps[i][s] ++;
	}

	//generate applicable rules for each string
	gen_applicable_rules();

	//generate expansion set
	gen_expansion_set();
}

void Joiner::gen_applicable_rules()
{
	//build rule inverted lists
	int max_lhs_size = 0;
	unordered_map<string, vector<int>> rule_invl;
	for (int i = 0; i < (int) rules.size(); i ++)
	{
		string s = "";
		for (int j = 0; j < (int) rules[i].first.size(); j ++)
		{
			s += rules[i].first[j];
			if (j + 1 < (int) rules[i].first.size())
				s += " ";
		}
		rule_invl[s].push_back(i);
		max_lhs_size = max(max_lhs_size, (int) rules[i].first.size());
	}
/*
	for (auto cp : rule_invl)
		for (int rule_id : cp.second)
			Common::print_rule(rules[rule_id]);

	vector<pair<int, string>> sort_array;
	for (auto cp : rule_invl)
		sort_array.emplace_back(cp.second.size(), cp.first);
	sort(sort_array.begin(), sort_array.end(), greater<pair<int, string>>());
	for (int i = 0; i < (int) sort_array.size(); i ++)
		cout << sort_array[i].second << " : " << sort_array[i].first << endl;
*/
	//generate applicable rule ids
	int sum_r = 0, max_r = 0;
	for (int i = 0; i < n; i ++)
	{
		unordered_set<int> app_set;
		for (int j = 0; j < (int) tokens[i].size(); j ++)
		{
			string cur_substr = "";
			for (int l = 1; l <= max_lhs_size; l ++)
			{
				if (j + l - 1 >= (int) tokens[i].size())
					break;
				if (l > 1)
					cur_substr += " ";
				cur_substr += tokens[i][j + l - 1];
				for (int rule_id : rule_invl[cur_substr])
					app_set.insert(rule_id);
			}
		}
		applicable_rule_ids.push_back(vector<int>(app_set.begin(), app_set.end()));
		max_r = max(max_r, (int) applicable_rule_ids.back().size());
		sum_r += (int) applicable_rule_ids.back().size();
	}

	cout << "MAX #applicable rule: " << max_r << endl;
	cout << "AVG #applicable rule: " << sum_r / (double) n << endl;
}

void Joiner::gen_expansion_set()
{
	expansion_set.clear();
	for (int i = 0; i < n; i ++)
	{
		umpsi cur_expansion_set = token_maps[i];
		for (int rule_id : applicable_rule_ids[i])
		{
			t_rule rule = rules[rule_id];
			for (string t : rule.second)
				cur_expansion_set[t] ++;
		}
		expansion_set.push_back(cur_expansion_set);
	}
}