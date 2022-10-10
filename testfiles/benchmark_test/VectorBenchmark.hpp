#ifndef VECTORBENCHMARK_HPP
#define VECTORBENCHMARK_HPP

#include "benchmark_test.hpp"

class VectorBenchmark
{
	public:
		VectorBenchmark();
		~VectorBenchmark();

		void VectorBenchmarking();

	private:
		void Benchmarking(std::string test_name, void (VectorBenchmark::*f)());
		void Benchmarking(std::string test_name,
							void (VectorBenchmark::*f)(PRE::vector<int> *vec));
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
}; // class VectorBenchmark

#endif // VECTORBENCHMARK_HPP
