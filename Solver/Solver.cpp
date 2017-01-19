//
// Created by Wenbo Tao on 12/26/16.
//

#include "Solver.h"
#include "../RuleGenerator/FastLCS.h"
#include "../Joiner/BruteForceJoiner.h"
#include "../Joiner/PolynomialJoiner.h"
#include "../RuleGenerator/SimpleNLP.h"
#include "../RuleGenerator/BadBoy.h"
#include <fstream>
//using namespace std;

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
	cout << "# Rule: " << rules.size() * 2 << endl;

//	for (t_rule rule : rules)
// 		Common::print_rule(rule);

	//add reverse rules
	for (int i = 0, n = (int) rules.size(); i < n; i ++)
		rules.emplace_back(make_pair(rules[i].second, rules[i].first));

	//calculate number of distinct lhs
	unordered_map<string, int> lhs_set;
	for (t_rule rule : rules)
		if ((rule.first.size() < rule.second.size()) ||
				(rule.first.size() == 1 && rule.first[0].size() < rule.second[0].size()))
			lhs_set[rule.first[0]] ++;
	cout << "# Distinct lhs: " << lhs_set.size() << endl;

	//output top 10 bad boys
	vector<pair<int, string>> sort_array;
	for (auto cp : lhs_set)
		sort_array.emplace_back(cp.second, cp.first);
	sort(sort_array.begin(), sort_array.end(), greater<pair<int, string>>());
	for (int i = 0; i < 10; i ++)
		cout << sort_array[i].second<< " : " << sort_array[i].first << endl;


//	cout << rules.size() << endl;

	//joins
	cerr << "Joining......" << endl;
	Joiner *joiner = new PolynomialJoiner(rules, cells, weights);
	vector<pair<string, string>> joinedStringPairs = joiner->getJoinedStringPairs();

	//output
	cout << joinedStringPairs.size() << endl;
	for (auto cp : joinedStringPairs)
		cout << cp.first << endl << cp.second << endl << endl;
}
