#include "StackBenchmark.hpp"

StackBenchmark::StackBenchmark()
	: cs_(s_), cs2_(s2_)
{
	for (int i = 0; i < SIZE; i++)
		s_.push(42);
	for (int i = 0; i < SIZE * 2; i++)
		s2_.push(42);
}

StackBenchmark::~StackBenchmark()
{
}

void StackBenchmark::StackBenchmarking()
{
	Benchmarking("StackDefaultConstructor", &StackBenchmark::StackDefaultConstructor);
	Benchmarking("StackCopyConstructor", &StackBenchmark::StackCopyConstructor);
	Benchmarking("StackCopyOperator", &StackBenchmark::StackCopyOperator);
	Benchmarking("StackTop", &StackBenchmark::StackTop);
	Benchmarking("StackEmpty", &StackBenchmark::StackEmpty);
	Benchmarking("StackSize", &StackBenchmark::StackSize);
	Benchmarking("StackPush", &StackBenchmark::StackPush);
	Benchmarking("StackPop", &StackBenchmark::StackPop);
	Benchmarking("StackEqualOperator", &StackBenchmark::StackEqualOperator);
	Benchmarking("StackNotEqualOperator", &StackBenchmark::StackNotEqualOperator);
	Benchmarking("StackLessOperator", &StackBenchmark::StackLessOperator);
	Benchmarking("StackLessEqualOperator", &StackBenchmark::StackLessEqualOperator);
	Benchmarking("StackGreaterOperator", &StackBenchmark::StackGreaterOperator);
	Benchmarking("StackGreaterEqualOperator", &StackBenchmark::StackGreaterEqualOperator);
}

void StackBenchmark::Benchmarking(std::string test_name, void (StackBenchmark::*f)())
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

void StackBenchmark::StackDefaultConstructor()		{ PRE::stack<int> s; }
void StackBenchmark::StackCopyConstructor()			{ PRE::stack<int> s(s_); }
void StackBenchmark::StackCopyOperator()			{ PRE::stack<int> s; s = cs_; }
void StackBenchmark::StackTop()						{ s_.top(); }
void StackBenchmark::StackEmpty()					{ s_.empty(); }
void StackBenchmark::StackSize()					{ s_.size(); }
void StackBenchmark::StackPush() 					{ push_pop_s_.push(42); }
void StackBenchmark::StackPop() 					{ push_pop_s_.pop(); }
void StackBenchmark::StackEqualOperator()			{ (void)(cs_ == cs2_); }
void StackBenchmark::StackNotEqualOperator()		{ (void)(cs_ != cs2_); }
void StackBenchmark::StackLessOperator()			{ (void)(cs_ < cs2_); }
void StackBenchmark::StackLessEqualOperator()		{ (void)(cs_ <= cs2_); }
void StackBenchmark::StackGreaterOperator() 		{ (void)(cs_ > cs2_); }
void StackBenchmark::StackGreaterEqualOperator()	{ (void)(cs_ > cs2_); }
