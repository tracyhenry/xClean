//
// Created by Wenbo Tao on 2/11/17.
//

#include "Exp.h"
using namespace std;

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
	string file_name1 = "data/dept_names/sim_string_sim.txt";
	string file_name2 = "data/dept_names/sim_string_jacct.txt";
	ifstream fin1(file_name1.c_str());
	ifstream fin2(file_name2.c_str());
	vector<pair<string, string>> p1, p2;
	string s1, s2, b;

	while (getline(fin1, s1))
	{
		getline(fin1, s2);
		getline(fin1, b);
		if (s1 > s2)
			swap(s1, s2);
		p1.emplace_back(s1, s2);
	}
	while (getline(fin2, s1))
	{
		getline(fin2, s2);
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