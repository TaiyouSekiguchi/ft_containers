#include "test.hpp"

static void test_put(const PRE::vector<Number>& v)
{
	cout << "empty()  : " << v.empty() << endl;
	cout << "size()   : " << v.size() << endl;
	cout << "content  : [ ";
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << "]" << endl;
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


void vector_test()
{
	constructor_test();
	copy_operator_test();
	access_operator_test();
	iterator_test();
	const_iterator_test();
	reverse_iterator_test();
	const_reverse_iterator_test();
	empty_test();
}
