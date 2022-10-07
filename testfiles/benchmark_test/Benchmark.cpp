#include "Benchmark.hpp"

static int RandomNumber() { return (rand() % SIZE); }

Benchmark::Benchmark()
	: cv_(v_), cv2_(v2_)
{
	for (int i = 0; i < SIZE; i++)
		v_.push_back(42);
	for (int i = 0; i < SIZE * 2; i++)
		v2_.push_back(42);
	insert_v_ = v_;
	erase_v_ = v_;
	swap1_v_ = v_;
	swap2_v_ = v2_;
}

Benchmark::~Benchmark()
{
}

void Benchmark::VectorBenchmarking()
{
	Benchmarking("VectorDefaultConstructor", &Benchmark::VectorDefaultConstructor);
	Benchmarking("VectorArgConstructor", &Benchmark::VectorArgConstructor);
	Benchmarking("VectorIteratorConstructor", &Benchmark::VectorIteratorConstructor);
	Benchmarking("VectorCopyConstructor", &Benchmark::VectorCopyConstructor);
	Benchmarking("VectorCopyOperator", &Benchmark::VectorCopyOperator);
	Benchmarking("VectorAssign", &Benchmark::VectorAssign);
	Benchmarking("VectorAssign", &Benchmark::VectorAssignIterator);
	Benchmarking("VectorGetAllocator", &Benchmark::VectorGetAllocator);
	Benchmarking("VectorAt", &Benchmark::VectorAt);
	Benchmarking("VectorAccessOperator", &Benchmark::VectorAccessOperator);
	Benchmarking("VectorFront", &Benchmark::VectorFront);
	Benchmarking("VectorBack", &Benchmark::VectorBack);
	Benchmarking("VectorData", &Benchmark::VectorData);
	Benchmarking("VectorBegin", &Benchmark::VectorBegin);
	Benchmarking("VectorEnd", &Benchmark::VectorEnd);
	Benchmarking("VectorRbegin", &Benchmark::VectorRbegin);
	Benchmarking("VectorRend", &Benchmark::VectorRend);
	Benchmarking("VectorEmpty", &Benchmark::VectorEmpty);
	Benchmarking("VectorSize", &Benchmark::VectorSize);
	Benchmarking("VectorMaxSize", &Benchmark::VectorMaxSize);
	Benchmarking("VectorReserve", &Benchmark::VectorReserve);
	Benchmarking("VectorCapacity", &Benchmark::VectorCapacity);
	Benchmarking("VectorClear", &Benchmark::VectorClear);
	Benchmarking("VectorInsert", &Benchmark::VectorInsert);
	Benchmarking("VectorInserts", &Benchmark::VectorInserts);
	Benchmarking("VectorInsertIterator", &Benchmark::VectorInsertIterator);
	Benchmarking("VectorInsertErase", &Benchmark::VectorErase);
	Benchmarking("VectorInsertEraseIterator", &Benchmark::VectorEraseIterator);
	Benchmarking("VectorPushBack", &Benchmark::VectorPushBack);
	Benchmarking("VectorPopBack", &Benchmark::VectorPopBack);
	Benchmarking("VectorResize", &Benchmark::VectorResize);
	Benchmarking("VectorSwap", &Benchmark::VectorSwap);
	Benchmarking("VectorEqualOperator", &Benchmark::VectorEqualOperator);
	Benchmarking("VectorNotEqualOperator", &Benchmark::VectorNotEqualOperator);
	Benchmarking("VectorLessOperator", &Benchmark::VectorLessOperator);
	Benchmarking("VectorLessEqualOperator", &Benchmark::VectorLessEqualOperator);
	Benchmarking("VectorGreaterOperator", &Benchmark::VectorGreaterOperator);
	Benchmarking("VectorGreaterEqualOperator", &Benchmark::VectorGreaterEqualOperator);
	Benchmarking("VectorNonMemberSwap", &Benchmark::VectorNonMemberSwap);
}

void Benchmark::Benchmarking(std::string test_name, void (Benchmark::*f)())
{
	Timer timer;

	for (int i = 0; i < SIZE; i++)
	{
		timer.start();
		(this->*f)();
		timer.stop();
	}
	std::cout << test_name << "," << timer.getElapsedTime() << std::endl;
}

void Benchmark::Benchmarking(std::string test_name,
								void (Benchmark::*f)(PRE::vector<int> *vec))
{
	Timer timer;

	for (int i = 0; i < SIZE; i++)
	{
		PRE::vector<int> tmp(SIZE, 33);

		timer.start();
		(this->*f)(&tmp);
		timer.stop();
	}
	std::cout << test_name << "," << timer.getElapsedTime() << std::endl;
}

void Benchmark::VectorDefaultConstructor()			{ PRE::vector<int> v; }
void Benchmark::VectorArgConstructor()				{ PRE::vector<int> v(SIZE, 33); }
void Benchmark::VectorIteratorConstructor()			{ PRE::vector<int> v(v_.begin(), v_.end()); }
void Benchmark::VectorCopyConstructor()				{ PRE::vector<int> v(v_); }
void Benchmark::VectorCopyOperator()				{ PRE::vector<int> v; v = cv_; }
void Benchmark::VectorAssign()						{ assign_v_.assign(SIZE, 42); }
void Benchmark::VectorAssignIterator()				{ assign_v_.assign(v_.begin(), v_.end()); }
void Benchmark::VectorGetAllocator()				{ v_.get_allocator(); }
void Benchmark::VectorAt()							{ v_.at(RandomNumber()); }
void Benchmark::VectorAccessOperator()				{ v_[RandomNumber()]; }
void Benchmark::VectorFront()						{ v_.front(); }
void Benchmark::VectorBack()						{ v_.back(); }
void Benchmark::VectorData()						{ v_.data(); }
void Benchmark::VectorBegin()						{ v_.begin(); }
void Benchmark::VectorEnd()							{ v_.end(); }
void Benchmark::VectorRbegin()						{ v_.rbegin(); }
void Benchmark::VectorRend()						{ v_.rend(); }
void Benchmark::VectorEmpty()						{ v_.empty(); }
void Benchmark::VectorSize()						{ v_.size(); }
void Benchmark::VectorMaxSize()						{ v_.max_size(); }
void Benchmark::VectorReserve()						{ reserve_v_.reserve(RandomNumber()); }
void Benchmark::VectorCapacity()					{ v_.capacity(); }
void Benchmark::VectorClear(PRE::vector<int> *vec)	{ vec->clear(); }
void Benchmark::VectorInsert()
{
	insert_v_.insert(insert_v_.begin() + (rand() % (insert_v_.size() - 1)), 42);
}
void Benchmark::VectorInserts()
{
	insert_v_.insert(insert_v_.begin() + (rand() % (insert_v_.size() - 1)), 100, 42);
}
void Benchmark::VectorInsertIterator()
{
	insert_v_.insert(insert_v_.begin() + (rand() % (insert_v_.size() - 1)), v_.begin(), v_.end());
}
void Benchmark::VectorErase(PRE::vector<int> *vec)
{
	vec->erase(vec->begin() + (rand() % (vec->size() - 1)));
}
void Benchmark::VectorEraseIterator(PRE::vector<int> *vec)
{
	vec->erase(vec->begin(), vec->end());
}
void Benchmark::VectorPushBack() 				{ push_back_v_.push_back(42); }
void Benchmark::VectorPopBack() 				{ push_back_v_.pop_back(); }
void Benchmark::VectorResize() 					{ resize_v_.resize(RandomNumber()); }
void Benchmark::VectorSwap() 					{ swap1_v_.swap(swap2_v_); }
void Benchmark::VectorEqualOperator() 			{ (void)(cv_ == cv2_); }
void Benchmark::VectorNotEqualOperator() 		{ (void)(cv_ != cv2_);}
void Benchmark::VectorLessOperator() 			{ (void)(cv_ < cv2_); }
void Benchmark::VectorLessEqualOperator() 		{ (void)(cv_ <= cv2_); }
void Benchmark::VectorGreaterOperator() 		{ (void)(cv_ > cv2_); }
void Benchmark::VectorGreaterEqualOperator() 	{ (void)(cv_ > cv2_); }
void Benchmark::VectorNonMemberSwap() 			{ swap(swap1_v_, swap2_v_); }
