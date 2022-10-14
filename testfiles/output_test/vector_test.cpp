#include "test.hpp"

static void test_put(const PRE::vector<Number>& v)
{
	cout << "empty()     : " << v.empty() << endl;
	cout << "size()      : " << v.size() << endl;
	cout << "content     : [ ";
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << "]\n" << endl;
}

static void test_put2(const PRE::vector<Number>& v, const PRE::vector<Number>::iterator& it)
{
	cout << "empty()   : " << v.empty() << endl;
	cout << "size()    : " << v.size() << endl;
	cout << "content   : [ ";
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << "]" << endl;
	if (it != v.end())
		cout << "*it       : " << *it << endl;
	cout << endl;
}

static void constructor_test()
{
	cout << "*********** constructor ***********\n" << endl;

	cout << "[ default constructor ]" << endl;
	PRE::vector<Number> v1;
	test_put(v1);

	cout << "\n[ argument constructor ]" << endl;
	PRE::vector<Number> v2(3, Number(42));
	test_put(v2);

	cout << "\n[ iterator constructor ]" << endl;
	PRE::vector<Number> v3(v2.begin(), v2.end());
	test_put(v3);

	cout << "\n[ copy constructor ]" << endl;
	PRE::vector<Number> v4(v2);
	test_put(v4);

	cout << "\n***********************************\n" << endl;
}

static void copy_operator_test()
{
	cout << "********** copy operator **********\n" << endl;
	PRE::vector<Number> v1(3, Number(42));
	PRE::vector<Number> v2;

	v2 = v1;
	test_put(v2);

	cout << "\n***********************************\n" << endl;
}

static void access_operator_test()
{
	cout << "********* access operator *********\n" << endl;
	PRE::vector<Number> v(5, Number(42));

	test_put(v);

	cout << "\n***********************************\n" << endl;
}

static void iterator_test()
{
	cout << "************ iterator ************\n" << endl;
	PRE::vector<Number> v;
	v.push_back(Number(1));
	v.push_back(Number(2));
	v.push_back(Number(3));
	v.push_back(Number(4));
	v.push_back(Number(5));
	test_put(v);

	PRE::vector<Number>::iterator it = v.begin();
	PRE::vector<Number>::iterator it_end = v.end();

	cout << "iterator output" << endl;
	for (; it != it_end; ++it)
		cout << *it << " ";
	cout << endl;

	cout << "\n***********************************\n" << endl;
}

static void const_iterator_test()
{
	cout << "************ const_iterator ************\n" << endl;
	PRE::vector<Number> v;
	v.push_back(Number(1));
	v.push_back(Number(2));
	v.push_back(Number(3));
	v.push_back(Number(4));
	v.push_back(Number(5));

	const PRE::vector<Number> &cv = v;
	test_put(cv);

	PRE::vector<Number>::const_iterator it = cv.begin();
	PRE::vector<Number>::const_iterator it_end = cv.end();

	cout << "const iterator output" << endl;
	for (; it != it_end; ++it)
		cout << *it << " ";
	cout << endl;

	cout << "\n***********************************\n" << endl;
}

static void reverse_iterator_test()
{
	cout << "************ reverse_iterator ************\n" << endl;
	PRE::vector<Number> v;
	v.push_back(Number(1));
	v.push_back(Number(2));
	v.push_back(Number(3));
	v.push_back(Number(4));
	v.push_back(Number(5));
	test_put(v);

	PRE::vector<Number>::reverse_iterator it = v.rbegin();
	PRE::vector<Number>::reverse_iterator it_end = v.rend();

	cout << "reverse iterator output" << endl;
	for (; it != it_end; ++it)
		cout << *it << " ";
	cout << endl;

	cout << "\n***********************************\n" << endl;
}

static void const_reverse_iterator_test()
{
	cout << "************ const_reverse_iterator ************\n" << endl;
	PRE::vector<Number> v;
	v.push_back(Number(1));
	v.push_back(Number(2));
	v.push_back(Number(3));
	v.push_back(Number(4));
	v.push_back(Number(5));

	const PRE::vector<Number> &cv = v;
	test_put(cv);

	PRE::vector<Number>::const_reverse_iterator it = cv.rbegin();
	PRE::vector<Number>::const_reverse_iterator it_end = cv.rend();

	cout << "const reverse iterator output" << endl;
	for (; it != it_end; ++it)
		cout << *it << " ";
	cout << endl;

	cout << "\n***********************************\n" << endl;
}

static void empty_test()
{
	cout << "************ empty ************\n" << endl;
	PRE::vector<Number> v1;
	test_put(v1);

	PRE::vector<Number> v2(3, Number(42));
	test_put(v2);

	cout << "\n***********************************\n" << endl;
}

static void size_test()
{
	cout << "************ size ************\n" << endl;
	PRE::vector<Number> v1;
	test_put(v1);

	PRE::vector<Number> v2(21, Number(42));
	test_put(v2);

	cout << "\n***********************************\n" << endl;
}

static void max_size_test()
{
	cout << "************ max_size ************\n" << endl;
	PRE::vector<Number> v;
	test_put(v);
	cout << "max_size : " << v.max_size() << endl;

	cout << "\n***********************************\n" << endl;
}

static void capacity_test()
{
	cout << "************ capacity ************\n" << endl;
	PRE::vector<Number> v1;
	test_put(v1);
	cout << "capacity : " << v1.capacity() << endl;

	PRE::vector<Number> v2(10, 42);
	test_put(v2);
	cout << "capacity : " << v2.capacity() << endl;

	PRE::vector<Number> v3(42, 10);
	v3.push_back(33);
	v3.push_back(33);
	v3.push_back(33);
	v3.push_back(33);
	v3.push_back(33);
	v3.push_back(33);
	test_put(v3);
	cout << "capacity : " << v3.capacity() << endl;

	cout << "\n***********************************\n" << endl;
}

static void reserve_test()
{
	cout << "************ reserve ************\n" << endl;
	PRE::vector<Number> v1;
	v1.reserve(10);
	test_put(v1);

	PRE::vector<Number> v2(10, 42);
	v2.reserve(3);
	test_put(v2);

	PRE::vector<Number> v3(42, 10);
	try
	{
		v3.resize(-1);
	}
	catch(const std::length_error& e)
	{
		cout << "catch length_error" << endl;
	}
	test_put(v3);

	cout << "\n***********************************\n" << endl;
}

static void clear_test()
{
	cout << "************ clear ************\n" << endl;
	PRE::vector<Number> v1;
	v1.clear();
	test_put(v1);

	PRE::vector<Number> v2(10, 42);
	v2.clear();
	test_put(v2);

	PRE::vector<Number> v3(42, 10);
	v3.push_back(33);
	v3.push_back(33);
	v3.push_back(33);
	v3.push_back(33);
	v3.push_back(33);
	v3.push_back(33);
	v3.clear();
	test_put(v3);

	cout << "\n***********************************\n" << endl;
}

static void insert_test()
{
	cout << "************ insert ************\n" << endl;
	PRE::vector<Number> v1;
	PRE::vector<Number>::iterator it;

	it = v1.insert(v1.begin(), Number(1));
	test_put2(v1, it);
	it = v1.insert(v1.begin() + 1, Number(2));
	test_put2(v1, it);
	it = v1.insert(v1.begin() + 2, Number(3));
	test_put2(v1, it);

	PRE::vector<Number> v2;
	v2.insert(v2.begin(), 5, Number(42));
	test_put(v2);
	v2.insert(v2.begin() + 5, 5, Number(33));
	test_put(v2);
	v2.insert(v2.begin(), 5, Number(11));
	test_put(v2);

	PRE::vector<Number> v3;
	v3.insert(v3.begin(), v2.begin(), v2.end());
	test_put(v3);
	v3.insert(v3.begin() + 2, v2.begin() + 5 , v2.begin() + 7);
	test_put(v3);

	cout << "\n***********************************\n" << endl;
}

static void erase_test()
{
	cout << "************ erase ************\n" << endl;
	PRE::vector<Number> v1;
	v1.push_back(Number(1));
	v1.push_back(Number(2));
	v1.push_back(Number(3));
	v1.push_back(Number(4));
	v1.push_back(Number(5));
	v1.push_back(Number(6));
	v1.push_back(Number(7));
	test_put(v1);

	PRE::vector<Number>::iterator it;

	it = v1.erase(v1.end() - 1);
	test_put2(v1, it);

	it = v1.erase(v1.begin() + 2, v1.begin() + 5);
	test_put2(v1, it);

	it = v1.erase(v1.begin(), v1.end());
	test_put2(v1, it);

	cout << "\n***********************************\n" << endl;
}

static void push_back_test()
{
	cout << "************ push_back ************\n" << endl;
	PRE::vector<Number> v1;
	v1.push_back(Number(1));
	v1.push_back(Number(2));
	v1.push_back(Number(3));
	v1.push_back(Number(4));
	v1.push_back(Number(5));
	v1.push_back(Number(6));
	v1.push_back(Number(7));
	test_put(v1);

	cout << "\n***********************************\n" << endl;
}

static void pop_back_test()
{
	cout << "************ pop_back ************\n" << endl;
	PRE::vector<Number> v(10, 3);
	test_put(v);

	v.pop_back();
	v.pop_back();
	v.pop_back();
	test_put(v);

	cout << "\n***********************************\n" << endl;
}

static void resize_test()
{
	cout << "************ resize ************\n" << endl;
	PRE::vector<Number> v(5, 42);
	test_put(v);

	v.resize(10, 33);
	test_put(v);
	v.resize(15);
	test_put(v);
	v.resize(3);
	test_put(v);

	try
	{
		v.resize(-1);
	}
	catch(const std::length_error& e)
	{
		cout << "catch length_error" << endl;
	}
	test_put(v);

	cout << "\n***********************************\n" << endl;
}

static void swap_test()
{
	cout << "************ swap ************\n" << endl;
	PRE::vector<Number> v1(5, 42);
	PRE::vector<Number> v2(7, 33);
	cout << "v1 capacity : " << v1.capacity() << endl;
	test_put(v1);
	cout << "v2 capacity : " << v2.capacity() << endl;
	test_put(v2);

	v1.swap(v2);
	cout << "v1 capacity : " << v1.capacity() << endl;
	test_put(v1);
	cout << "v2 capacity : " << v2.capacity() << endl;
	test_put(v2);

	cout << "\n***********************************\n" << endl;
}

static void comparison_operator_test()
{
	cout << "************ comparison operator ************\n" << endl;
	PRE::vector<Number> v1(10, 5);
	PRE::vector<Number> v2(10, 5);
	PRE::vector<Number> v3(42, 5);

	test_put(v1);
	test_put(v2);
	test_put(v3);
	if (v1 == v2)
		cout << "OK ( == )" << endl;
	else
		cout << "NG ( == )" << endl;

	if (v1 != v3)
		cout << "OK ( != )" << endl;
	else
		cout << "NG ( != )" << endl;

	if (v1 < v3)
		cout << "OK ( < )" << endl;
	else
		cout << "NG ( < )" << endl;

	if (v1 <= v2)
		cout << "OK ( <= )" << endl;
	else
		cout << "NG ( <= )" << endl;

	if (v3 > v1)
		cout << "OK ( > )" << endl;
	else
		cout << "NG ( > )" << endl;

	if (v1 >= v2)
		cout << "OK ( >= )" << endl;
	else
		cout << "NG ( >= )" << endl;

	cout << "\n***********************************\n" << endl;
}

static void non_member_swap_test()
{
	cout << "************ non-member swap ************\n" << endl;
	PRE::vector<Number> v1(5, 42);
	PRE::vector<Number> v2(7, 33);
	cout << "v1 capacity : " << v1.capacity() << endl;
	test_put(v1);
	cout << "v2 capacity : " << v2.capacity() << endl;
	test_put(v2);

	swap(v1, v2);
	cout << "v1 capacity : " << v1.capacity() << endl;
	test_put(v1);
	cout << "v2 capacity : " << v2.capacity() << endl;
	test_put(v2);

	cout << "\n***********************************\n" << endl;
}

static void assign_test()
{
	cout << "************ assign ************\n" << endl;
	PRE::vector<Number> v;

	v.assign(3, 42);
	test_put(v);
	v.assign(3, 42);
	test_put(v);
	v.assign(3, 42);
	test_put(v);

	try
	{
		v.assign(-1, 42);
	}
	catch(const std::length_error& e)
	{
		cout << "catch length_error" << endl;
	}
	test_put(v);

	//std::array<Number, 4> data = {Number(4), Number(3), Number(2), Number(2)};
	//PRE::vector<Number> data;
	std::list<Number> data;
	data.push_back(Number(5));
	data.push_back(Number(4));
	data.push_back(Number(3));
	data.push_back(Number(2));
	data.push_back(Number(1));

	v.assign(data.begin(), data.end());
	v.assign(data.begin(), data.end());
	v.assign(data.begin(), data.end());
	/*
	test_put(v);
	v.assign(data.begin(), data.begin() + 2);
	test_put(v);
	v.assign(data.begin(), data.end());
	test_put(v);
	try
	{
		v.assign(data.begin(), data.begin() - 1);
	}
	catch(const std::length_error& e)
	{
		cout << "catch length_error" << endl;
	}
	*/
	test_put(v);

	cout << "\n***********************************\n" << endl;
}

static void get_allocator_test()
{
	cout << "************ get_allocator ************\n" << endl;

	PRE::vector<Number> v;

	if (v.get_allocator() == std::allocator<Number>())
		cout << "OK" << endl;
	else
		cout << "NG" << endl;

	cout << "\n***********************************\n" << endl;
}

static void at_test()
{
	cout << "************ at ************\n" << endl;

	PRE::vector<Number> v;
	for (int i = 0; i < 5; i++)
		v.push_back(Number(i));

	for (int i = 0; i < 5; i++)
		cout << v.at(i) << " ";
	cout << endl;

	try
	{
		v.at(5);
	}
	catch(const std::out_of_range& e)
	{
		cout << "catch out_of_range" << endl;
	}

	cout << "\n***********************************\n" << endl;
}

static void front_test()
{
	cout << "************ front ************\n" << endl;

	PRE::vector<Number> v(3, 42);
	const PRE::vector<Number> &cv = v;

	cout << v.front() << endl;
	cout << cv.front() << endl;

	cout << "\n***********************************\n" << endl;
}

static void back_test()
{
	cout << "************ back ************\n" << endl;

	PRE::vector<Number> v(3, 42);
	const PRE::vector<Number> &cv = v;

	cout << v.back() << endl;
	cout << cv.back() << endl;

	cout << "\n***********************************\n" << endl;
}

static void data_test()
{
	cout << "************ data ************\n" << endl;

	PRE::vector<Number> v(3, 42);
	const PRE::vector<Number> &cv = v;

	cout << *(v.data()) << endl;
	cout << *(cv.data()) << endl;

	cout << "\n***********************************\n" << endl;
}

void vector_test()
{
	constructor_test();
	copy_operator_test();
	assign_test();
	get_allocator_test();

	// Element access
	at_test();
	access_operator_test();
	front_test();
	back_test();
	data_test();

	// Iterators
	iterator_test();
	const_iterator_test();
	reverse_iterator_test();
	const_reverse_iterator_test();

	// Capacity
	empty_test();
	size_test();
	max_size_test();
	reserve_test();
	capacity_test();

	// Modifiers
	clear_test();
	insert_test();
	erase_test();
	push_back_test();
	pop_back_test();
	resize_test();
	swap_test();

	// Non-member functions
	comparison_operator_test();
	non_member_swap_test();
}
