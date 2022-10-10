#include "VectorBenchmark.hpp"
#include "StackBenchmark.hpp"

int main(void)
{
	srand((unsigned int)time(NULL));

	VectorBenchmark vbm;
	// StackBenchmark sbm;

	vbm.VectorBenchmarking();
	// sbm.StackBenchmarking();

	return (0);
}
