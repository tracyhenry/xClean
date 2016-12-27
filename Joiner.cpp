//
// Created by Wenbo Tao on 12/27/16.
//

#include "Joiner.h"

Joiner::Joiner(vector<t_rule> r, vector<string> s, vector<int> w)
		: rules(r), cells(s), weights(w)
{
	this->r = (int) r.size();
	this->n = (int) s.size();
}
