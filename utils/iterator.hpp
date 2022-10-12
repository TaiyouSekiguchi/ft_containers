#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iterator>

namespace ft
{

// tags
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Iterator>
struct iterator_traits
{
	typedef typename Iterator::difference_type 		difference_type;
	typedef typename Iterator::value_type 			value_type;
	typedef typename Iterator::pointer 				pointer;
	typedef typename Iterator::reference 			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

template <class T>
struct iterator_traits<T*>
{
	typedef ptrdiff_t 								difference_type;
	typedef T 										value_type;
	typedef T* 										pointer;
	typedef T& 										reference;
	typedef std::random_access_iterator_tag 		iterator_category;
};

template <class T>
struct iterator_traits<const T*>
{
	typedef ptrdiff_t 								difference_type;
	typedef T 										value_type;
	typedef const T* 								pointer;
	typedef const T& 								reference;
	typedef std::random_access_iterator_tag 		iterator_category;
};

template <class Category,
			class T,
			class Distance = std::ptrdiff_t,
			class Pointer = T*,
			class Reference = T&>
struct iterator
{
	typedef Category		iterator_category;
	typedef T 				value_type;
	typedef Distance 		difference_type;
	typedef Pointer 		pointer;
	typedef Reference 		reference;
};

template <class Iter>
class reverse_iterator
	: public iterator<typename ft::iterator_traits<Iter>::iterator_category,
						typename ft::iterator_traits<Iter>::value_type,
						typename ft::iterator_traits<Iter>::difference_type,
						typename ft::iterator_traits<Iter>::pointer,
						typename ft::iterator_traits<Iter>::reference>
{
	protected:
		Iter current_;
		typedef ft::iterator_traits<Iter>				traits_type;

	public:
		// alias
		typedef Iter									iterator_type;
		typedef typename traits_type::iterator_category iterator_category;
		typedef typename traits_type::value_type		value_type;
		typedef typename traits_type::difference_type	difference_type;
		typedef typename traits_type::pointer 			pointer;
		typedef typename traits_type::reference			reference;

		// constructor
		reverse_iterator()
			: current_()
		{
		}

		explicit reverse_iterator(iterator_type x)
			: current_(x)
		{
		}

		template <class U>
		reverse_iterator(const reverse_iterator<U> &other)
			: current_(other.base())
		{
		}

		// destructor
		virtual ~reverse_iterator()
		{
		}

		// copy operator
		template <class U>
		reverse_iterator& operator=(const ft::reverse_iterator<U>& other)
		{
			current_ = other.base();
			return (*this);
		}

		// function
		iterator_type base() const
		{
			return (current_);
		}

		reference operator*() const
		{
			Iter tmp = current_;
			return (*--tmp);
		}

		pointer operator->() const
		{
			return (&(operator*()));
		}

		reference operator[](difference_type n) const
		{
			return (*(*this + n));
		}

		reverse_iterator &operator++()
		{
			--current_;
			return (*this);
		}

		reverse_iterator &operator--()
		{
			++current_;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--current_;
			return (tmp);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++current_;
			return (tmp);
		}

		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(current_ - n);
		}

		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(current_ + n);
		}

		reverse_iterator &operator+=(difference_type n)
		{
			current_ -= n;
			return (*this);
		}

		reverse_iterator &operator-=(difference_type n)
		{
			current_ += n;
			return (*this);
		}

}; // class reverse_iterator

template <class Iterator1, class Iterator2>
bool operator==(const ft::reverse_iterator<Iterator1> &lhs,
				const ft::reverse_iterator<Iterator2> &rhs)
{
	return lhs.base() == rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator!=(const ft::reverse_iterator<Iterator1> &lhs,
				const ft::reverse_iterator<Iterator2> &rhs)
{
	return !(lhs == rhs);
}

template <class Iterator1, class Iterator2>
bool operator<(const ft::reverse_iterator<Iterator1> &lhs,
				const ft::reverse_iterator<Iterator2> &rhs)
{
	return rhs.base() < lhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>(const ft::reverse_iterator<Iterator1> &lhs,
				const ft::reverse_iterator<Iterator2> &rhs)
{
	return lhs < rhs;
}

template <class Iterator1, class Iterator2>
bool operator<=(const ft::reverse_iterator<Iterator1> &lhs,
				const ft::reverse_iterator<Iterator2> &rhs)
{
	return !(rhs < lhs);
}

template <class Iterator1, class Iterator2>
bool operator>=(const ft::reverse_iterator<Iterator1> &lhs,
				const ft::reverse_iterator<Iterator2> &rhs)
{
	return !(lhs < rhs);
}

template <class Iter>
ft::reverse_iterator<Iter> operator+(
	typename ft::reverse_iterator<Iter>::difference_type n,
	const ft::reverse_iterator<Iter> &it)
{
	return ft::reverse_iterator<Iter>(it.base() - n);
}

template <class Iterator>
typename ft::reverse_iterator<Iterator>::difference_type operator-(
	const ft::reverse_iterator<Iterator> &lhs,
	const ft::reverse_iterator<Iterator> &rhs)
{
	return rhs.base() - lhs.base();
}

template <class InputIterator, class Distance>
void advance(InputIterator &it, Distance n)
{
	while (n > 0)
	{
		++it;
		--n;
	}
	while (n < 0)
	{
		--it;
		++n;
	}
	return;
}

template <class InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type distance(
	InputIterator first, InputIterator last)
{
	typename ft::iterator_traits<InputIterator>::difference_type ret = 0;
	while (first != last)
	{
		++first;
		++ret;
	}
	return (ret);
}

} // namespace ft

#endif //ITERATOR_HPP
