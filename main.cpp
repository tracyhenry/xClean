#include "Common.h"
#include "Solver.h"

using namespace std;

int main()
{
	Solver *solver = new Solver("dept_names/dept_names.txt", "dept_names/dept_names_weights.txt");

	return 0;
}
