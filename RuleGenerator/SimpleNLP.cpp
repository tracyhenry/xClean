//
// Created by Wenbo Tao on 1/6/17.
//

#include "SimpleNLP.h"
#include "FastLCS.h"

using namespace std;

SimpleNLP::SimpleNLP(vector<string> s, vector<int> w)
	: RuleGenerator(s, w)
{
}

vector<t_rule> SimpleNLP::gen_rules()
{
	RuleGenerator *fastLCS = new FastLCS(cells, weights);
	vector<t_rule> initial_rule_set = fastLCS->gen_rules();
	delete fastLCS;

	vector<pair<double, t_rule>> sort_array;
	for (t_rule rule : initial_rule_set)
	{
		//remove rules like science ==> science center
		if (rule.first.size() == 1 && rule.second.size() > 1)
			if (rule.second[0].find(rule.first[0]) == 0 ||
					rule.first[0].find(rule.second[0]) == 0)
				if (fabs((int) rule.first[0].size() - (int) rule.second[0].size()) <= 1)
					continue;

		//remove rules with lhs size greater than 1
		if (rule.first.size() > 1)
			continue;

		//remove rules with digits
		bool has_digit = false;
		for (int i = 0; i < (int) rule.first[0].size(); i ++)
			if (isdigit(rule.first[0][i]))
				has_digit = true;
		for (int i = 0; i < (int) rule.second[0].size(); i ++)
			if (isdigit(rule.second[0][i]))
				has_digit = true;

		if (has_digit)
			continue;

		//directly approve initialism
		if (rule.first.size() == 1 && rule.second.size() == 1)
			if (rule.second[0].find(rule.first[0]) == 0)
			{
				sort_array.emplace_back(0, rule);
				continue;
			}

		//string representation of left & right hand side
		string lhs = "", rhs = "";
		for (string t : rule.first)
			lhs += t;
		for (string t : rule.second)
			rhs += t;

		//whether a char in rhs is the beginning of a token
		vector<int> word_beginning;
		for (string t : rule.second)
		{
			if (! stop_words.count(t))
				word_beginning.push_back(0);
			else
				word_beginning.push_back((int) t.size());
			for (int i = 1; i < (int) t.size(); i ++)
				word_beginning.push_back((int) t.size());
		}

		//consonant counting
		vector<vector<int>> cons_counting(rhs.size(), vector<int>(rhs.size(), 0));
		for (int i = 0; i < (int) rhs.size(); i ++)
			for (int j = i; j < (int) rhs.size(); j ++)
			{
				cons_counting[i][j] = (j == i ? 0 : cons_counting[i][j - 1]);
				if (! vowels.count(rhs[j]))
					cons_counting[i][j] ++;
			}

		//calculate a best LCS matching
		int len_l = (int) lhs.size();
		int len_r = (int) rhs.size();
		vector<vector<int>> opt(len_l + 1, vector<int>(len_r + 1, -1));
		opt[0][0] = 0;
		for (int i = 1; i <= len_l; i ++)
			for (int j = 1; j <= len_r; j ++)
			{
				if (lhs[i - 1] != rhs[j - 1])
					continue;

				//enumerate the matching for i - 1
				for (int k = j - 1; k >= 0; k --)
				{
					if (word_beginning[j - 1] && vowels.count(lhs[i - 1]) && k < j - 1)
						break;
					if (word_beginning[j - 1])
					{
						if ((double) j - k - 1 > (double) word_beginning[j - 1] * SKIP_PCTG)
							break;
						if (cons_counting[k][j - 2] > 1)
							break;
					}

					int wt = (word_beginning[j - 1] ? cons_counting[k][j - 2] : 0);
					if (opt[i - 1][k] != -1 && (opt[i][j] == -1 || opt[i - 1][k] + wt < opt[i][j]))
						opt[i][j] = opt[i - 1][k] + wt;

					//do not skip the beginning of a word
					if (k > 0 && word_beginning[k - 1] == 0)
						break;
				}
			}

		//optimal
		int min_skip = -1;
		for (int j = 1; j <= len_r; j ++)
			if (opt[len_l][j] != -1 && (j == len_r || opt[len_l][j] + cons_counting[j][len_r - 1] <= 2))
				if (min_skip == -1 || opt[len_l][j] < min_skip)
					min_skip = opt[len_l][j];

		if (min_skip == -1)
			continue;

		//rhs size equals one, min_skip should be less than 2
		if (rule.second.size() == 1 && min_skip > 1)
			continue;

		//acronym should have min_skip = 0
		if (rule.second.size() > 1 && min_skip)
			continue;

		sort_array.emplace_back((double) min_skip, rule);
	}

	//sort by percentage of skip
	sort(sort_array.begin(), sort_array.end());

	vector<t_rule> rules;
	for (auto cp : sort_array)
		rules.push_back(cp.second);

	//add reverse rules
	vector<t_rule> rules_vector = vector<t_rule>(rules.begin(), rules.end());
	for (int i = 0, n = (int) rules_vector.size(); i < n; i ++)
		rules_vector.push_back(make_pair(rules_vector[i].second, rules_vector[i].first));

	return rules_vector;
}
