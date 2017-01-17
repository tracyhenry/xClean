//
// Created by Wenbo Tao on 1/16/17.
//

#include "../PolynomialJoiner.h"
using namespace std;

double PolynomialJoiner::greedy_get_similarity(int x, int y)
{
	//build edges
	vector<pair<pair<int, int>, pair<int, int>>> edges;
	for (auto cp_x : matchable_tokens[x])
		for (auto cp_y : matchable_tokens[y])
		{
			vector<string> lhs, rhs;
			for (int i = cp_x.first; i <= cp_x.second; i ++)
				lhs.push_back(tokens[x][i]);
			for (int i = cp_y.first; i <= cp_y.second; i ++)
				rhs.push_back(tokens[y][i]);
			if (lhs == rhs || rule_hash_table.count(make_pair(lhs, rhs)))
				edges.emplace_back(cp_x, cp_y);
		}

//	cout << endl;
//	cout << cells[x] << endl << cells[y] << endl;
//	for (auto c : edges)
//		cout << c.first.first << " " << c.first.second << " & " << c.second.first << " " << c.second.second << endl;

	//select
	vector<bool> x_used(tokens[x].size());
	vector<bool> y_used(tokens[y].size());
	vector<bool> edge_used(edges.size());
	int i_size = 0;
	int u_size = 0;
	while (1)
	{
		bool matching_exist = false;
		for (int i = 0; i < (int) edges.size(); i ++)
			if (! edge_used[i])
			{
				auto cp_x = edges[i].first;
				auto cp_y = edges[i].second;
				bool ok = true;
				for (int k = cp_x.first; k <= cp_x.second; k ++)
					if (x_used[k])
					{
						ok = false;
						break;
					}
				if (! ok) continue;
				for (int k = cp_y.first; k <= cp_y.second; k ++)
					if (y_used[k])
					{
						ok = false;
						break;
					}
				if (! ok) continue;
				matching_exist = true;
				edge_used[i] = true;
				for (int k = cp_x.first; k <= cp_x.second; k ++)
					x_used[k] = true;
				for (int k = cp_y.first; k <= cp_y.second; k ++)
					y_used[k] = true;
//				int max_size = max(cp_x.second - cp_x.first, cp_y.second - cp_y.first) + 1;
				i_size += 1;
				break;
			}
		if (! matching_exist)
			break;
	}

	u_size = i_size;
	for (int i = 0; i < (int) tokens[x].size(); i ++)
		if (! x_used[i])
			u_size ++;
	for (int i = 0; i < (int) tokens[y].size(); i ++)
		if (! y_used[i])
			u_size ++;

//	cout << i_size << " " << u_size << endl;

	//return jaccard similarity
	return (double) i_size / u_size;
}
