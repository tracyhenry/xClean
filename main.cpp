#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

const int MIN_LEN = 3;
const int MAX_LEN = 6;

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
	vector<string> token_set = get_tokens(rhs);
	int n = (int) lhs.size();
	int m = (int) token_set.size();
	vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
	dp[0][0] = true;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
		{
			for (int k = 0; k < i - 1; k ++)
				if (dp[k][j - 1])
				{
					string cur_substr = lhs.substr(k, i - k);
					if (cur_substr[0] != token_set[j - 1][0])
						continue;
					if (is_subseq_greedy(cur_substr.substr(1), token_set[j - 1].substr(1)))
					{
						dp[i][j] = true;
						break;
					}
				}
		}

	return dp[n][m];
}

int main()
{
	freopen("dept_names.in", "r", stdin);
	vector<string> cells;
	for (string cell; getline(cin, cell); )
		cells.push_back(cell);

	int n = (int) cells.size();
	vector<vector<string>> tokens;
	for (int i = 0; i < n; i ++)
		tokens.push_back(get_tokens(cells[i]));

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

	//possible repairs
	unordered_map<string, string> repairs;
	for (int i = 0; i < n; i ++)
		for (int x = 0; x < (int) tokens[i].size(); x ++)
		{
			string cur_lhs = "";
			for (int y = x; y < (int) tokens[i].size(); y ++)
			{
				cur_lhs += tokens[i][y];
				if ((int) cur_lhs.size() > MAX_LEN)
					break;
				if ((int) cur_lhs.size() < MIN_LEN)
					continue;
				if (repairs.count(cur_lhs))
					continue;

				string cur_repair;
				int max_occurrence = 0;
				for (auto cp : occurrence)
				{
					string cur_string = cp.first;
					int cur_occurrence = cp.second;

					//check whether cur_lhs is a sub sequence of cur_string
					if (is_subseq_dp(cur_lhs, cur_string))
						if (cur_occurrence > max_occurrence)
						{
							max_occurrence = cur_occurrence;
							cur_repair = cur_string;
						}
				}

				if (max_occurrence > 0)
					repairs[cur_lhs] = cur_repair;
			}
		}

	for (auto cp : repairs)
        if (cp.first != cp.second)
			cout << cp.first << " ==> " << cp.second << endl;

	return 0;
}
