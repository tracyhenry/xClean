//
// Created by Wenbo Tao on 1/12/17.
//

#ifndef XCLEAN_LARGETOKENDPSIGBUILDER_H
#define XCLEAN_LARGETOKENDPSIGBUILDER_H


#include "SigBuilder.h"
using namespace std;

class LargeTokenDpSigBuilder : public SigBuilder
{
public:
	LargeTokenDpSigBuilder(vector<string> &, vector<t_rule> &, umpsi &, double);

	//overwrite base class virtual function
	unordered_set<string> genSignatures();
};


#endif //XCLEAN_LARGETOKENDPSIGBUILDER_H
