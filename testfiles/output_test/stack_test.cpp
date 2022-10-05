#include "test.hpp"

static void test_put(PRE::stack<Number> &s)
{
	cout << "empty()     : " << s.empty() << endl;
	cout << "size()      : " << s.size() << endl;
	cout << "content     : [ ";
	while (s.size() != 0)
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << "]\n" << endl;
}

static void constructor_test()
{
	cout << "*********** constructor ***********\n" << endl;

	cout << "[ default constructor ]" << endl;
	PRE::stack<Number> s1;
	test_put(s1);

	s1.push(Number(1));
	s1.push(Number(2));
	s1.push(Number(3));
	test_put(s1);

	cout << "\n[ copy constructor ]" << endl;
	PRE::stack<Number> s2(s1);
	test_put(s2);

	cout << "\n***********************************\n" << endl;
}

static void copy_operator_test()
{
	cout << "********** copy operator **********\n" << endl;
	PRE::stack<Number> s1;
	PRE::stack<Number> s2;

	s1.push(Number(1));
	s1.push(Number(2));
	s1.push(Number(3));

	s2 = s1;
	test_put(s2);

	cout << "\n***********************************\n" << endl;
}

static void top_test()
{
	cout << "********** top **********\n" << endl;
	PRE::stack<Number> s1;
	s1.push(Number(1));
	s1.push(Number(2));
	s1.push(Number(3));
	s1.push(Number(4));
	s1.push(Number(5));
	test_put(s1);
	cout << "\n***********************************\n" << endl;
}

static void empty_test()
{
	cout << "************ empty ************\n" << endl;
	PRE::stack<Number> s1;
	test_put(s1);
	s1.push(Number(1));
	s1.push(Number(2));
	s1.push(Number(3));
	s1.push(Number(4));
	s1.push(Number(5));
	test_put(s1);

	cout << "\n***********************************\n" << endl;
}

static void size_test()
{
	cout << "************ size ************\n" << endl;
	PRE::stack<Number> s1;
	test_put(s1);
	s1.push(Number(1));
	s1.push(Number(2));
	s1.push(Number(3));
	s1.push(Number(4));
	s1.push(Number(5));
	test_put(s1);
	cout << "\n***********************************\n" << endl;
}

static void push_pop_test()
{
	cout << "************ push pop ************\n" << endl;
	PRE::stack<Number> s1;
	test_put(s1);
	s1.push(Number(1));
	s1.push(Number(2));
	s1.push(Number(3));
	s1.push(Number(4));
	s1.push(Number(5));
	test_put(s1);
	cout << "\n***********************************\n" << endl;
}

static void comparison_operator_test()
{
	cout << "************ comparison operator ************\n" << endl;
	PRE::stack<Number> s1;
	PRE::stack<Number> s2;
	PRE::stack<Number> s3;

	s1.push(Number(1));
	s1.push(Number(2));
	s1.push(Number(3));
	s1.push(Number(4));
	s1.push(Number(5));

	s2 = s1;

	s3 = s1;
	s3.push(Number(6));


	if (s1 == s2)
		cout << "OK ( == )" << endl;
	else
		cout << "NG ( == )" << endl;

	if (s1 != s3)
		cout << "OK ( != )" << endl;
	else
		cout << "NG ( != )" << endl;

	if (s1 < s3)
		cout << "OK ( < )" << endl;
	else
		cout << "NG ( < )" << endl;

	if (s1 <= s2)
		cout << "OK ( <= )" << endl;
	else
		cout << "NG ( <= )" << endl;

	if (s3 > s1)
		cout << "OK ( > )" << endl;
	else
		cout << "NG ( > )" << endl;

	if (s1 >= s2)
		cout << "OK ( >= )" << endl;
	else
		cout << "NG ( >= )" << endl;

	test_put(s1);
	test_put(s2);
	test_put(s3);

	cout << "\n***********************************\n" << endl;
}

void stack_test()
{
	constructor_test();
	copy_operator_test();
	top_test();
	empty_test();
	size_test();
	push_pop_test();
	comparison_operator_test();
}
