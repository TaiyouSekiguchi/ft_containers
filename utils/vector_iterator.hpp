#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <iterator>
#include "iterator.hpp"

namespace ft
{

template <typename Iter>
class vector_iterator
{
	public:
		typedef Iter iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference 			reference;

	private:
		pointer 	ptr_;

	public:

		// member function
		vector_iterator()
			: ptr_(NULL)
		{
		}

		template <typename T2>
		vector_iterator(const vector_iterator<T2>& o)
			: ptr_(o.base())
		{
		}

		explicit vector_iterator(pointer ptr)
			: ptr_(ptr)
		{
		}

		vector_iterator &operator=(const vector_iterator &other)
		{
			if (this != &other)
				ptr_ = other.ptr_;
			return (*this);
		}

		virtual ~vector_iterator()
		{
		}

		pointer base() const
		{
			return (ptr_);
		}

		reference operator*() const
		{
			return (*ptr_);
		}

		pointer operator->() const
		{
			return (ptr_);
		}

		reference operator[](difference_type n) const
		{
			return (*(*this + n));
		}

		vector_iterator &operator++()
		{
			++ptr_;
			return (*this);
		}

		vector_iterator &operator--()
		{
			--ptr_;
			return (*this);
		}

		vector_iterator operator++(int)
		{
			vector_iterator tmp = *this;
			++ptr_;
			return (tmp);
		}

		vector_iterator operator--(int)
		{
			vector_iterator tmp = *this;
			--ptr_;
			return (tmp);
		}

		vector_iterator operator+(difference_type n) const
		{
			return (vector_iterator(ptr_ + n));
		}

		vector_iterator operator-(difference_type n) const
		{
			return (vector_iterator(ptr_ - n));
		}

		vector_iterator &operator+=(difference_type n)
		{
			ptr_ += n;
			return (*this);
		}

		vector_iterator &operator-=(difference_type n)
		{
			ptr_ -= n;
			return (*this);
		}

		/*
		** ex. ft::reverse_iterator<ft::vector<int>::const_iterator> it1 =
		*a1.rbegin();
		operator vector_iterator<const T>() const
		{
			return (vector_iterator<const T>(ptr_));
		}
		*/

}; // class vector_iterator

// Non-member functions

template <class Iterator1, class Iterator2>
bool operator==(const ft::vector_iterator<Iterator1> &lhs,
				const ft::vector_iterator<Iterator2> &rhs)
{
	return lhs.base() == rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator!=(const ft::vector_iterator<Iterator1> &lhs,
				const ft::vector_iterator<Iterator2> &rhs)
{
	return !(lhs == rhs);
}

template <class Iterator1, class Iterator2>
bool operator<(const ft::vector_iterator<Iterator1> &lhs,
				const ft::vector_iterator<Iterator2> &rhs)
{
	return lhs.base() < rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<=(const ft::vector_iterator<Iterator1> &lhs,
				const ft::vector_iterator<Iterator2> &rhs)
{
	return rhs < lhs;
}

template <class Iterator1, class Iterator2>
bool operator>(const ft::vector_iterator<Iterator1> &lhs,
				const ft::vector_iterator<Iterator2> &rhs)
{
	return rhs < lhs;
}

template <class Iterator1, class Iterator2>
bool operator>=(const ft::vector_iterator<Iterator1> &lhs,
				const ft::vector_iterator<Iterator2> &rhs)
{
	return lhs < rhs;
}

template <class Iter>
ft::vector_iterator<Iter> operator+(
	typename ft::vector_iterator<Iter>::difference_type n,
	const ft::vector_iterator<Iter> &it)
{
	return ft::vector_iterator<Iter>(it.base() + n);
}

template <class Iterator>
typename ft::vector_iterator<Iterator>::difference_type operator-(
	const ft::vector_iterator<Iterator> &lhs,
	const ft::vector_iterator<Iterator> &rhs)
{
	return lhs.base() - rhs.base();
}

} // namespace ft

#endif // VECTOR_ITERATOR_HPP
