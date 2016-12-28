//
// Created by Wenbo Tao on 12/27/16.
//

#ifndef XCLEAN_BRUTEFORCEJOINER_H
#define XCLEAN_BRUTEFORCEJOINER_H
#include "Joiner.h"
using namespace std;

class BruteForceJoiner : public Joiner
{
public:
	//constructors
	BruteForceJoiner() {}
	BruteForceJoiner(vector<t_rule>, vector<string>, vector<int>);

	//overwrite the virtual method
	vector<pair<string, string>> getJoinedStringPairs();

private:
	//thresholds
	const double JAC_THRESHOLD = 0.7;
	const int APPLICABLE_THRESHOLD = 15;
};


#endif //XCLEAN_BRUTEFORCEJOINER_H
