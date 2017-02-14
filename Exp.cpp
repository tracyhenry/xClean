//
// Created by Wenbo Tao on 2/11/17.
//

#include "Exp.h"
#include "Joiner/Joiner.h"
#include "Joiner/PolynomialJoiner.h"
#include "Solver/Solver.h"
#include "Joiner/JaccardJoiner.h"

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
	string file_name1 = "data/dept_names/sim_string_sigmod13.txt";
	ifstream fin1(file_name1.c_str());
	vector<pair<string, string>> p1;
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

	srand(time(0));
	cout << p1.size() << endl;
	for (auto i = 0; i < 50; i ++)
	{
		int x = rand() % p1.size();
		cout << p1[x].first << endl << p1[x].second << endl << endl;
	}
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
		if (f != "data/area_names/area_names.txt")
			continue;
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
	Common::JAC_THRESHOLD = 0.65;
	Common::MEASURE = 0;

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
