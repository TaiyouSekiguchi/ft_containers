#include "VectorBenchmark.hpp"

static int RandomNumber() { return (rand() % SIZE); }

VectorBenchmark::VectorBenchmark()
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

VectorBenchmark::~VectorBenchmark()
{
}

void VectorBenchmark::VectorBenchmarking()
{
	Benchmarking("VectorDefaultConstructor", &VectorBenchmark::VectorDefaultConstructor);
	Benchmarking("VectorArgConstructor", &VectorBenchmark::VectorArgConstructor);
	Benchmarking("VectorIteratorConstructor", &VectorBenchmark::VectorIteratorConstructor);
	Benchmarking("VectorCopyConstructor", &VectorBenchmark::VectorCopyConstructor);
	Benchmarking("VectorCopyOperator", &VectorBenchmark::VectorCopyOperator);
	Benchmarking("VectorAssign", &VectorBenchmark::VectorAssign);
	Benchmarking("VectorAssignIterator", &VectorBenchmark::VectorAssignIterator);
	Benchmarking("VectorGetAllocator", &VectorBenchmark::VectorGetAllocator);
	Benchmarking("VectorAt", &VectorBenchmark::VectorAt);
	Benchmarking("VectorAccessOperator", &VectorBenchmark::VectorAccessOperator);
	Benchmarking("VectorFront", &VectorBenchmark::VectorFront);
	Benchmarking("VectorBack", &VectorBenchmark::VectorBack);
	Benchmarking("VectorData", &VectorBenchmark::VectorData);
	Benchmarking("VectorBegin", &VectorBenchmark::VectorBegin);
	Benchmarking("VectorEnd", &VectorBenchmark::VectorEnd);
	Benchmarking("VectorRbegin", &VectorBenchmark::VectorRbegin);
	Benchmarking("VectorRend", &VectorBenchmark::VectorRend);
	Benchmarking("VectorEmpty", &VectorBenchmark::VectorEmpty);
	Benchmarking("VectorSize", &VectorBenchmark::VectorSize);
	Benchmarking("VectorMaxSize", &VectorBenchmark::VectorMaxSize);
	Benchmarking("VectorReserve", &VectorBenchmark::VectorReserve);
	Benchmarking("VectorCapacity", &VectorBenchmark::VectorCapacity);
	Benchmarking("VectorClear", &VectorBenchmark::VectorClear);
	//Benchmarking("VectorInsert", &VectorBenchmark::VectorInsert);
	//Benchmarking("VectorInserts", &VectorBenchmark::VectorInserts);
	//Benchmarking("VectorInsertIterator", &VectorBenchmark::VectorInsertIterator);
	Benchmarking("VectorErase", &VectorBenchmark::VectorErase);
	Benchmarking("VectorEraseIterator", &VectorBenchmark::VectorEraseIterator);
	Benchmarking("VectorPushBack", &VectorBenchmark::VectorPushBack);
	Benchmarking("VectorPopBack", &VectorBenchmark::VectorPopBack);
	Benchmarking("VectorResize", &VectorBenchmark::VectorResize);
	Benchmarking("VectorSwap", &VectorBenchmark::VectorSwap);
	Benchmarking("VectorEqualOperator", &VectorBenchmark::VectorEqualOperator);
	Benchmarking("VectorNotEqualOperator", &VectorBenchmark::VectorNotEqualOperator);
	Benchmarking("VectorLessOperator", &VectorBenchmark::VectorLessOperator);
	Benchmarking("VectorLessEqualOperator", &VectorBenchmark::VectorLessEqualOperator);
	Benchmarking("VectorGreaterOperator", &VectorBenchmark::VectorGreaterOperator);
	Benchmarking("VectorGreaterEqualOperator", &VectorBenchmark::VectorGreaterEqualOperator);
	Benchmarking("VectorNonMemberSwap", &VectorBenchmark::VectorNonMemberSwap);
}

void VectorBenchmark::Benchmarking(std::string test_name, void (VectorBenchmark::*f)())
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

void VectorBenchmark::Benchmarking(std::string test_name,
									void (VectorBenchmark::*f)(PRE::vector<int> *vec))
{
	Timer timer;

	for (int i = 0; i < 1000; i++)
	{
		PRE::vector<int> tmp(SIZE, 33);

		timer.start();
		(this->*f)(&tmp);
		timer.stop();
	}
	std::cout << test_name << "," << timer.getElapsedTime() << std::endl;
}

void VectorBenchmark::VectorDefaultConstructor()			{ PRE::vector<int> v; }
void VectorBenchmark::VectorArgConstructor()				{ PRE::vector<int> v(SIZE, 33); }
void VectorBenchmark::VectorIteratorConstructor()			{ PRE::vector<int> v(v_.begin(), v_.end()); }
void VectorBenchmark::VectorCopyConstructor()				{ PRE::vector<int> v(v_); }
void VectorBenchmark::VectorCopyOperator()					{ PRE::vector<int> v; v = cv_; }
void VectorBenchmark::VectorAssign()						{ assign_v_.assign(SIZE, 42); }
void VectorBenchmark::VectorAssignIterator()				{ assign_v_.assign(v_.begin(), v_.end()); }
void VectorBenchmark::VectorGetAllocator()					{ v_.get_allocator(); }
void VectorBenchmark::VectorAt()							{ v_.at(RandomNumber()); }
void VectorBenchmark::VectorAccessOperator()				{ v_[RandomNumber()]; }
void VectorBenchmark::VectorFront()							{ v_.front(); }
void VectorBenchmark::VectorBack()							{ v_.back(); }
void VectorBenchmark::VectorData()							{ v_.data(); }
void VectorBenchmark::VectorBegin()							{ v_.begin(); }
void VectorBenchmark::VectorEnd()							{ v_.end(); }
void VectorBenchmark::VectorRbegin()						{ v_.rbegin(); }
void VectorBenchmark::VectorRend()							{ v_.rend(); }
void VectorBenchmark::VectorEmpty()							{ v_.empty(); }
void VectorBenchmark::VectorSize()							{ v_.size(); }
void VectorBenchmark::VectorMaxSize()						{ v_.max_size(); }
void VectorBenchmark::VectorReserve()						{ reserve_v_.reserve(RandomNumber()); }
void VectorBenchmark::VectorCapacity()						{ v_.capacity(); }
void VectorBenchmark::VectorClear(PRE::vector<int> *vec)	{ vec->clear(); }
void VectorBenchmark::VectorInsert()
{
	insert_v_.insert(insert_v_.begin() + (rand() % (insert_v_.size() - 1)), 42);
}
void VectorBenchmark::VectorInserts()
{
	insert_v_.insert(insert_v_.begin() + (rand() % (insert_v_.size() - 1)), 100, 42);
}
void VectorBenchmark::VectorInsertIterator()
{
	insert_v_.insert(insert_v_.begin() + (rand() % (insert_v_.size() - 1)), v_.begin(), v_.end());
}
void VectorBenchmark::VectorErase(PRE::vector<int> *vec)
{
	vec->erase(vec->begin() + (rand() % (vec->size() - 1)));
}
void VectorBenchmark::VectorEraseIterator(PRE::vector<int> *vec)
{
	vec->erase(vec->begin(), vec->end());
}
void VectorBenchmark::VectorPushBack() 				{ push_back_v_.push_back(42); }
void VectorBenchmark::VectorPopBack() 				{ push_back_v_.pop_back(); }
void VectorBenchmark::VectorResize() 				{ resize_v_.resize(RandomNumber()); }
void VectorBenchmark::VectorSwap() 					{ swap1_v_.swap(swap2_v_); }
void VectorBenchmark::VectorEqualOperator()			{ (void)(cv_ == cv2_); }
void VectorBenchmark::VectorNotEqualOperator() 		{ (void)(cv_ != cv2_);}
void VectorBenchmark::VectorLessOperator() 			{ (void)(cv_ < cv2_); }
void VectorBenchmark::VectorLessEqualOperator() 	{ (void)(cv_ <= cv2_); }
void VectorBenchmark::VectorGreaterOperator() 		{ (void)(cv_ > cv2_); }
void VectorBenchmark::VectorGreaterEqualOperator() 	{ (void)(cv_ > cv2_); }
void VectorBenchmark::VectorNonMemberSwap() 		{ swap(swap1_v_, swap2_v_); }
