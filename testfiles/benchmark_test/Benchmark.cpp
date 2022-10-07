#include "Benchmark.hpp"

Benchmark::Benchmark()
{
}

Benchmark::~Benchmark()
{
}

void Benchmark::VectorBenchmarking()
{
	Benchmarking("VectorDefaultConstructor", &Benchmark::VectorDefaultConstructor);
	Benchmarking("VectorArgConstructor", &Benchmark::VectorArgConstructor);
}

void Benchmark::Benchmarking(std::string test_name, void (Benchmark::*f)())
{
	Timer timer;

	for (int i = 0; i < 1000; i++)
	{
		timer.start();
		(this->*f)();
		timer.stop();
	}
	std::cout << test_name << "," << timer.getElapsedTime() << std::endl;
}

void Benchmark::VectorDefaultConstructor()
{
	PRE::vector<int> v;
}

void Benchmark::VectorArgConstructor()
{
	PRE::vector<int> v(1000, 33);
}
