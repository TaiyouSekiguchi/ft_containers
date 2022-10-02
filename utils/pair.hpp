#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
template<class T1, class T2>
struct pair
{
	// Member types
	typedef T1		first_type;
	typedef T2 		second_type;

	// Member objects
	first_type		first;
	second_type		second;

	// Member functions
	pair() : first(), second() {}
	pair(const T1& x, const T2& y) : first(x), second(y) {}
	template<class U1, class U2>
	pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
	pair(const pair& p) : first(p.first), second(p.second) {}
	pair& operator=(const pair& p)
	{
		if (this != &p)
		{
			first = p.first;
			second = p.second;
		}
		return *this;
	}
}; // struct pair

// Non-member functions
template<class T1, class T2>
ft::pair<T1, T2> make_pair(T1 t, T2 u)
{
	return (pair<T1, T2>(t, u));
}
template<class T1, class T2>
bool operator==(const ft::pair<T1, T2>& x, const ft::pair<T1, T2>& y)
{
	return x.first == y.first && x.second == y.second;
}
template<class T1, class T2>
bool operator!=(const ft::pair<T1, T2>& x, const ft::pair<T1, T2>& y)
{
	return !(x == y);
}
template<class T1, class T2>
bool operator<(const ft::pair<T1, T2>& x, const ft::pair<T1, T2>& y)
{
	return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
}
template<class T1, class T2>
bool operator>(const ft::pair<T1, T2>& x, const ft::pair<T1, T2>& y)
{
	return y < x;
}
template<class T1, class T2>
bool operator>=(const ft::pair<T1, T2>& x, const ft::pair<T1, T2>& y)
{
	return !(x < y);
}
template<class T1, class T2>
bool operator<=(const ft::pair<T1, T2>& x, const ft::pair<T1, T2>& y)
{
	return !(y < x);
}

} // namespace ft

#endif // PAIR_HPP
