#include <iostream>
#include <string>
#include <array>
#include <vector>

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"
#define SUCCESS 1
#define FAILURE 0

#ifdef FT
#include "../containers/map.hpp"
#define PRE ft
#else
#include <map>
#define PRE std
#endif

void result_put(const std::vector<int> &result)
{
	for (int i = 0; i < result.size(); i++)
	{
		if (result.at(i) == SUCCESS)
			std::cout << GRN "TEST " << i + 1 << " : SUCCESS!!" NC << std::endl;
		else
			std::cout << RED "TEST " << i + 1 << " : FAILURE!!" NC << std::endl;
	}
}

int test1(void)
{
	PRE::map<std::string, int> m;

	if (!m.empty() || m.size() != 0)
		return (FAILURE);
	else
		return (SUCCESS);
}

int test2(void)
{
	PRE::map<std::string, int> map1;
	map1["something"] = 69;
	map1["anything"] = 199;
	map1["that thing"] = 50;

	PRE::map<std::string, int> iter(map1.find("anything"), map1.end());
	if (iter["something"] != 69
		|| iter["anything"] != 199
		|| iter["that thing"] != 50)
		return (FAILURE);

	return (SUCCESS);
}

int test3(void)
{
	PRE::map<std::string, int> m;
	m["something"] = 69;
	m["anything"] = 199;
	m["that thing"] = 50;

	PRE::map<std::string, int> copy(m);
	if (copy["something"] != 69
		|| copy["anything"] != 199
		|| copy["that thing"] != 50)
		return (FAILURE);

	return (SUCCESS);
}

int test4(void)
{
	PRE::map<std::string, int> m;
	m["something"] = 69;
	m["anything"] = 199;
	m["that thing"] = 50;

	PRE::map<std::string, int> copy;

	copy = m;
	if (m == copy)
		return (SUCCESS);
	else
		return (FAILURE);
}

int test5(void)
{
	int	ret;
	PRE::map<int, char> m;
	std::pair<const int, char> *p = m.get_allocator().allocate(2);

	p[0].second = 'a';
	p[1].second = 'b';

	if (p[0].second == 'a'
		&& p[1].second == 'b')
		ret = SUCCESS;
	else
		ret = FAILURE;

	return ret;
}

/*
int test6(void)
{
	PRE::map<int, char> m;
	m.insert(std::make_pair(1, 'a'));

	try
	{
		if (m.at(1) != 'a')
			return (FAILURE);
	}
	catch(const std::out_of_range& e)
	{
		return (FAILURE);
	}

	try
	{
		m.at(2);
		return (FAILURE);
	}
	catch(const std::out_of_range& e)
	{
	}
	return (SUCCESS);
}
*/

int test7(void)
{
	PRE::map<int, char> m;
	m.insert(std::make_pair(1, 'a'));

	if (m[1] == 'a')
		return SUCCESS;
	else
		return FAILURE;
}

int	test8(void)
{
	PRE::map<int, int> m;
	m[0] = 0;
	m[1] = 1;
	m[2] = 2;
	m[3] = 3;
	m[4] = 4;

	PRE::map<int, int>::iterator it;
	PRE::map<int, int>::iterator it_end;

	it = m.begin();
	it_end = m.end();

	int n = 0;
	for (; it != it_end; ++it, ++n)
	{
		if (it->second != n)
			return (FAILURE);
	}

	return (SUCCESS);
}

/*
int test9(void)
{
	PRE::map<int, int> m;
	m[0] = 0;
	m[1] = 1;
	m[2] = 2;
	m[3] = 3;
	m[4] = 4;

	PRE::map<int, int>::reverse_iterator it;
	PRE::map<int, int>::reverse_iterator it_end;

	it = m.rbegin();
	it_end = m.rend();

	int n = 4;
	for (; it != it_end; ++it)
	{
		if (it->second != n)
			return (FAILURE);
		--n;
	}

	return (SUCCESS);
}
*/

int test10(void)
{
	PRE::map<int, char> m;

	if (!m.empty())
		return FAILURE;

	m.insert(std::make_pair(42, 'a'));

	if (m.empty())
		return FAILURE;

	return SUCCESS;
}

int test11(void)
{
	PRE::map<int, char> m;

	if (m.size() != 0)
		return FAILURE;

	m.insert(std::make_pair(1, 'a'));
	m.insert(std::make_pair(2, 'b'));
	m.insert(std::make_pair(3, 'c'));

	if (m.size() != 3)
		return FAILURE;

	return SUCCESS;
}

/*
int test12(void)
{
	PRE::map<char, char> m;
	std::cout << "max_size : " << m.max_size() << std::endl;

	return SUCCESS;
}
*/

int test13(void)
{
	PRE::map<int, char> m;

	m[3] = 'C';
	m[4] = 'D';
	m[1] = 'A';
	m[2] = 'B';
	if (m.size() != 4)
		return FAILURE;

	m.clear();
	if (m.size() != 0)
		return FAILURE;

	return SUCCESS;
}

int test14(void)
{
	PRE::map<int, int> m;

	m.insert(std::make_pair(3, 3));

	PRE::map<int, int> tmp;
	tmp.insert(std::make_pair(4, 4));
	tmp.insert(std::make_pair(3, 3));
	tmp.insert(std::make_pair(5, 5));

	m.insert(tmp.begin(), tmp.end());

	PRE::map<int, int>::iterator it = m.begin();
	PRE::map<int, int>::iterator it_end = m.end();

	int n = 3;
	for (; it != it_end; ++it)
	{
		if (it->second != n)
			return FAILURE;
		n++;
	}
	if (m.size() != 3)
		return FAILURE;

	return SUCCESS;
}

int test15(void)
{
	PRE::map<int, char> m;

	m.insert(std::make_pair(1, 'A'));
	m.insert(std::make_pair(2, 'B'));
	m.insert(std::make_pair(3, 'C'));
	std::cout << "check1" << std::endl;
	if (m.size() != 3)
		return FAILURE;

	m.erase(1);
	std::cout << "check2" << std::endl;
	std::cout << "size : " << m.size() << std::endl;
	if (m.size() != 2)
		return FAILURE;

	m.erase(5);
	std::cout << "check3" << std::endl;
	if (m.size() != 2)
		return FAILURE;

	m.erase(m.begin(), m.end());
	std::cout << "check4" << std::endl;
	if (m.size() != 0)
		return FAILURE;
	return SUCCESS;
}

int test16(void)
{
	PRE::map<int, char> m1;
	m1.insert(std::make_pair(1, 'A'));
	m1.insert(std::make_pair(2, 'B'));
	m1.insert(std::make_pair(3, 'C'));

	PRE::map<int, char> m2;
	m2.insert(std::make_pair(4, 'D'));
	m2.insert(std::make_pair(5, 'E'));

	m1.swap(m2);
	if (m1[4] != 'D'
		|| m1[5] != 'E'
		|| m1.size() != 2)
		return FAILURE;

	if (m2[1] != 'A'
		|| m2[2] != 'B'
		|| m2[3] != 'C'
		|| m2.size() != 3)
		return FAILURE;

	return SUCCESS;
}

int test17(void)
{
	PRE::map<std::string, int> m;
	m.insert(std::make_pair("Alice", 3));
	m.insert(std::make_pair("Bob", 1));
	m.insert(std::make_pair("Carol", 4));

	if (m.count("Bob") != 1)
		return FAILURE;
	if (m.count("Marvin") != 0)
		return FAILURE;

	return SUCCESS;
}

int test18(void)
{
	PRE::map<std::string, int> m;
	m.insert(std::make_pair("Alice", 3));
	m.insert(std::make_pair("Bob", 1));
	m.insert(std::make_pair("Carol", 4));

	PRE::map<std::string, int>::iterator it;
	it = m.find("Bob");
	if (it == m.end())
		return FAILURE;

	it = m.find("Marvin");
	if (it != m.end())
		return FAILURE;

	return SUCCESS;
}

int test19(void)
{
	PRE::map<std::string, int> m;
	m.insert(std::make_pair("A", 3));
	m.insert(std::make_pair("B", 1));
	m.insert(std::make_pair("C", 4));
	m.insert(std::make_pair("D", 5));

	typedef typename PRE::map<std::string, int>::iterator iterator;

	std::pair<iterator, iterator> ret = m.equal_range("B");

	for (iterator it = ret.first; it != ret.second; ++it)
	{
		if (it->first != "B"
			|| it->second != 1)
			return FAILURE;
	}
	return SUCCESS;
}

int test20(void)
{
	PRE::map<int, int> m;
	m.insert(std::make_pair(1, 1));
	m.insert(std::make_pair(2, 2));
	m.insert(std::make_pair(3, 3));
	m.insert(std::make_pair(4, 4));
	m.insert(std::make_pair(5, 5));
	m.insert(std::make_pair(6, 6));

	typedef typename PRE::map<int, int>::iterator iterator;

	iterator it = m.lower_bound(2);
	iterator it_end = m.upper_bound(5);
	int n = 2;
	for (; it != it_end; ++it)
	{
		if (it->first != n || it->second != n)
			return FAILURE;
		++n;
	}
	return SUCCESS;
}

int test21(void)
{
	PRE::map<int, char> m;
	PRE::map<int, char>::key_compare comp = m.key_comp();

	if (comp(1,2) != 1
		|| comp(3, 2) != 0)
		return FAILURE;
	return SUCCESS;
}

/*
int test22(void)
{
	PRE::map<int, char> c;
	const PRE::map<int, char>::value_compare &comp = c.value_comp();

	std::pair<int, char> p1 = std::make_pair(1, 'a');
	std::pair<int, char> p2 = std::make_pair(2, 'b');
	std::pair<int, char> p3 = std::make_pair(3, 'c');

	if (comp(p1, p2) != 1
		|| comp(p3,p2) != 0)
		return FAILURE;
	return SUCCESS;
}
*/

int test23(void)
{
	PRE::map<int, char> m1;
	m1[0] = 'a';

	PRE::map<int, char> m2 = m1;
	if (m1 != m2)
		return FAILURE;

	m2[0] = 'b';
	if (m1 == m2)
		return FAILURE;

	return SUCCESS;
}

int test24(void)
{
	PRE::map<char, int> m1, m2;
	m1.insert(std::make_pair('a', 10));
	m1.insert(std::make_pair('b', 20));
	m1.insert(std::make_pair('c', 30));
	m2 = m1;

	if (m1 < m2)
		return FAILURE;

	m2.insert(std::make_pair('d', 40));

	if (!(m1 < m2))
		return FAILURE;

	return SUCCESS;
}

int test25(void)
{
	PRE::map<char, int> m1, m2;
	m1.insert(std::make_pair('a', 10));
	m1.insert(std::make_pair('b', 20));
	m1.insert(std::make_pair('c', 30));
	m2 = m1;

	if (!(m1 <= m2))
		return FAILURE;

	m2.insert(std::make_pair('d', 40));

	if (!(m1 < m2))
		return FAILURE;

	return SUCCESS;
}

int test26(void)
{
	PRE::map<char, int> m1, m2;
	m1.insert(std::make_pair('a', 10));
	m1.insert(std::make_pair('b', 20));
	m1.insert(std::make_pair('c', 30));
	m2 = m1;

	if (m1 > m2)
		return FAILURE;

	m1.insert(std::make_pair('d', 40));

	if (!(m1 > m2))
		return FAILURE;

	return SUCCESS;
}

int test27(void)
{
	PRE::map<char, int> m1, m2;
	m1.insert(std::make_pair('a', 10));
	m1.insert(std::make_pair('b', 20));
	m1.insert(std::make_pair('c', 30));
	m2 = m1;

	if (!(m1 >= m2))
		return FAILURE;

	m1.insert(std::make_pair('d', 40));

	if (!(m1 >= m2))
		return FAILURE;

	return SUCCESS;
}
/*
int test28(void)
{
	PRE::map<int, char> m1, m2;

	m1.insert(std::make_pair(10, 'a'));
	m1.insert(std::make_pair(20, 'b'));
	m1.insert(std::make_pair(30, 'c'));

	m2.insert(std::make_pair(5, 'd'));
	m2.insert(std::make_pair(15, 'e'));

	PRE::swap(m1, m2);

	if (m1[5] != 'd'
		|| m1[15] != 'e'
		|| m1.size() != 2)
		return FAILURE;

	if (m2[10] != 'a'
		|| m2[20] != 'b'
		|| m2[30] != 'c'
		|| m2.size() != 3)
		return FAILURE;
	return SUCCESS;
}
*/

int main()
{
	std::vector<int> result;

	std::cout << "MAP TEST START!!\n" << std::endl;

	result.push_back(test1());
	result.push_back(test2());
	result.push_back(test3());
	result.push_back(test4());
	result.push_back(test5());
	//result.push_back(test6());
	result.push_back(FAILURE);
	result.push_back(test7());
	result.push_back(test8());
	//result.push_back(test9());
	result.push_back(FAILURE);
	result.push_back(test10());
	result.push_back(test11());
	//result.push_back(test12());
	result.push_back(FAILURE);
	result.push_back(test13());
	result.push_back(test14());
	result.push_back(test15());
	//result.push_back(FAILURE);
	result.push_back(test16());
	result.push_back(test17());
	result.push_back(test18());
	result.push_back(test19());
	result.push_back(test20());
	result.push_back(test21());
	//result.push_back(test22());
	result.push_back(FAILURE);
	result.push_back(test23());
	result.push_back(test24());
	result.push_back(test25());
	result.push_back(test26());
	result.push_back(test27());
	//result.push_back(test28());
	result.push_back(FAILURE);
	/*
	result.push_back(test29());
	result.push_back(test30());
	result.push_back(test31());
	*/

	result_put(result);
	std::cout << "\nMAP TEST FINISH!!" << std::endl;
}
