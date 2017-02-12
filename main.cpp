#include "Common.h"
#include "Exp.h"
#include "Solver/Solver.h"

using namespace std;

int main()
{

	struct timeval t1, t2;
	gettimeofday(&t1, NULL);
	Solver *solver = new Solver("data/dept_names/dept_names.txt", "data/dept_names/dept_names_weights.txt");
//	Solver *solver = new Solver("data/course_names/course_names.txt", "data/course_names/course_names_weights.txt");
//	Solver *solver = new Solver("data/area_names/area_names.txt", "data/area_names/area_names_weights.txt");
	gettimeofday(&t2, NULL);
	double elapsedTime = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) / 1000000.0;
	cout << elapsedTime << "s." << endl;

//	Exp::preprocess();
	return 0;
}
