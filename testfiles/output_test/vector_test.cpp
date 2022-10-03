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

	cout << "\n***********************************\n\n" << endl;
}

void vector_test()
{
	constructor_test();

}
