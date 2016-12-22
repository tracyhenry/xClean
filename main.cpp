#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;
typedef pair<vector<string>, vector<string>> t_rule;
typedef unordered_map<string, int> umpsi;

vector<string> get_tokens(string s)
{
	s += ' ';
	vector<string> ans;
	string ss = "";
	for (int i = 0; i < (int) s.size(); i ++)
		if (! isalpha(s[i]) && ! isdigit(s[i]))
		{
			if (ss.size())
				ans.push_back(ss);
			ss = "";
		}
		else
			ss += s[i];
	return ans;
}

bool is_subseq_greedy(string lhs, string rhs)
{
	int last_pos = -1;
	for (int j = 0; j < (int) lhs.size(); j ++)
		for (last_pos ++; last_pos < (int) rhs.size(); last_pos ++)
			if (rhs[last_pos] == lhs[j])
				break;

	return last_pos < (int) rhs.size();
}

bool is_subseq_dp(string lhs, string rhs)
{
	vector<string> lhs_token_set = get_tokens(lhs);
	vector<string> rhs_token_set = get_tokens(rhs);

	vector<int> start_token;
	string lhs_concat = "";
	for (string s : lhs_token_set)
	{
		lhs_concat += s;
		start_token.push_back((int) s.size());
		for (int i = 0; i < (int) s.size() - 1; i ++)
			start_token.push_back(0);
	}

	int n = (int) lhs_concat.size();
	int m = (int) rhs_token_set.size();
	vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

	dp[0][0] = true;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
		{
			for (int k = 0; k < i; k ++)
				if (dp[k][j - 1])
				{
					string cur_substr = lhs_concat.substr(k, i - k);
					if (cur_substr[0] != rhs_token_set[j - 1][0])
						continue;
					if (is_subseq_greedy(cur_substr.substr(1), rhs_token_set[j - 1].substr(1)))
					{
						dp[i][j] = true;
						break;
					}
				}
		}

	return dp[n][m] && lhs != rhs;
}

void print_rule(t_rule rule)
{
	for (string s : rule.first)
		cout << s << " ";
	cout << "==> ";
	for (string s : rule.second)
		cout << s << " ";
	cout << endl;
}

double jaccard(umpsi a, umpsi b)
{
	double itsct = 0, unn = 0;
	for (auto cp : a)
		if (b.count(cp.first))
		{
			itsct += min(a[cp.first], b[cp.first]);
			unn += max(a[cp.first], b[cp.first]);
		}
		else
			unn += cp.second;
	for (auto cp : b)
		if (! a.count(cp.first))
			unn += cp.second;
	return itsct / unn;
}

int main()
{
	freopen("dept_names/dept_names.txt", "r", stdin);
	vector<string> cells;
	for (string cell; getline(cin, cell); )
		cells.push_back(cell);

	int n = (int) cells.size();
	vector<vector<string>> tokens;
	vector<umpsi> token_maps;
	for (int i = 0; i < n; i ++)
	{
		tokens.push_back(get_tokens(cells[i]));
		token_maps.push_back(umpsi());
		for (string s : tokens[i])
			token_maps[i][s] ++;
	}

	//count occurrences
	unordered_map<string, int> occurrence;
	for (int i = 0; i < n; i ++)
		for (int x = 0; x < (int) tokens[i].size(); x ++)
			for (int y = x; y < (int) tokens[i].size(); y ++)
			{
				string cur_string = "";
				for (int j = x; j < y; j ++)
					cur_string += tokens[i][j] + " ";
				cur_string += tokens[i][y];
				occurrence[cur_string] ++;
			}

	//candidate rules
	vector<t_rule> rules;
	unordered_set<string> lhs_set;
	for (int i = 0; i < n; i ++)
		for (int x = 0; x < (int) tokens[i].size(); x ++)
		{
			string cur_lhs = tokens[i][x];
			if (cur_lhs.size() < 3)
				continue;
			if (lhs_set.count(cur_lhs))
				continue;
			lhs_set.insert(cur_lhs);
			for (auto cp : occurrence)
			{
				string cur_string = cp.first;
				//check whether cur_lhs is a sub sequence of cur_string
				if (is_subseq_dp(cur_lhs, cur_string))
					rules.emplace_back(get_tokens(cur_lhs), get_tokens(cur_string));
			}
		}
/*
	for (t_rule rule : rules)
		print_rule(rule);
*/

	//add reverse rules
	for (int i = 0, n = (int) rules.size(); i < n; i ++)
		rules.push_back(make_pair(rules[i].second, rules[i].first));

	//make full expansion set
	vector<umpsi> expansion_set;
	vector<vector<int>> applicable_rule_ids;
	for (int i = 0; i < n; i ++)
	{
		umpsi cur_expansion_set = token_maps[i];

		applicable_rule_ids.push_back(vector<int>());
		for (int j = 0; j < (int) rules.size(); j ++)
		{
			t_rule rule = rules[j];
			bool applicable = true;
			umpsi tmp_map = token_maps[i];
			for (string t : rule.first)
				if (! tmp_map.count(t) || tmp_map[t] == 0)
				{
					applicable = false;
					break;
				}
				else
					tmp_map[t] --;
			if (! applicable)
				continue;

			applicable_rule_ids[i].push_back(j);
			for (string t : rule.second)
				cur_expansion_set[t] ++;

		}
		expansion_set.push_back(cur_expansion_set);
	}

	//check
	for (int i = 0; i < n; i ++)
		for (int j = i + 1; j < n; j ++)
		{
			vector<int> cur_applicable;
			for (int k = 0; k < (int) applicable_rule_ids[i].size(); k ++)
			{
				t_rule rule = rules[applicable_rule_ids[i][k]];
				bool applicable = true;
				umpsi tmp_map = token_maps[i];
				for (string t : rule.first)
					if (! tmp_map.count(t) || tmp_map[t] == 0)
					{
						applicable = false;
						break;
					}
					else
						tmp_map[t] --;
				for (string t : rule.second)
					if (! expansion_set[j].count(t))
					{
						applicable = false;
						break;
					}
				if (! applicable)
					continue;
				cur_applicable.push_back(applicable_rule_ids[i][k]);
			}
			if (cur_applicable.size() > 15)
				continue;

			//brute-force
			int M = 1 << (cur_applicable.size());
			double max_sim = 0;
			for (int mask = 0; mask < M; mask ++)
			{
				umpsi cur_map = token_maps[i];
				bool applicable = true;
				for (int k = 0; k < (int) cur_applicable.size(); k ++)
				{
					if (! (mask & (1 << k)))
						continue;
					t_rule cur_rule = rules[cur_applicable[k]];
					for (string s : cur_rule.first)
						if (! cur_map.count(s) || cur_map[s] == 0)
							applicable = false;
						else
							cur_map[s] --;
					if (! applicable)
						break;
				}
				if (! applicable)
					continue;
				for (int k = 0; k < (int) cur_applicable.size(); k ++)
				{
					if (!(mask & (1 << k)))
						continue;
					t_rule cur_rule = rules[cur_applicable[k]];
					for (string s : cur_rule.second)
						cur_map[s] ++;
				}
				max_sim = max(max_sim, jaccard(cur_map, token_maps[j]));
			}
			if (max_sim > 0.7)
				cout << cells[i] << endl << cells[j] << endl << endl;
		}

	return 0;
}
