#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <iostream>
#include <ctime> // time
#include <cstdlib> // srand, rand
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

#define SIZE 1000

class Benchmark
{
	public:
		Benchmark();
		~Benchmark();

		void VectorBenchmarking();

	private:
		void Benchmarking(std::string test_name, void (Benchmark::*f)());
		void Benchmarking(std::string test_name,
							void (Benchmark::*f)(PRE::vector<int> *vec));
		void VectorDefaultConstructor();
		void VectorArgConstructor();
		void VectorIteratorConstructor();
		void VectorCopyConstructor();
		void VectorCopyOperator();
		void VectorAssign();
		void VectorAssignIterator();
		void VectorGetAllocator();
		void VectorAt();
		void VectorAccessOperator();
		void VectorFront();
		void VectorBack();
		void VectorData();
		void VectorBegin();
		void VectorEnd();
		void VectorRbegin();
		void VectorRend();
		void VectorEmpty();
		void VectorSize();
		void VectorMaxSize();
		void VectorReserve();
		void VectorCapacity();
		void VectorClear(PRE::vector<int> *vec);
		void VectorInsert();
		void VectorInserts();
		void VectorInsertIterator();
		void VectorErase(PRE::vector<int> *vec);
		void VectorEraseIterator(PRE::vector<int> *vec);
		void VectorPushBack();
		void VectorPopBack();
		void VectorResize();
		void VectorSwap();
		void VectorEqualOperator();
		void VectorNotEqualOperator();
		void VectorLessOperator();
		void VectorLessEqualOperator();
		void VectorGreaterOperator();
		void VectorGreaterEqualOperator();
		void VectorNonMemberSwap();

		PRE::vector<int> v_;
		PRE::vector<int> v2_;
		const PRE::vector<int>& cv_;
		const PRE::vector<int>& cv2_;
		PRE::vector<int> assign_v_;
		PRE::vector<int> reserve_v_;
		PRE::vector<int> insert_v_;
		PRE::vector<int> erase_v_;
		PRE::vector<int> push_back_v_;
		PRE::vector<int> resize_v_;
		PRE::vector<int> swap1_v_;
		PRE::vector<int> swap2_v_;

};

#endif // BENCHMARK_HPP
