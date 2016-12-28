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
}
