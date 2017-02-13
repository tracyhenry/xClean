//
// Created by Wenbo Tao on 2/11/17.
//

#include "Vldb09.h"
#include "../Joiner/JaccardJoiner.h"
using namespace std;

Vldb09::Vldb09(vector<string> s)
	: RuleGenerator(s)
{
}

vector<t_rule> Vldb09::gen_rules()
{
	vector<t_rule> rules;

	//build example pairs
	JaccardJoiner *jacJoiner = new JaccardJoiner(vector<t_rule>(), cells, Common::VLDB09_JAC_THRESHOLD);
	vector<pair<double, pair<string, string>>> examples = jacJoiner->getJoinedStringPairs();
	cout << "example size: " << examples.size() << endl;

	//algorithm
	unordered_map<t_rule, int, rule_hash> rule_freq;
	for (auto cp : examples)
	{
		vector<string> tks1 = Common::get_tokens(cp.second.first);
		vector<string> tks2 = Common::get_tokens(cp.second.second);
		vector<bool> u1(tks1.size()), u2(tks2.size());
		while (1)
		{
			bool find_identical_pair = false;
			for (auto i = 0; i < tks1.size(); i ++)
				if (! u1[i])
					for (auto j = 0; j < tks2.size(); j ++)
						if (! u2[j] && tks1[i] == tks2[j])
						{
							find_identical_pair = true;
							u1[i] = u2[j] = true;
						}
			if (! find_identical_pair)
				break;
		}
		for (auto i = 0; i < tks1.size(); i ++)
			for (auto j = 0; j < tks2.size(); j ++)
				if (! u1[i] && ! u2[j])
					rule_freq[make_pair(vector<string>(1, tks1[i]), vector<string>(1, tks2[j]))] ++;
	}

	for (auto cp : rule_freq)
		if (cp.second >= 2)
			rules.push_back(cp.first);

	return rules;
}
