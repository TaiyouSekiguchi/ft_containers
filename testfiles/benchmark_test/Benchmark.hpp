#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <iostream>
#include "Timer.hpp"

#ifdef FT
# define PRE ft
# include "../../containers/vector.hpp"
# include "../../containers/stack.hpp"
# include "../../containers/map.hpp"
#else
# define PRE std
# include <vector>
# include <stack>
# include <map>
# include <iterator>
# include <utility>
#endif

class Benchmark
{
	public:
		Benchmark();
		~Benchmark();

		void VectorBenchmarking();

	private:
		void Benchmarking(std::string test_name, void (Benchmark::*f)());
		void VectorDefaultConstructor();
		void VectorArgConstructor();
};

#endif // BENCHMARK_HPP
