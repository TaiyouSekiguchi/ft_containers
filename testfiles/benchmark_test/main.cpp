#include "Benchmark.hpp"

int main(void)
{
	srand((unsigned int)time(NULL));

	Benchmark bm;

	bm.VectorBenchmarking();

	return (0);
}
