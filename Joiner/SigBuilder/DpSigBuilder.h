//
// Created by Wenbo Tao on 1/3/17.
//

#ifndef XCLEAN_DPSIGBUILDER_H
#define XCLEAN_DPSIGBUILDER_H

#include "SigBuilder.h"
using namespace std;

class DpSigBuilder : public SigBuilder
{
public:
	DpSigBuilder(vector<string>, vector<t_rule>, umpsi, double);

	//overwrite base class virtual function
	unordered_set<string> genSignatures();
};


#endif //XCLEAN_DPSIGBUILDER_H
