#include "test.hpp"

static void test_put(const PRE::map<Number, std::string> &m)
{
	PRE::map<Number, std::string>::const_iterator it = m.begin();
	PRE::map<Number, std::string>::const_iterator it_end = m.end();

	cout << "empty()     : " << m.empty() << endl;
	cout << "size()      : " << m.size() << endl;
	cout << "content     : [ ";
	for (; it != it_end; ++it)
	{
		cout << "( " << it->first << ", " << it->second << " ) ";
	}
	cout << "]\n" << endl;
}

static void constructor_test()
{
	cout << "*********** constructor ***********\n" << endl;

	cout << "[ default constructor ]" << endl;
	PRE::map<Number, std::string> m1;
	test_put(m1);

	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(1)] = "one";
	m1[Number(5)] = "five";
	m1[Number(0)] = "zero";
	test_put(m1);

	cout << "\n[ iterator constructor ]" << endl;
	PRE::map<Number, std::string> m2(m1.begin(), m1.end());
	test_put(m2);

	cout << "\n[ copy constructor ]" << endl;
	PRE::map<Number, std::string> m3(m1);
	test_put(m3);

	cout << "\n***********************************\n" << endl;
}

static void copy_operator_test()
{
	cout << "********** copy operator **********\n" << endl;
	PRE::map<Number, std::string> m1;

	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(1)] = "one";
	m1[Number(5)] = "five";
	m1[Number(0)] = "zero";
	test_put(m1);

	PRE::map<Number, std::string> m2;

	m2 = m1;
	test_put(m2);

	cout << "\n***********************************\n" << endl;
}

static void get_allocator_test()
{
	cout << "************ get_allocator ************\n" << endl;

	PRE::map<Number, std::string> m;

	if (m.get_allocator() == std::allocator<PRE::pair<const Number, std::string> >())
		cout << "OK" << endl;
	else
		cout << "NG" << endl;

	cout << "\n***********************************\n" << endl;
}

static void access_operator_test()
{
	cout << "********* access operator *********\n" << endl;
	PRE::map<Number, std::string> m1;

	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(1)] = "one";
	m1[Number(5)] = "five";
	m1[Number(0)] = "zero";
	test_put(m1);

	cout << "[ ";
	for (size_t i = 0; i < m1.size(); ++i)
	{
		cout << m1[Number(i)] << " ";
	}
	cout << "]" << endl;

	cout << "\n***********************************\n" << endl;
}

static void iterator_test()
{
	cout << "************ iterator ************\n" << endl;
	PRE::map<Number, std::string> m1;

	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(1)] = "one";
	m1[Number(5)] = "five";
	m1[Number(0)] = "zero";
	test_put(m1);

	PRE::map<Number, std::string>::iterator it = m1.begin();
	PRE::map<Number, std::string>::iterator it_end = m1.end();

	cout << "iterator output" << endl;
	for (; it != it_end; ++it)
		cout << "( " << it->first << ", " << it->second << " ) ";
	cout << endl;

	cout << "\n***********************************\n" << endl;
}

static void const_iterator_test()
{
	cout << "************ const_iterator ************\n" << endl;
	PRE::map<Number, std::string> m1;

	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(1)] = "one";
	m1[Number(5)] = "five";
	m1[Number(0)] = "zero";
	test_put(m1);

	const PRE::map<Number, std::string> &cm = m1;

	PRE::map<Number, std::string>::const_iterator cit = cm.begin();
	PRE::map<Number, std::string>::const_iterator cit_end = cm.end();

	cout << "const iterator output" << endl;
	for (; cit != cit_end; ++cit)
		cout << "( " << cit->first << ", " << cit->second << " ) ";
	cout << endl;

	cout << "\n***********************************\n" << endl;
}

static void reverse_iterator_test()
{
	cout << "************ reverse iterator ************\n" << endl;
	PRE::map<Number, std::string> m1;

	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(1)] = "one";
	m1[Number(5)] = "five";
	m1[Number(0)] = "zero";
	test_put(m1);

	PRE::map<Number, std::string>::reverse_iterator it = m1.rbegin();
	PRE::map<Number, std::string>::reverse_iterator it_end = m1.rend();

	cout << "reverse iterator output" << endl;
	for (; it != it_end; ++it)
		cout << "( " << it->first << ", " << it->second << " ) ";
	cout << endl;

	cout << "\n***********************************\n" << endl;
}

static void const_reverse_iterator_test()
{
	cout << "************ const_reverse_iterator ************\n" << endl;
	PRE::map<Number, std::string> m1;

	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(1)] = "one";
	m1[Number(5)] = "five";
	m1[Number(0)] = "zero";
	test_put(m1);

	const PRE::map<Number, std::string>& cm = m1;

	PRE::map<Number, std::string>::const_reverse_iterator cit = cm.rbegin();
	PRE::map<Number, std::string>::const_reverse_iterator cit_end = cm.rend();

	cout << "const reverse iterator output" << endl;
	for (; cit != cit_end; ++cit)
		cout << "( " << cit->first << ", " << cit->second << " ) ";
	cout << endl;

	cout << "\n***********************************\n" << endl;
}

static void empty_test()
{
	cout << "************ empty ************\n" << endl;
	PRE::map<Number, std::string> m1;
	test_put(m1);

	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(1)] = "one";
	m1[Number(5)] = "five";
	m1[Number(0)] = "zero";
	test_put(m1);

	cout << "\n***********************************\n" << endl;
}

static void size_test()
{
	cout << "************ size ************\n" << endl;
	PRE::map<Number, std::string> m1;
	test_put(m1);

	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(1)] = "one";
	m1[Number(5)] = "five";
	m1[Number(0)] = "zero";
	test_put(m1);

	cout << "\n***********************************\n" << endl;
}

static void max_size_test()
{
	cout << "************ max_size ************\n" << endl;
	PRE::map<Number, std::string> m1;
	test_put(m1);
	cout << "max_size : " << m1.max_size() << endl;

	cout << "\n***********************************\n" << endl;
}

static void clear_test()
{
	cout << "************ clear ************\n" << endl;
	PRE::map<Number, std::string> m1;
	test_put(m1);

	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(1)] = "one";
	m1[Number(5)] = "five";
	m1[Number(0)] = "zero";
	test_put(m1);
	m1.clear();
	test_put(m1);

	cout << "\n***********************************\n" << endl;
}

static void insert_test()
{
	cout << "************ insert ************\n" << endl;
	PRE::map<Number, std::string> m1;
	test_put(m1);

	PRE::pair<PRE::map<Number, std::string>::iterator, bool> ret;
	PRE::map<Number, std::string>::iterator it;

	ret = m1.insert(PRE::make_pair(Number(0), "zero"));
	cout << "( " << (ret.first)->first << ", " << (ret.first)->second << " ) " << ret.second << endl;
	ret = m1.insert(PRE::make_pair(Number(1), "one"));
	cout << "( " << (ret.first)->first << ", " << (ret.first)->second << " ) " << ret.second << endl;
	ret = m1.insert(PRE::make_pair(Number(3), "three"));
	cout << "( " << (ret.first)->first << ", " << (ret.first)->second << " ) " << ret.second << endl;
	ret = m1.insert(PRE::make_pair(Number(2), "two"));
	cout << "( " << (ret.first)->first << ", " << (ret.first)->second << " ) " << ret.second << endl;
	ret = m1.insert(PRE::make_pair(Number(2), "two"));
	cout << "( " << (ret.first)->first << ", " << (ret.first)->second << " ) " << ret.second << endl;
	test_put(m1);

	it = m1.insert(m1.find(Number(4)), PRE::make_pair(Number(4), "four"));
	cout << "( " << it->first << ", " << it->second << " )" << endl;
	it = m1.insert(m1.find(Number(5)), PRE::make_pair(Number(5), "five"));
	cout << "( " << it->first << ", " << it->second << " )" << endl;
	it = m1.insert(m1.find(Number(5)), PRE::make_pair(Number(5), "five"));
	cout << "( " << it->first << ", " << it->second << " )" << endl;
	test_put(m1);

	PRE::map<Number, std::string> m2;
	test_put(m2);
	m2.insert(m1.begin(), m1.end());
	test_put(m2);

	cout << "\n***********************************\n" << endl;
}

static void erase_test()
{
	cout << "************ erase ************\n" << endl;
	PRE::map<Number, std::string> m1;

	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(1)] = "one";
	m1[Number(5)] = "five";
	m1[Number(0)] = "zero";
	test_put(m1);

	m1.erase(m1.find(Number(5)));
	test_put(m1);
	m1.erase(m1.find(Number(2)));
	test_put(m1);

	size_t ret;

	ret = m1.erase(Number(4));
	cout << "ret : " << ret << endl;
	test_put(m1);
	ret = m1.erase(Number(4));
	cout << "ret : " << ret << endl;
	test_put(m1);

	m1.erase(m1.begin(), m1.end());
	test_put(m1);

	cout << "\n***********************************\n" << endl;
}

static void swap_test()
{
	cout << "************ swap ************\n" << endl;
	PRE::map<Number, std::string> m1;
	PRE::map<Number, std::string> m2;

	m1[Number(0)] = "zero";
	m1[Number(1)] = "one";
	m1[Number(2)] = "two";

	m2[Number(4)] = "four";
	m2[Number(3)] = "three";
	m2[Number(5)] = "five";

	test_put(m1);
	test_put(m2);
	m1.swap(m2);
	test_put(m1);
	test_put(m2);
	cout << "\n***********************************\n" << endl;
}

static void count_test()
{
	cout << "************ count ************\n" << endl;
	PRE::map<Number, std::string> m1;

	m1[Number(0)] = "zero";
	m1[Number(1)] = "one";
	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(5)] = "five";
	test_put(m1);

	cout << "Number(2) : " << m1.count(Number(2)) << endl;
	cout << "Number(3) : " << m1.count(Number(3)) << endl;
	cout << "Number(6) : " << m1.count(Number(6)) << endl;
	cout << "Number(9) : " << m1.count(Number(9)) << endl;
	cout << "\n***********************************\n" << endl;
}

static void find_test()
{
	cout << "************ find ************\n" << endl;
	PRE::map<Number, std::string> m1;
	PRE::map<Number, std::string>::iterator it;

	m1[Number(0)] = "zero";
	m1[Number(1)] = "one";
	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(5)] = "five";
	test_put(m1);

	it = m1.find(Number(0));
	if (it != m1.end())
		cout << "( " << it->first << ", " << it->second << " )" << endl;
	else
		cout << "None" << endl;

	it = m1.find(Number(7));
	if (it != m1.end())
		cout << "( " << it->first << ", " << it->second << " )" << endl;
	else
		cout << "None" << endl;

	const PRE::map<Number, std::string> &cm = m1;
	PRE::map<Number, std::string>::const_iterator cit;
	cit = cm.find(Number(5));
	if (cit != cm.end())
		cout << "( " << cit->first << ", " << cit->second << " )" << endl;
	else
		cout << "None" << endl;

	cit = cm.find(Number(11));
	if (cit != cm.end())
		cout << "( " << cit->first << ", " << cit->second << " )" << endl;
	else
		cout << "None" << endl;


	cout << "\n***********************************\n" << endl;
}

static void equal_range_test()
{
	cout << "************ equal_range ************\n" << endl;
	PRE::map<Number, std::string> m1;

	m1[Number(0)] = "zero";
	m1[Number(1)] = "one";
	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(5)] = "five";
	test_put(m1);

	typedef PRE::map<Number, std::string>::iterator itr;
	PRE::pair<itr, itr>								ret;

	ret = m1.equal_range(Number(2));
	for (itr it = ret.first; it != ret.second; ++it)
		cout << "( " << it->first << ", " << it->second << " )" << endl;
	ret = m1.equal_range(Number(42));
	for (itr it = ret.first; it != ret.second; ++it)
		cout << "( " << it->first << ", " << it->second << " )" << endl;

	const PRE::map<Number, std::string> &cm = m1;
	typedef PRE::map<Number, std::string>::const_iterator	citr;
	PRE::pair<citr, citr>									cret;

	cret = cm.equal_range(Number(4));
	for (citr it = cret.first; it != cret.second; ++it)
		cout << "( " << it->first << ", " << it->second << " )" << endl;
	cret = cm.equal_range(Number(33));
	for (citr it = cret.first; it != cret.second; ++it)
		cout << "( " << it->first << ", " << it->second << " )" << endl;

	cout << "\n***********************************\n" << endl;
}

static void lower_bound_test()
{
	cout << "************ lower_bound ************\n" << endl;
	PRE::map<Number, std::string> m1;
	PRE::map<Number, std::string>::iterator it;

	m1[Number(0)] = "zero";
	m1[Number(1)] = "one";
	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(5)] = "five";
	test_put(m1);

	it = m1.lower_bound(Number(2));
	if (it != m1.end())
		cout << "( " << it->first << ", " << it->second << " )" << endl;
	else
		cout << "None" << endl;

	it = m1.lower_bound(Number(10));
	if (it != m1.end())
		cout << "( " << it->first << ", " << it->second << " )" << endl;
	else
		cout << "None" << endl;

	const PRE::map<Number, std::string>& cm = m1;
	PRE::map<Number, std::string>::const_iterator cit;

	cit = cm.lower_bound(Number(2));
	if (cit != cm.end())
		cout << "( " << cit->first << ", " << cit->second << " )" << endl;
	else
		cout << "None" << endl;

	cit = cm.lower_bound(Number(10));
	if (cit != cm.end())
		cout << "( " << cit->first << ", " << cit->second << " )" << endl;
	else
		cout << "None" << endl;

	cout << "\n***********************************\n" << endl;
}

static void upper_bound_test()
{
	cout << "************ upper_bound ************\n" << endl;
	PRE::map<Number, std::string> m1;
	PRE::map<Number, std::string>::iterator it;

	m1[Number(0)] = "zero";
	m1[Number(1)] = "one";
	m1[Number(2)] = "two";
	m1[Number(4)] = "four";
	m1[Number(3)] = "three";
	m1[Number(5)] = "five";
	test_put(m1);

	it = m1.upper_bound(Number(4));
	if (it != m1.end())
		cout << "( " << it->first << ", " << it->second << " )" << endl;
	else
		cout << "None" << endl;

	it = m1.upper_bound(Number(10));
	if (it != m1.end())
		cout << "( " << it->first << ", " << it->second << " )" << endl;
	else
		cout << "None" << endl;

	const PRE::map<Number, std::string>& cm = m1;
	PRE::map<Number, std::string>::const_iterator cit;

	cit = cm.upper_bound(Number(4));
	if (cit != cm.end())
		cout << "( " << cit->first << ", " << cit->second << " )" << endl;
	else
		cout << "None" << endl;

	cit = cm.upper_bound(Number(10));
	if (cit != cm.end())
		cout << "( " << cit->first << ", " << cit->second << " )" << endl;
	else
		cout << "None" << endl;

	cout << "\n***********************************\n" << endl;
}

static void key_comp_test()
{
	cout << "************ key_comp ************\n" << endl;
	PRE::map<Number, std::string> m;
	PRE::map<Number, std::string>::key_compare comp = m.key_comp();

	cout << comp(Number(1), Number(2)) << endl;
	cout << comp(Number(3), Number(2)) << endl;
	cout << comp(Number(2), Number(2)) << endl;
	cout << "\n***********************************\n" << endl;
}

static void value_comp_test()
{
	cout << "************ value_comp ************\n" << endl;
	PRE::map<Number, std::string> m;
	PRE::map<Number, std::string>::value_compare comp = m.value_comp();

	PRE::pair<Number, std::string> p1 = PRE::make_pair(Number(1), "one");
	PRE::pair<Number, std::string> p2 = PRE::make_pair(Number(2), "two");
	PRE::pair<Number, std::string> p3 = PRE::make_pair(Number(3), "three");

	cout << comp(p1,p2) << endl;
	cout << comp(p3,p2) << endl;
	cout << comp(p2,p2) << endl;
	cout << "\n***********************************\n" << endl;
}

static void comparison_operator_test()
{
	cout << "************ comparison operator ************\n" << endl;
	PRE::map<Number, std::string> m1;
	PRE::map<Number, std::string> m2;
	PRE::map<Number, std::string> m3;

	m1[Number(0)] = "zero";
	m1[Number(1)] = "one";
	m1[Number(2)] = "two";
	m1[Number(3)] = "three";
	m1[Number(4)] = "four";

	m2 = m1;
	m3 = m1;
	m3[Number(5)] = "five";
	m3[Number(6)] = "six";

	test_put(m1);
	test_put(m2);
	test_put(m3);
	if (m1 == m2)
		cout << "OK ( == )" << endl;
	else
		cout << "NG ( == )" << endl;

	if (m1 != m3)
		cout << "OK ( != )" << endl;
	else
		cout << "NG ( != )" << endl;

	if (m1 < m3)
		cout << "OK ( < )" << endl;
	else
		cout << "NG ( < )" << endl;

	if (m1 <= m2)
		cout << "OK ( <= )" << endl;
	else
		cout << "NG ( <= )" << endl;

	if (m3 > m1)
		cout << "OK ( > )" << endl;
	else
		cout << "NG ( > )" << endl;

	if (m1 >= m2)
		cout << "OK ( >= )" << endl;
	else
		cout << "NG ( >= )" << endl;

	cout << "\n***********************************\n" << endl;
}

static void non_member_swap_test()
{
	cout << "************ non-member swap ************\n" << endl;
	PRE::map<Number, std::string> m1;
	PRE::map<Number, std::string> m2;

	m1[Number(0)] = "zero";
	m1[Number(1)] = "one";
	m1[Number(2)] = "two";

	m2[Number(4)] = "four";
	m2[Number(3)] = "three";
	m2[Number(5)] = "five";

	test_put(m1);
	test_put(m2);
	swap(m1, m2);
	test_put(m1);
	test_put(m2);
	cout << "\n***********************************\n" << endl;
}
/*

static void assign_test()
{
	cout << "************ assign ************\n"
		 << endl;
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
	catch (const std::length_error &e)
	{
		cout << "catch length_error" << endl;
	}
	test_put(v);

	const std::array<int, 4> data = {4, 3, 2, 1};

	v.assign(data.begin(), data.begin() + 1);
	test_put(v);
	v.assign(data.begin(), data.begin() + 2);
	test_put(v);
	v.assign(data.begin(), data.end());
	test_put(v);
	try
	{
		v.assign(data.begin(), data.begin() - 1);
	}
	catch (const std::length_error &e)
	{
		cout << "catch length_error" << endl;
	}
	test_put(v);

	cout << "\n***********************************\n"
		 << endl;
}

static void get_allocator_test()
{
	cout << "************ get_allocator ************\n"
		 << endl;

	PRE::vector<Number> v;

	if (v.get_allocator() == std::allocator<Number>())
		cout << "OK" << endl;
	else
		cout << "NG" << endl;

	cout << "\n***********************************\n"
		 << endl;
}

static void at_test()
{
	cout << "************ at ************\n"
		 << endl;

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
	catch (const std::out_of_range &e)
	{
		cout << "catch out_of_range" << endl;
	}

	cout << "\n***********************************\n"
		 << endl;
}

static void front_test()
{
	cout << "************ front ************\n"
		 << endl;

	PRE::vector<Number> v(3, 42);
	const PRE::vector<Number> &cv = v;

	cout << v.front() << endl;
	cout << cv.front() << endl;

	cout << "\n***********************************\n"
		 << endl;
}

static void back_test()
{
	cout << "************ back ************\n"
		 << endl;

	PRE::vector<Number> v(3, 42);
	const PRE::vector<Number> &cv = v;

	cout << v.back() << endl;
	cout << cv.back() << endl;

	cout << "\n***********************************\n"
		 << endl;
}

static void data_test()
{
	cout << "************ data ************\n"
		 << endl;

	PRE::vector<Number> v(3, 42);
	const PRE::vector<Number> &cv = v;

	cout << *(v.data()) << endl;
	cout << *(cv.data()) << endl;

	cout << "\n***********************************\n"
		 << endl;
}
*/

void map_test()
{
	constructor_test();
	copy_operator_test();
	get_allocator_test();

	// Element access
	access_operator_test();

	// Iterators
	iterator_test();
	const_iterator_test();
	reverse_iterator_test();
	const_reverse_iterator_test();

	// Capacity
	empty_test();
	size_test();
	max_size_test();

	// Modifiers
	clear_test();
	insert_test();
	erase_test();
	swap_test();

	// Lookup
	count_test();
	find_test();
	equal_range_test();
	lower_bound_test();
	upper_bound_test();

	// Observers
	key_comp_test();
	value_comp_test();

	// Non-member functions
	comparison_operator_test();
	non_member_swap_test();
}
