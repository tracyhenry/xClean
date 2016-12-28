#include "Common.h"
#include "Solver/Solver.h"

using namespace std;

int main()
{
	Solver *solver = new Solver("dept_names/dept_names.txt", "dept_names/dept_names_weights.txt");
//	Solver *solver = new Solver("course_names/course_names.txt", "course_names/course_names.txt");

	return 0;
}
