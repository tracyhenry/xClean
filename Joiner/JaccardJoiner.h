//
// Created by Wenbo Tao on 2/11/17.
//

#ifndef XCLEAN_JACCARDJOINER_H
#define XCLEAN_JACCARDJOINER_H
#include "Joiner.h"
using namespace std;


class JaccardJoiner : public Joiner
{
public:
	//constructor
	JaccardJoiner(vector<t_rule>, vector<string>, vector<int>, double);

	//overwrite the virtual method
	vector<pair<string, string>> getJoinedStringPairs();

private:
	//jaccard threshold
	double threshold;
};


#endif //XCLEAN_JACCARDJOINER_H
