//
// Created by Wenbo Tao on 12/26/16.
//

#include "Solver.h"
#include "../RuleGenerator/FastLCS.h"
#include "../Joiner/BruteForceJoiner.h"
#include "../Joiner/PolynomialJoiner.h"
#include "../RuleGenerator/SimpleNLP.h"
#include <fstream>
using namespace std;

Solver::Solver(string string_file_name, string weights_file_name)
{
	//read string from file
	ifstream fin1(string_file_name.c_str());
	for (string cell; getline(fin1, cell); )
		cells.push_back(cell);
	fin1.close();
	n = cells.size();

	//read weights from file
	ifstream fin2(weights_file_name.c_str());
	weights.resize(n);
	for (int i = 0; i < n; i ++)
		fin2 >> weights[i];

	//generate rules
	cerr << "Generating rules......" << endl;
	RuleGenerator *ruleGenerator = new SimpleNLP(cells, weights);
	vector<t_rule> rules = ruleGenerator->gen_rules();
	cout << rules.size() << endl;

	for (t_rule rule : rules)
 		Common::print_rule(rule);

	cout << rules.size() << endl;

	//joins
	cerr << "Joining......" << endl;
	Joiner *joiner = new PolynomialJoiner(rules, cells, weights);
	vector<pair<string, string>> joinedStringPairs = joiner->getJoinedStringPairs();

	//output
	for (auto cp : joinedStringPairs)
		cout << cp.first << endl << cp.second << endl << endl;

}
