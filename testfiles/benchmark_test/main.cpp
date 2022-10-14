#include "VectorBenchmark.hpp"
#include "StackBenchmark.hpp"
#include "MapBenchmark.hpp"

int main(void)
{
	srand((unsigned int)time(NULL));

	VectorBenchmark		vbm;
	StackBenchmark		sbm;
	MapBenchmark		mbm;

	vbm.VectorBenchmarking();
	sbm.StackBenchmarking();
	mbm.MapBenchmarking();

	return (0);
}
