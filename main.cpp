#include "Common.h"
#include "Solver/Solver.h"

using namespace std;

int main()
{
	struct timeval t1, t2;
	gettimeofday(&t1, NULL);
	Solver *solver = new Solver("dept_names/dept_names.txt", "dept_names/dept_names_weights.txt");
//	Solver *solver = new Solver("course_names/course_names.txt", "course_names/course_names.txt");
	gettimeofday(&t2, NULL);
	double elapsedTime = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) / 1000000.0;
	cout << elapsedTime << "s." << endl;

	return 0;
}
