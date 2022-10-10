#ifndef MAPBENCHMARK_HPP
#define MAPBENCHMARK_HPP

#include "benchmark_test.hpp"

class MapBenchmark
{
	public:
		MapBenchmark();
		~MapBenchmark();

		void MapBenchmarking();

	private:
		void MapBenchmarking(std::string test_name, void (MapBenchmark::*f)());
		void MapBenchmarking(std::string test_name,
								void (MapBenchmark::*f)(PRE::map<int, int> *vec));
		void MapBenchmarking2(std::string test_name,
								void (MapBenchmark::*f)(PRE::map<int, int> *vec));
		void MapDefaultConstructor();
		void MapIteratorConstructor();
		void MapCopyConstructor();
		void MapCopyOperator();
		void MapGetAllocator();
		void MapAccessOperator();
		void MapBegin();
		void MapEnd();
		void MapRbegin();
		void MapRend();
		void MapEmpty();
		void MapSize();
		void MapMaxSize();
		void MapClear(PRE::map<int, int> *vec);
		void MapInsert();
		void MapInserts();
		void MapInsertIterator(PRE::map<int, int> *vec);
		void MapErase(PRE::map<int, int> *vec);
		void MapEraseIterator(PRE::map<int, int> *vec);
		void MapSwap();
		void MapCount();
		void MapFind();
		void MapEqualRange();
		void MapLowerBound();
		void MapUpperBound();
		void MapKeyComp();
		void MapValueComp();
		void MapEqualOperator();
		void MapNotEqualOperator();
		void MapLessOperator();
		void MapLessEqualOperator();
		void MapGreaterOperator();
		void MapGreaterEqualOperator();
		void MapNonMemberSwap();

		PRE::map<int, int> m_;
		PRE::map<int, int> m2_;
		const PRE::map<int, int> &cm_;
		const PRE::map<int, int> &cm2_;
		PRE::map<int, int> insert_m1_;
		PRE::map<int, int> insert_m2_;
		PRE::map<int, int> erase_m_;

		PRE::map<int, int> swap_m1_;
		PRE::map<int, int> swap_m2_;


};

#endif // MAPBENCHMARK_HPP
