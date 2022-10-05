#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <iostream>

class Number
{
	public:
		Number();
		Number(int n);
		Number(const Number &o);
		~Number();
		Number &operator=(const Number &o);

		bool operator==(const Number &o) const;
		bool operator!=(const Number &o) const;
		bool operator<(const Number &o) const;
		bool operator<=(const Number &o) const;
		bool operator>(const Number &o) const;
		bool operator>=(const Number &o) const;

		int getNum() const;

	private:
		int num_;
}; // class Number

std::ostream& operator<<(std::ostream &o, const Number &i);

#endif // NUMBER_HPP
