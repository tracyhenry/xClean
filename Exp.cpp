//
// Created by Wenbo Tao on 2/11/17.
//

#include <set>
#include "Exp.h"
#include "Joiner/Joiner.h"
#include "Joiner/PolynomialJoiner.h"
#include "Solver/Solver.h"
#include "Joiner/JaccardJoiner.h"
#include "RuleGenerator/BadBoy.h"
#include "RuleGenerator/FastLCS.h"

using namespace std;

unordered_set<string> Exp::file_names = unordered_set<string>({"data/dept_names/dept_names.txt",
															   "data/course_names/course_names.txt",
															   "data/area_names/area_names.txt"});

void Exp::preprocess()
{
	string file_names[3] = {"dept_names/dept_names",
							"course_names/course_names",
							"area_names/area_names"};

	for (string file_name : file_names)
	{
		string full_file_name = "data/" + file_name + "_raw.txt";
		ifstream fin(full_file_name.c_str());
		unordered_set<string> cell_set;
		vector<string> cells;
		string s;

		//cin
		while (getline(fin, s))
		{
			vector<string> raw_tokens = Common::get_tokens(s);
			vector<string> tokens;
			for (string t : raw_tokens)
			{
				bool contain_alpha = false;
				for (auto i = 0; i < t.size(); i ++)
					if (isalpha(t[i]))
						contain_alpha = true;
				if (! contain_alpha)
					continue;
				tokens.push_back(t);
			}
			string concat = "";
			for (string t : tokens)
				concat += t + " ";

			sort(tokens.begin(), tokens.end());
			string sort_concat = "";
			for (string t : tokens)
				sort_concat += t + " ";
			if (! cell_set.count(sort_concat))
				cell_set.insert(sort_concat), cells.push_back(concat);
		}

		//output
		full_file_name = "data/" + file_name + ".txt";
		ofstream fout1(full_file_name.c_str());
		for (string t : cells)
			fout1 << t << endl;
		fout1.close();

		full_file_name = "data/" + file_name + "_weights.txt";
		ofstream fout2(full_file_name.c_str());
		for (auto i = 0; i < cells.size(); i ++)
			fout2 << 1 << endl;
		fout2.close();
	}
}

void Exp::check()
{
	string folder = "exp/measure/";
	string files[] = {"area"};
	string methods[] = {"sim", "sigmod"};
	set<pair<string, string>> str_pairs;
	for (string file : files)
		for (string method : methods)
		{
			string file_name = folder + file + "/" + method + ".log";
			ifstream fin(file_name.c_str());

			string s1, s2, ss;
			getline(fin, ss);
			int n = atoi(ss.c_str());

			for (auto j = 0; j < n; j ++)
			{
				getline(fin, s1);
				getline(fin, s2);
				getline(fin, ss);
				double sim = atof(ss.c_str());
				getline(fin, ss);
				if (sim < 0.7)
					continue;
				if (s1.find("new orleans") != string::npos || s2.find("new orleans") != string::npos)
					continue;
				if (s1 > s2)
					swap(s1, s2);
				str_pairs.insert(make_pair(s1, s2));
			}
		}

	vector<pair<string, string>> str_pairs_vector;
	for (auto cp : str_pairs)
		str_pairs_vector.push_back(cp);

	random_shuffle(str_pairs_vector.begin(), str_pairs_vector.end());
	for (auto i = 0; i < str_pairs_vector.size() && i < 100000; i ++)
		cout << str_pairs_vector[i].first << endl << str_pairs_vector[i].second << endl << endl;
}

void Exp::check2()
{
	string file_name1 = "data/dept_names/sim_string_sim.txt";
	string file_name2 = "data/dept_names/sim_string_sigmod13.txt";
	ifstream fin1(file_name1.c_str());
	ifstream fin2(file_name2.c_str());
	vector<pair<string, string>> p1, p2;
	string s1, s2, b;

	while (getline(fin1, s1))
	{
		getline(fin1, s2);
		getline(fin1, b);
		getline(fin1, b);
		if (s1 > s2)
			swap(s1, s2);
		p1.emplace_back(s1, s2);
	}
	while (getline(fin2, s1))
	{
		getline(fin2, s2);
		getline(fin2, b);
		getline(fin2, b);
		if (s1 > s2)
			swap(s1, s2);
		p2.emplace_back(s1, s2);
	}

	for (auto cp : p2)
	{
		bool contain = false;
		for (auto cp2 : p1)
			if (cp == cp2)
				contain = true;
		if (! contain)
			cout << cp.first << endl << cp.second << endl << endl;
	}
}

void Exp::runSolver()
{
	for (string f : file_names)
	{
		for (auto i = 0; i < 10; i ++)
			cout << endl;
		cout << f << " : " << endl << endl;
		Solver *solver = new Solver(f);
		delete solver;
	}
}
void Exp::varyDictionary()
{
	Common::set_default();
	Common::JAC_THRESHOLD = 0.7;
	Common::MEASURE = 0;
/*
	//vldb 09, jac threshold = 0.5
	for (auto i = 0; i < 30; i ++)
		cout << endl;
	cout << "--------------------------" << endl;
	cout << "VLDB09 dictionary, jac = 0.5" << endl;
	cout << "--------------------------" << endl << endl;
	Common::DICTIONARY = 1;
	Common::VLDB09_JAC_THRESHOLD = 0.5;
	runSolver();

	//vldb 09, jac threshold = 0.75
	for (auto i = 0; i < 30; i ++)
		cout << endl;
	cout << "--------------------------" << endl;
	cout << "VLDB09 dictionary, jac = 0.75" << endl;
	cout << "--------------------------" << endl << endl;
	Common::DICTIONARY = 1;
	Common::VLDB09_JAC_THRESHOLD = 0.75;
	runSolver();
*/
	//lcs, delta = 0
	for (auto i = 0; i < 30; i ++)
		cout << endl;
	cout << "--------------------------" << endl;
	cout << "LCS dictionary, delta = 0" << endl;
	cout << "--------------------------" << endl << endl;
	Common::DICTIONARY = 0;
	Common::ENABLE_DELTA = false;
	runSolver();

	//lcs, delta = 1
	for (auto i = 0; i < 30; i ++)
		cout << endl;
	cout << "--------------------------" << endl;
	cout << "LCS dictionary, delta = 1" << endl;
	cout << "--------------------------" << endl << endl;
	Common::DICTIONARY = 0;
	Common::ENABLE_DELTA = true;
	runSolver();
}

void Exp::varyMeasure()
{
	Common::set_default();
	Common::DICTIONARY = 0;
	Common::ENABLE_DELTA = false;
	Common::JAC_THRESHOLD = 0.65;

	//sigmod 13
	for (auto i = 0; i < 30; i ++)
		cout << endl;
	cout << "--------------------------" << endl;
	cout << "SIGMOD 13 measure:" << endl;
	cout << "--------------------------" << endl << endl;
	Common::MEASURE = 1;
	runSolver();

	//our measure
	for (auto i = 0; i < 30; i ++)
		cout << endl;
	cout << "--------------------------" << endl;
	cout << "Our Sim measure:" << endl;
	cout << "--------------------------" << endl << endl;
	Common::MEASURE = 0;
	runSolver();

	//Jaccard
	for (auto i = 0; i < 30; i ++)
		cout << endl;
	cout << "--------------------------" << endl;
	cout << "Simple Jaccard:" << endl;
	cout << "--------------------------" << endl;
	for (string f : file_names)
	{
		for (auto i = 0; i < 10; i ++)
			cout << endl;
		cout << f << " : " << endl << endl;

		vector<string> cells;
		ifstream fin1(f.c_str());
		for (string cell; getline(fin1, cell); )
			cells.push_back(cell);
		JaccardJoiner *jacJoiner = new JaccardJoiner(vector<t_rule>(), cells, Common::JAC_THRESHOLD);
		vector<pair<double, pair<string, string>>> joinedStringPairs;
		joinedStringPairs = jacJoiner->getJoinedStringPairs();

		cout << joinedStringPairs.size() << endl;
		sort(joinedStringPairs.begin(), joinedStringPairs.end());
		for (auto cp : joinedStringPairs)
			cout << cp.second.first << endl << cp.second.second << endl << cp.first << endl << endl;
		delete jacJoiner;
	}
}

void Exp::varyThreshold()
{
	Common::set_default();
	Common::DICTIONARY = 0;
	Common::ENABLE_DELTA = false;
	Common::DO_JOIN = false;

	//vary threshold
	for (Common::JAC_THRESHOLD = 0.7; Common::JAC_THRESHOLD <= 0.9; Common::JAC_THRESHOLD += 0.1)
	{
		//sigmod 13
		for (auto i = 0; i < 30; i ++)
			cout << endl;
		Common::MEASURE = 1;
		cout << "--------------------------" << endl;
		cout << "SIGMOD 13, JAC_THRESHOLD = " << Common::JAC_THRESHOLD << " :" << endl;
		cout << "--------------------------" << endl;

		//vary datasets
		for (string f : file_names)
		{
			for (auto i = 0; i < 10; i ++)
				cout << endl;
			cout << f << " : " << endl << endl;

			vector<string> cells;
			ifstream fin1(f.c_str());
			for (string cell; getline(fin1, cell); )
				cells.push_back(cell);
			fin1.close();

			RuleGenerator *ruleGenerator = new BadBoy(cells);
			vector<t_rule> rules = ruleGenerator->gen_rules();
			for (int i = 0, n = (int) rules.size(); i < n; i ++)
				rules.emplace_back(make_pair(rules[i].second, rules[i].first));

			Joiner *joiner = new PolynomialJoiner(rules, cells);
			joiner->getJoinedStringPairs();
			delete ruleGenerator;
			delete joiner;
		}

		//our sim measure
		for (auto i = 0; i < 30; i ++)
			cout << endl;
		Common::MEASURE = 0;
		cout << "--------------------------" << endl;
		cout << "Sim, JAC_THRESHOLD = " << Common::JAC_THRESHOLD << " :" << endl;
		cout << "--------------------------" << endl;

		//vary datasets
		for (string f : file_names)
		{
			for (auto i = 0; i < 10; i ++)
				cout << endl;
			cout << f << " : " << endl << endl;

			vector<string> cells;
			ifstream fin1(f.c_str());
			for (string cell; getline(fin1, cell); )
				cells.push_back(cell);
			fin1.close();

			RuleGenerator *ruleGenerator = new BadBoy(cells);
			vector<t_rule> rules = ruleGenerator->gen_rules();
			for (int i = 0, n = (int) rules.size(); i < n; i ++)
				rules.emplace_back(make_pair(rules[i].second, rules[i].first));


			Joiner *joiner = new PolynomialJoiner(rules, cells);
			joiner->getJoinedStringPairs();
			delete ruleGenerator;
			delete joiner;
		}
	}
}

void Exp::genDirty()
{
	string folder = "exp/measure/";
	string files[] = {"area"};
	string methods[] = {"sim", "sigmod"};

	for (string file : files)
	{
		unordered_set<string> left, right;
		string file_name = "exp/quality_data/" + file + "/match.txt";
		ifstream fin1(file_name.c_str());
		string s1, s2, ss;
		while (getline(fin1, s1))
		{
			getline(fin1, s2);
			getline(fin1, ss);
			if (s1.back() != ' ')
				s1 += " ";
			if (s2.back() != ' ')
				s2 += " ";
			left.insert(s1);
			right.insert(s2);
		}
		fin1.close();

		unordered_set<string> dirty_record_set;
		for (string method : methods)
		{
			file_name = folder + file + "/" + method + ".log";
			ifstream fin(file_name.c_str());

			getline(fin, ss);
			int n = atoi(ss.c_str());
			for (auto j = 0; j < n; j ++)
			{
				getline(fin, s1);
				getline(fin, s2);
				getline(fin, ss);
				double sim = atof(ss.c_str());
				getline(fin, ss);

				if (left.count(s1))
					if (s2.find("new orleans") == string::npos)
						dirty_record_set.insert(s2);
				if (left.count(s2))
					if (s1.find("new orleans") == string::npos)
						dirty_record_set.insert(s1);
			}
		}

		vector<string> dirty_records;
		for (auto s : dirty_record_set)
			dirty_records.push_back(s);
		random_shuffle(dirty_records.begin(), dirty_records.end());
		for (int i = 0; i < 100; i ++)
			cout << dirty_records[i] << endl;
	}
}

void Exp::calculatePRF()
{
	string files[] = {"course", "dept", "area"};
	string methods[] = {"sim", "jaccard", "sigmod"};

	for (string file : files)
	{
		cout << file << " : " << endl << endl;
		unordered_set<string> left, right;
		set<pair<string, string>> true_pairs;
		string file_name, s1, s2, ss;

		//match.txt
		file_name = "exp/quality_data/" + file + "/match.txt";
		ifstream fin1(file_name.c_str());
		while (getline(fin1, s1))
		{
			getline(fin1, s2);
			getline(fin1, ss);
			if (s1.back() != ' ')
				s1 += " ";
			if (s2.back() != ' ')
				s2 += " ";
			if (left.count(s1))
				cout << s1 << endl;
			left.insert(s1);
			if (right.count(s2))
				cout << s2 << endl;
			right.insert(s2);
			true_pairs.insert(make_pair(s1, s2));
		}
		fin1.close();

		//dirty.txt
		file_name = "exp/quality_data/" + file + "/dirty.txt";
		ifstream fin2(file_name.c_str());
		while (getline(fin2, s1))
		{
			if (s1.back() != ' ')
				s1 += " ";
			if (right.count(s1))
				cout << s1 << endl;
			right.insert(s1);
		}

		//check duplicates
		cout << left.size() << " " << right.size() << endl;
		if (left.size() != 100 || right.size() != 200)
			cout << "There is duplicates !!!" << endl;

		//precision & recall
		for (string method : methods)
		{
			for (double th = 0.7; th <= 0.9; th += 0.1)
			{
				cout << "threshold : " << th << endl;
				string log_file_name = "exp/measure/" + file + "/" + method + ".log";
				ifstream fin3(log_file_name.c_str());
				getline(fin3, ss);
				int n = atoi(ss.c_str());
				int correct = 0;
				int total = 0;

				for (int i = 0; i < n; i ++)
				{
					double sim;
					getline(fin3, s1);
					getline(fin3, s2);
					getline(fin3, ss);
					sim = atof(ss.c_str());
					getline(fin3, ss);
					if (sim < th)
						continue;

					if ((left.count(s1) && right.count(s2)) ||
						(left.count(s2) && right.count(s1)))
					{
						total ++;
						if (true_pairs.count(make_pair(s1, s2)) ||
							true_pairs.count(make_pair(s2, s1)))
							correct ++;
					}
				}

//				cout << method << " : " << endl << "Presicion : " << correct << " / " << total << endl;
//				cout << "Recall : " << correct << " / " << true_pairs.size() << endl;

				cout << method << " : " << endl;
				double p = correct / (double) total;
				double r = correct / (double) true_pairs.size();
				cout << "Precision : " << p << endl;
				cout << "Recall : " << r << endl;
				cout << "F1 Score: " << (p + r > 0 ? 2 * p * r / (p + r) : 0) << endl << endl;

			}
		}
	}
}

void Exp::dictionary_scale()
{
	Common::set_default();
	Common::DICTIONARY = 0;

	RuleGenerator *ruleGenerator;
	for (string f : file_names)
	{
		cout << f << endl << endl;
		vector<string> cells;
		ifstream fin1(f.c_str());
		for (string cell; getline(fin1, cell); )
			cells.push_back(cell);
		random_shuffle(cells.begin(), cells.end());
		int N = (int) cells.size();
		int n = N / 4;
		fin1.close();

		cout << "\t delta = 0 : " << endl << endl;
		Common::ENABLE_DELTA = false;

		for (int i = 1; i <= 4; i ++)
		{
			vector<string> cells_partial;
			for (auto j = 0; j < n * i; j ++)
				cells_partial.push_back(cells[j]);
			struct timeval t1, t2;
			gettimeofday(&t1, NULL);
			ruleGenerator = new FastLCS(cells_partial);
			ruleGenerator->gen_rules();
			gettimeofday(&t2, NULL);
			double elapsedTime = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) / 1000000.0;
			cout << "\t\t i = " << i << " : " << elapsedTime << "s." << endl << endl;
			delete ruleGenerator;
		}

		cout << "\t delta = 1 : " << endl << endl;
		Common::ENABLE_DELTA = true;

		for (int i = 1; i <= 4; i ++)
		{
			vector<string> cells_partial;
			for (auto j = 0; j < n * i; j ++)
				cells_partial.push_back(cells[j]);
			struct timeval t1, t2;
			gettimeofday(&t1, NULL);
			ruleGenerator = new FastLCS(cells_partial);
			ruleGenerator->gen_rules();
			gettimeofday(&t2, NULL);
			double elapsedTime = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) / 1000000.0;
			cout << "\t\t i = " << i << " : " << elapsedTime << "s." << endl << endl;
			delete ruleGenerator;
		}
	}
}
