#include "Common.h"
#include "Exp.h"
#include "Solver/Solver.h"

using namespace std;

int main()
{
	Solver *solver = new Solver("data/dept_names/dept_names.txt", "data/dept_names/dept_names_weights.txt");
//	Solver *solver = new Solver("data/course_names/course_names.txt", "data/course_names/course_names_weights.txt");
//	Solver *solver = new Solver("data/area_names/area_names.txt", "data/area_names/area_names_weights.txt");

//	Exp::preprocess();
//	Exp::check();
	return 0;
}
