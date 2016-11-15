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
				for (int j = x; j <= y; j ++)
					cur_string += tokens[i][j] + " ";
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
					int last_pos = -1;
					for (int j = 0; j < (int) cur_lhs.size(); j ++)
						for (last_pos ++; last_pos < (int) cur_string.size(); last_pos ++)
							if (cur_string[last_pos] == cur_lhs[j])
								break;

					if (last_pos < (int) cur_string.size())
						if (cur_occurrence > max_occurrence)
							max_occurrence = cur_occurrence, cur_repair = cur_string;
				}

				repairs[cur_lhs] = cur_repair;
			}
		}

	for (auto cp : repairs)
        if (cp.first != cp.second)
		    cout << cp.first << " ==> " << cp.second << endl;

	return 0;
}
