#include "MapBenchmark.hpp"

static int RandomNumber() { return (rand() % SIZE); }
static int RandomInsertNumber() { return (rand() % ( SIZE * 10)); }

MapBenchmark::MapBenchmark()
	: cm_(m_), cm2_(m2_)
{
	for (int i = 0; i < SIZE; i++)
		m_[i] = i;
	for (int i = 0; i < SIZE * 2; i++)
		m2_[i] = i;
	erase_m_ = m_;
	swap_m1_ = m_;
	swap_m2_ = m2_;
}

MapBenchmark::~MapBenchmark()
{
}

void MapBenchmark::MapBenchmarking()
{
	Benchmarking("MapDefaultConstructor", &MapBenchmark::MapDefaultConstructor);
	Benchmarking("MapIteratorConstructor", &MapBenchmark::MapIteratorConstructor);
	Benchmarking("MapCopyConstructor", &MapBenchmark::MapCopyConstructor);
	Benchmarking("MapCopyOperator", &MapBenchmark::MapCopyOperator);
	Benchmarking("MapGetAllocator", &MapBenchmark::MapGetAllocator);
	Benchmarking("MapAccessOperator", &MapBenchmark::MapAccessOperator);
	Benchmarking("MapBegin", &MapBenchmark::MapBegin);
	Benchmarking("MapEnd", &MapBenchmark::MapEnd);
	Benchmarking("MapRbegin", &MapBenchmark::MapRbegin);
	Benchmarking("MapRend", &MapBenchmark::MapRend);
	Benchmarking("MapEmpty", &MapBenchmark::MapEmpty);
	Benchmarking("MapSize", &MapBenchmark::MapSize);
	Benchmarking("MapMaxSize", &MapBenchmark::MapMaxSize);
	Benchmarking("MapClear", &MapBenchmark::MapClear);
	Benchmarking("MapInsert", &MapBenchmark::MapInsert);
	Benchmarking("MapInserts", &MapBenchmark::MapInserts);
	Benchmarking2("MapInsertIterator", &MapBenchmark::MapInsertIterator);
	Benchmarking("MapInsertErase", &MapBenchmark::MapErase);
	Benchmarking("MapInsertEraseIterator", &MapBenchmark::MapEraseIterator);
	Benchmarking("MapSwap", &MapBenchmark::MapSwap);
	Benchmarking("MapCount", &MapBenchmark::MapCount);
	Benchmarking("MapFind", &MapBenchmark::MapFind);
	Benchmarking("MapEqualRange", &MapBenchmark::MapEqualRange);
	Benchmarking("MapLowerBound", &MapBenchmark::MapLowerBound);
	Benchmarking("MapUpperBound", &MapBenchmark::MapUpperBound);
	Benchmarking("MapKeyComp", &MapBenchmark::MapKeyComp);
	Benchmarking("MapValueComp", &MapBenchmark::MapValueComp);
	Benchmarking("MapEqualOperator", &MapBenchmark::MapEqualOperator);
	Benchmarking("MapNotEqualOperator", &MapBenchmark::MapNotEqualOperator);
	Benchmarking("MapLessOperator", &MapBenchmark::MapLessOperator);
	Benchmarking("MapLessEqualOperator", &MapBenchmark::MapLessEqualOperator);
	Benchmarking("MapGreaterOperator", &MapBenchmark::MapGreaterOperator);
	Benchmarking("MapGreaterEqualOperator", &MapBenchmark::MapGreaterEqualOperator);
	Benchmarking("MapNonMemberSwap", &MapBenchmark::MapNonMemberSwap);
}

void MapBenchmark::Benchmarking(std::string test_name, void (MapBenchmark::*f)())
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

void MapBenchmark::Benchmarking(std::string test_name,
									 void (MapBenchmark::*f)(PRE::map<int, int> *map))
{
	Timer timer;

	for (int i = 0; i < 1000; i++)
	{
		PRE::map<int, int> tmp(cm_);

		timer.start();
		(this->*f)(&tmp);
		timer.stop();
	}
	std::cout << test_name << "," << timer.getElapsedTime() << std::endl;
}

void MapBenchmark::Benchmarking2(std::string test_name,
									 void (MapBenchmark::*f)(PRE::map<int, int> *map))
{
	Timer timer;

	for (int i = 0; i < 1000; i++)
	{
		PRE::map<int, int> tmp;

		timer.start();
		(this->*f)(&tmp);
		timer.stop();
	}
	std::cout << test_name << "," << timer.getElapsedTime() << std::endl;
}

void MapBenchmark::MapDefaultConstructor() { PRE::map<int, int> m; }
void MapBenchmark::MapIteratorConstructor() { PRE::map<int, int> m(m_.begin(), m_.end()); }
void MapBenchmark::MapCopyConstructor() { PRE::map<int, int> m(m_); }
void MapBenchmark::MapCopyOperator() { PRE::map<int, int> m; m = cm_; }
void MapBenchmark::MapGetAllocator() { m_.get_allocator(); }
void MapBenchmark::MapAccessOperator() { m_[RandomNumber()]; }
void MapBenchmark::MapBegin() { m_.begin(); }
void MapBenchmark::MapEnd() { m_.end(); }
void MapBenchmark::MapRbegin() { m_.rbegin(); }
void MapBenchmark::MapRend() { m_.rend(); }
void MapBenchmark::MapEmpty() { m_.empty(); }
void MapBenchmark::MapSize() { m_.size(); }
void MapBenchmark::MapMaxSize() { m_.max_size(); }
void MapBenchmark::MapClear(PRE::map<int, int> *map) { map->clear(); }
void MapBenchmark::MapInsert()
{
	int num = RandomInsertNumber();
	insert_m1_.insert(PRE::make_pair(num, num));
}
void MapBenchmark::MapInserts()
{
	int num = RandomInsertNumber();
	insert_m2_.insert(insert_m2_.lower_bound(num),PRE::make_pair(num, num));
}
void MapBenchmark::MapInsertIterator(PRE::map<int, int> *map)
{
	map->insert(m_.begin(), m_.end());
}
void MapBenchmark::MapErase(PRE::map<int, int> *map)
{
	map->erase(map->find(RandomNumber()));
}
void MapBenchmark::MapEraseIterator(PRE::map<int, int> *map)
{
	map->erase(map->begin(), map->end());
}
void MapBenchmark::MapSwap() { swap_m1_.swap(swap_m2_); }
void MapBenchmark::MapCount() { m_.count(RandomNumber()); }
void MapBenchmark::MapFind() { m_.find(RandomNumber()); }
void MapBenchmark::MapEqualRange() { m_.equal_range(RandomNumber()); }
void MapBenchmark::MapLowerBound() { m_.lower_bound(RandomNumber()); }
void MapBenchmark::MapUpperBound() { m_.upper_bound(RandomNumber()); }
void MapBenchmark::MapKeyComp() { m_.key_comp(); }
void MapBenchmark::MapValueComp() { m_.value_comp(); }
void MapBenchmark::MapEqualOperator() { (void)(cm_ == cm2_); }
void MapBenchmark::MapNotEqualOperator() { (void)(cm_ != cm2_); }
void MapBenchmark::MapLessOperator() { (void)(cm_ < cm2_); }
void MapBenchmark::MapLessEqualOperator() { (void)(cm_ <= cm2_); }
void MapBenchmark::MapGreaterOperator() { (void)(cm_ > cm2_); }
void MapBenchmark::MapGreaterEqualOperator() { (void)(cm_ > cm2_); }
void MapBenchmark::MapNonMemberSwap() { swap(swap_m1_, swap_m2_); }
