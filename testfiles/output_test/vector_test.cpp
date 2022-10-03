#include "test.hpp"

static void vector_constructor_test()
{
	std::cout << "[ vector_constructor_test ]" << std::endl;

	PRE::vector<int> v;

	std::cout << "empty()  : " << v.empty() << std::endl;
	std::cout << "size()   : " << v.size() << std::endl;
}

void vector_test()
{
	vector_constructor_test();
}
