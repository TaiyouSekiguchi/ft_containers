#ifndef STACKBENCHMARK_HPP
#define STACKBENCHMARK_HPP

#include <iostream>
#include <ctime>   // time
#include <cstdlib> // srand, rand
#include "Timer.hpp"

#ifdef FT
#define PRE ft
#include "../../containers/vector.hpp"
#include "../../containers/stack.hpp"
#include "../../containers/map.hpp"
#else
#define PRE std
#include <vector>
#include <stack>
#include <map>
#include <iterator>
#include <utility>
#endif

#define SIZE 1000

class StackBenchmark
{
public:
	StackBenchmark();
	~StackBenchmark();

	void StackBenchmarking();

private:
	void Benchmarking(std::string test_name, void (StackBenchmark::*f)());
	//void Benchmarking(std::string test_name, void (StackBenchmark::*f)(PRE::stack<int> *vec));
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
