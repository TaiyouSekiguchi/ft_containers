#include <iostream>
#include <string>
#include <array>

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"
#define SUCCESS 1
#define FAILURE 0

#ifdef FT
# include "../containers/vector.hpp"
# define PRE ft
#else
# include <vector>
# define PRE std
#endif

void	result_put(const PRE::vector<int>& result)
{
	for (int i = 0; i < result.size(); i++)
	{
		if (result.at(i) == SUCCESS)
			std::cout << GRN "TEST " << i + 1 << " : SUCCESS!!" NC << std::endl;
		else
			std::cout << RED "TEST " << i + 1 << " : FAILURE!!" NC << std::endl;
	}
}

int	test1(void)
{
	PRE::vector<int> v;

	if (!v.empty()
		|| v.size() != 0)
		return (FAILURE);
	else
		return (SUCCESS);
}

int	test2(void)
{
	PRE::vector<int> v(5, 42);

	for (int i = 0; i < v.size(); i++)
	{
		if (v[1] != 42)
			return (FAILURE);
	}
	if (v.size() != 5)
		return (FAILURE);

	return (SUCCESS);
}

int	test3(void)
{
	PRE::vector<int> v1(5, 42);
	PRE::vector<int> v2(std::begin(v1), std::end(v1));

	for (int i = 0; i < v2.size(); i++)
	{
		if (v2[1] != 42)
			return (FAILURE);
	}
	if (v2.size() != 5)
		return (FAILURE);

	return (SUCCESS);
}

int	test4(void)
{
	PRE::vector<int> v1(5, 33);
	PRE::vector<int> v2(v1);

	for (int i = 0; i < v2.size(); i++)
	{
		if (v2[1] != 33)
			return (FAILURE);
	}
	if (v2.size() != 5)
		return (FAILURE);

	return (SUCCESS);
}

int	test5(void)
{
	PRE::vector<int> v1(5, 33);
	PRE::vector<int> v2;

	v2 = v1;
	if (v1 == v2)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	test6(void)
{
	PRE::vector<int> v(5, 33);
	const PRE::vector<int> &cv = v;

	PRE::vector<int>::iterator i = v.begin();
	PRE::vector<int>::const_iterator ci = cv.begin();

	if (*i == 33 && *ci == 33)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	test7(void)
{
	PRE::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	const PRE::vector<int> &cv = v;

	PRE::vector<int>::iterator i = v.begin();
	PRE::vector<int>::iterator last = v.end();

	PRE::vector<int>::const_iterator ci = cv.begin();
	PRE::vector<int>::const_iterator clast = cv.end();

	int n = 1;
	for (; i != last; ++i)
	{
		if (*i != n)
			return (FAILURE);
		++n;
	}

	int cn = 1;
	for (; ci != clast; ++ci)
	{
		if (*ci != cn)
			return (FAILURE);
		++cn;
	}

	return (SUCCESS);
}

/*
int	test8(void)
{
	PRE::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	const PRE::vector<int> &cv = v;

	PRE::vector<int>::reverse_iterator i = v.rbegin();
	PRE::vector<int>::reverse_iterator last = v.rend();

	PRE::vector<int>::const_reverse_iterator ci = cv.rbegin();
	PRE::vector<int>::const_reverse_iterator clast = cv.rend();

	int n = 5;
	for (; i != last; ++i)
	{
		if (*i != n)
			return (FAILURE);
		--n;
	}

	int cn = 5;
	for (; ci != clast; ++ci)
	{
		if (*ci != cn)
			return (FAILURE);
		--cn;
	}

	return (SUCCESS);
}
*/

int	test9(void)
{
	PRE::vector<int> v(7, 42);

	if (v.size() == 7)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	test10(void)
{
	PRE::vector<int> v(5, 42);

	v.resize(7);
	if (v[0] != 42
		|| v[1] != 42
		|| v[2] != 42
		|| v[3] != 42
		|| v[4] != 42
		|| v[5] != 0
		|| v[6] != 0
		|| v.size() != 7)
		return (FAILURE);

	v.resize(3);
	if (v[0] != 42
		|| v[1] != 42
		|| v[2] != 42
		|| v.size() != 3)
		return (FAILURE);

	return (SUCCESS);
}

int	test11(void)
{
	{
		PRE::vector<int> v;
		v.reserve(3);

		std::size_t cap = v.capacity();
		if (cap != 3)
			return (FAILURE);
	}

	{
		PRE::vector<int> v(3, 42);
		v.erase(v.begin());

		std::size_t cap = v.capacity();
		if (cap != 3)
			return (FAILURE);
	}

	return (SUCCESS);
}

int	test12(void)
{
	{
		PRE::vector<int> v;

		if (!v.empty())
			return (FAILURE);
	}

	{
		PRE::vector<int> v(3, 42);

		if (v.empty())
			return (FAILURE);
	}

	return (SUCCESS);
}

int	test13(void)
{
	PRE::vector<int> v;

	v.reserve(5);
	if (v.capacity() < 5)
		return (FAILURE);

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	if (v.capacity() == 5)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	test14(void)
{
	PRE::vector<int> v;
	v.push_back(3);
	v.push_back(1);
	v.push_back(4);

	if ( v[0] != 3
		|| v[1] != 1
		|| v[2] != 4)
		return (FAILURE);
	else
		return (SUCCESS);
}

int test15(void)
{
	PRE::vector<int> v;
	v.push_back(3);
	v.push_back(1);
	v.push_back(4);

	if (v.at(2) != 4)
		return (FAILURE);

	try
	{
		int &y = v.at(3);
	}
	catch (std::out_of_range &ex)
	{
		return (SUCCESS);
	}
	return (FAILURE);
}

int test16(void)
{
	PRE::vector<int> v;
	v.push_back(3);
	v.push_back(1);
	v.push_back(4);

	int *p = v.data();
	if (*p != 3)
		return (FAILURE);
	p++;
	if (*p != 1)
		return (FAILURE);
	p++;
	if (*p != 4)
		return (FAILURE);
	return (SUCCESS);
}

int test17(void)
{
	PRE::vector<int> v;
	v.push_back(3);
	v.push_back(1);
	v.push_back(4);

	int &x = v.front();

	if (x == 3)
		return (SUCCESS);
	else
		return (FAILURE);
}

int test18(void)
{
	PRE::vector<int> v;
	v.push_back(3);
	v.push_back(1);
	v.push_back(4);

	int &x = v.back();

	if (x == 4)
		return (SUCCESS);
	else
		return (FAILURE);
}

int test19(void)
{
	PRE::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	const std::array<int, 4> data = {4, 3, 2, 1};

	v.assign(data.begin(), data.end());
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i] != v.size() - i)
			return (FAILURE);
	}

	v.assign(4, 42);
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i] != 42)
			return (FAILURE);
	}
	return (SUCCESS);
}

int test20(void)
{
	PRE::vector<int> v;

	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] != i)
			return (FAILURE);
	}
	if (v.size() != 5)
		return (FAILURE);

	return (SUCCESS);
}

int test21(void)
{
	PRE::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	v.pop_back();
	v.pop_back();

	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] != i + 1)
			return (FAILURE);
	}
	if (v.size() != 3)
		return (FAILURE);

	return (SUCCESS);
}

int test22(void)
{
	PRE::vector<std::string> v;
	v.push_back("aaa");
	v.push_back("bbb");
	v.push_back("ccc");

	std::string s1 = "ddd";
	v.insert(v.begin() + 1, s1);  // "aaa" "ddd" "bbb" "ccc"

	std::string s2 = "eee";
	v.insert(v.begin() + 2, 3, s2); // "aaa" "ddd" "eee" "eee" "eee" "bbb" "ccc"

	PRE::vector<std::string> add;
	add.push_back("xxx");
	add.push_back("yyy");
	add.push_back("zzz");

	v.insert(v.begin() + v.size(), add.begin(), add.end()); // "aaa" "ddd" "eee" "eee" "eee" "bbb" "ccc" "xxx" "yyy" "zzz"

	if (v[0] != "aaa"
		|| v[1] != "ddd"
		|| v[2] != "eee"
		|| v[3] != "eee"
		|| v[4] != "eee"
		|| v[5] != "bbb"
		|| v[6] != "ccc"
		|| v[7] != "xxx"
		|| v[8] != "yyy"
		|| v[9] != "zzz"
		|| v.size() != 10)
		return (FAILURE);
	return (SUCCESS);
}

int test23(void)
{
	PRE::vector<std::string> v;
	v.push_back("aaa");
	v.push_back("marvin");
	v.push_back("bbb");
	v.push_back("tmp");
	v.push_back("tmp");
	v.push_back("tmp");
	v.push_back("ccc");
	v.push_back("ddd");
	v.push_back("eee");

	v.erase(v.begin() + 1);
	v.erase(v.begin() + 2, v.begin() + 5);

	if (v[0] != "aaa"
		|| v[1] != "bbb"
		|| v[2] != "ccc"
		|| v[3] != "ddd"
		|| v[4] != "eee"
		|| v.size() != 5)
		return (FAILURE);
	return (SUCCESS);
}

int test24(void)
{
	PRE::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);

	PRE::vector<int> v2;
	v2.push_back(4);
	v2.push_back(5);
	v2.push_back(6);

	v1.swap(v2);

	for (int i = 0; i < v1.size(); i++)
	{
		if (v1[i] != i + 4)
			return (FAILURE);
	}
	for (int i = 0; i < v2.size(); i++)
	{
		if (v2[i] != i + 1)
			return (FAILURE);
	}
	return (SUCCESS);
}

int test25(void)
{
	PRE::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	v.clear();

	if (v.empty())
		return (SUCCESS);
	else
		return (FAILURE);
}

int test26(void)
{
	std::allocator<int> alloc;
	PRE::vector<int> v(alloc);

	std::allocator<int> result = v.get_allocator();

	if (result != alloc)
		return (FAILURE);
	return (SUCCESS);
}

int test27(void)
{
	PRE::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	PRE::vector<int> v2;
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	PRE::vector<int> v3;
	v3.push_back(1);
	v3.push_back(2);
	v3.push_back(3);
	v3.push_back(4);

	if (v1 == v2 && v1 != v3)
		return (SUCCESS);
	return (FAILURE);
}

int test28(void)
{
	PRE::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	PRE::vector<int> v2;
	v2.push_back(4);
	v2.push_back(5);
	v2.push_back(6);

	if (v1 < v2)
		return (SUCCESS);
	else
		return (FAILURE);
}

int test29(void)
{
	PRE::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	PRE::vector<int> v2;
	v2.push_back(4);
	v2.push_back(5);
	v2.push_back(6);

	if (v1 <= v2)
		return (SUCCESS);
	else
		return (FAILURE);
}

int test30(void)
{
	PRE::vector<int> v1;
	v1.push_back(4);
	v1.push_back(5);
	v1.push_back(6);
	PRE::vector<int> v2;
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);

	if (v1 > v2)
		return (SUCCESS);
	else
		return (FAILURE);
}

int test31(void)
{
	PRE::vector<int> v1;
	v1.push_back(4);
	v1.push_back(5);
	v1.push_back(6);
	PRE::vector<int> v2;
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);

	if (v1 >= v2)
		return (SUCCESS);
	else
		return (FAILURE);
}

int main()
{
	PRE::vector<int> result;

	std::cout << "VECTOR TEST START!!\n" << std::endl;

	result.push_back(test1());
	result.push_back(test2());
	result.push_back(test3());
	result.push_back(test4());
	result.push_back(test5());
	result.push_back(test6());
	result.push_back(test7());
	//result.push_back(test8());
	result.push_back(0);
	result.push_back(test9());
	result.push_back(test10());
	result.push_back(test11());
	result.push_back(test12());
	result.push_back(test13());
	result.push_back(test14());
	result.push_back(test15());
	result.push_back(test16());
	result.push_back(test17());
	result.push_back(test18());
	result.push_back(test19());
	result.push_back(test20());
	result.push_back(test21());
	result.push_back(test22());
	result.push_back(test23());
	result.push_back(test24());
	result.push_back(test25());
	result.push_back(test26());
	result.push_back(test27());
	result.push_back(test28());
	result.push_back(test29());
	result.push_back(test30());
	result.push_back(test31());

	result_put(result);
	std::cout << "\nVECTOR TEST FINISH!!" << std::endl;
}
