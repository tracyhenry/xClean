#include "Common.h"
#include "Exp.h"
#include "Solver/Solver.h"

using namespace std;

int main()
{
//	Solver *solver = new Solver("data/dept_names/dept_names.txt");
//	Solver *solver = new Solver("data/course_names/course_names.txt");
//	Solver *solver = new Solver("data/area_names/area_names.txt");

//	Exp::preprocess();
//	Exp::check();
//	Exp::varyDictionary();
//	Exp::varyThreshold();
//	Exp::check();
//	Exp::calculatePRF();
//	Exp::check();
//	Exp::genDirty();
	Exp::dictionary_scale();
	return 0;
}
