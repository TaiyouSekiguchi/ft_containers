#include "Number.hpp"

Number::Number()
	: num_(0)
{
}

Number::Number(int n)
	: num_(n)
{
}

Number::Number(const Number& o)
{
	*this = o;
}

Number::~Number()
{
}

Number& Number::operator=(const Number& o)
{
	if (this != &o)
		num_ = o.num_;
	return *this;
}

int Number::getNum() const
{
	return num_;
}

std::ostream& operator<<(std::ostream& o, const Number& i)
{
	o << i.getNum();

	return o;
}
