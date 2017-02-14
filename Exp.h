//
// Created by Wenbo Tao on 2/11/17.
//

#ifndef XCLEAN_EXP_H
#define XCLEAN_EXP_H
#include "Common.h"
using namespace std;


class Exp
{
public:
	//datasets
	static unordered_set<string> file_names;

	//preprocess the raw data
	static void preprocess();

	//check
	static void check();
	static void check2();

	//effectiveness
	static void varyDictionary();
	static void varyMeasure();

};


#endif //XCLEAN_EXP_H
