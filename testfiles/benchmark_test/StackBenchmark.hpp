#ifndef STACKBENCHMARK_HPP
#define STACKBENCHMARK_HPP

#include "benchmark_test.hpp"

class StackBenchmark
{
public:
	StackBenchmark();
	~StackBenchmark();

	void StackBenchmarking();

private:
	void Benchmarking(std::string test_name, void (StackBenchmark::*f)());
	void StackDefaultConstructor();
	void StackCopyConstructor();
	void StackCopyOperator();
	void StackTop();
	void StackEmpty();
	void StackSize();
	void StackPush();
	void StackPop();
	void StackEqualOperator();
	void StackNotEqualOperator();
	void StackLessOperator();
	void StackLessEqualOperator();
	void StackGreaterOperator();
	void StackGreaterEqualOperator();

	PRE::stack<int> s_;
	PRE::stack<int> s2_;
	const PRE::stack<int> &cs_;
	const PRE::stack<int> &cs2_;
	PRE::stack<int> push_pop_s_;

}; // class StackBenchmark

#endif // STACKBENCHMARK_HPP
