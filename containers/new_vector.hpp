#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iterator>
#include <algorithm>
#include <limits>

#include "../utils/algorithm.hpp"
#include "../utils/iterator.hpp"
#include "../utils/vector_iterator.hpp"
#include "../utils/util.hpp"

namespace ft
{

template <typename T, typename Allocator = std::allocator<T> >
class vector
{
public:
	// Member types
	typedef T 										value_type;
	typedef Allocator 								allocator_type;
	typedef std::size_t 							size_type;
	typedef std::ptrdiff_t							difference_type;
	typedef value_type&								reference;
	typedef const value_type&						const_reference;
	typedef typename Allocator::pointer 			pointer;
	typedef typename Allocator::const_pointer		const_pointer;
	typedef ft::vector_iterator<pointer>			iterator;
	typedef ft::vector_iterator<const_pointer>		const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	// Member functions
	// constructor
	vector()
		: first_(NULL)
		, last_(NULL)
		, reserved_last_(NULL)
		, alloc_(allocator_type())
	{
	}

	explicit vector(const allocator_type &alloc)
		: first_(NULL)
		, last_(NULL)
		, reserved_last_(NULL)
		, alloc_(alloc)
	{
	}

	explicit vector(size_type count,
					const T &value = T(),
					const Allocator &alloc = Allocator())
		: first_(NULL)
		, last_(NULL)
		, reserved_last_(NULL)
		, alloc_(alloc)
	{
		if (count != 0)
		{
			allocate(count);
			construct_range(first_, last_, value);
		}
	}

private:
	template <typename InputIt>
	void range_constructor_impl(InputIt first, InputIt  last, std::input_iterator_tag)
	{
		for (; first != last; ++first)
			push_back(*first);
	}

	template <typename ForwardIterator>
	void range_constructor_impl(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
	{
		size_type size = std::distance(first, last);
		if (size == 0)
			return;
		allocate(size);
		construct_range(first_, last_, first);
	}

public:
	template <typename InputIt>
	vector(InputIt first,
			typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last,
			const Allocator &alloc = Allocator())
		: first_(NULL)
		, last_(NULL)
		, reserved_last_(NULL)
		, alloc_(alloc)
	{
		range_constructor_impl(first, last, typename ft::iterator_traits<InputIt>::iterator_category());
	}

	vector(const vector &o)
		: first_(NULL)
		, last_(NULL)
		, reserved_last_(NULL)
		, alloc_((o.alloc_))
	{
		size_type size = o.size();
		if (size == 0)
			return;
		allocate(size);
		construct_range(first_, last_, o.first_);
	}

	// destructor
	~vector()
	{
		clear();
		deallocate();
	}

	vector &operator=(const vector &o)
	{
		if (this != &o)
		{
			if (alloc_ != o.alloc_)
			{
				clear();
				deallocate();
			}
			alloc_ = o.alloc_;
			assign(o.first_, o.last_);
		}
		return (*this);
	}

	iterator 				begin() 		{ return (iterator(first_)); }
	const_iterator 			begin() const	{ return (const_iterator(first_)); }
	iterator				end()			{ return (iterator(last_)); }
	const_iterator			end() const		{ return (const_iterator(last_)); }
	reverse_iterator 		rbegin()		{ return (reverse_iterator(last_)); }
	const_reverse_iterator	rbegin() const	{ return (const_reverse_iterator(const_iterator(last_))); }
	reverse_iterator		rend()			{ return (reverse_iterator(first_)); }
	const_reverse_iterator	rend() const	{ return (const_reverse_iterator(const_iterator((first_)))); }

	// function
	size_type 	size() const 			{ return (last_ - first_);}
	bool 		empty() const 				{ return (first_ == last_);}
	size_type	capacity() const	{ return (reserved_last_ - first_); }
	size_type	max_size() const
	{
		return (std::min<size_type>(alloc_.max_size(), std::numeric_limits<difference_type>::max()));
	}

	void	resize(size_type n, value_type val = value_type())
	{
		if (n < size())
			erase(iterator(first_ + n), end());
		else
			insert(end(), n - size(), val);
	}

	void reserve(size_type n)
	{
		if (n < capacity())
			return;

		pointer		old_first = first_;
		pointer		old_last = last_;
		size_type	old_size = size();
		size_type 	old_capacity = capacity();
		allocate(n);
		last_ = first_ + old_size;
		std::uninitialized_copy(old_first, old_last, first_);
		destroy_range(old_first, old_last);
		alloc_.deallocate(old_first, old_capacity);
	}

	reference 		operator[](size_type i)			{ return first_[i]; }
	const_reference	operator[](size_type i) const 	{ return first_[i]; }

	reference at(size_type i)
	{
		if (i >= size())
			throw std::out_of_range("index is out of range.");
		return (first_[i]);
	}
	const_reference at(size_type i) const
	{
		if (i >= size())
			throw std::out_of_range("index is out of range.");
		return (first_[i]);
	}
	reference			front()			{ return (*first_); }
	const_reference 	front() const	{ return (*first_); }
	reference 			back() 			{ return (*(last_ - 1)); }
	const_reference		back() const	{ return (*(last_ - 1)); }
	value_type*			data() 			{ return (first_); }
	const value_type*	data() const 	{ return (first_); }

private:
	template <typename InputIterator>
	void assign_impl(InputIterator first, InputIterator last, std::input_iterator_tag)
	{
		clear();
		for (; first != last; ++first)
			push_back(*first);
	}

	template <typename ForwardIterator>
	void assign_impl(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
	{
		size_type new_size = std::distance(first, last);
		if (new_size <= capacity())
		{
			pointer new_last = first_ + new_size;
			if (last_ < new_last)
				construct_range(last_, new_last);
			std::copy(first, last, first_);
			if (new_last < last_)
				destroy_range(new_last, last_);
			last_ = new_last;
		}
		else
		{
			clear();
			deallocate();
			allocate(new_size);
			std::uninitialized_copy(first, last, first_);
		}
	}

public:
	template <typename InputIterator>
	typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
		assign(InputIterator first, InputIterator last)
	{
		assign_impl(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
	}

	void assign(size_type n, const value_type& val)
	{
		if (n <= capacity())
		{
			pointer new_last = first_ + n;
			if (last_ < new_last)
				construct_range(last_, new_last);
			std::fill(first_, new_last, val);
			if (new_last < last_)
				destroy_range(new_last, last_);
			last_ = new_last;
		}
		else
		{
			clear();
			deallocate();
			allocate(n);
			std::uninitialized_fill(first_, last_, val);
		}
	}

	void push_back(const value_type& val)
	{
		if (last_ == reserved_last_)
			reserve(recommend_size(size() + 1));
		alloc_.construct(last_, val);
		last_+= 1;
	}

	void pop_back(void)
	{
		alloc_.destroy(last_ - 1);
		last_ -= 1;
	}

	iterator insert(iterator position, const value_type& val)
	{
		difference_type pos_dist = std::distance(first_, position.base());
		insert(position, 1, val);
		return (iterator(first_ + pos_dist));
	}

	void insert(iterator position, size_type n, const value_type& val)
	{
		difference_type pos_dist = std::distance(first_, position.base());
		size_type new_size = size() + n;
		if (capacity() < new_size)
		{
			reserve(recommend_size(new_size));
			position = begin() + pos_dist;
		}
		pointer new_last = last_ + n;
		construct_range(last_, new_last);
		std::copy_backward(position.base(), last_, new_last);
		std::fill(position.base(), position.base() + n, val);
		last_ = new_last;
	}

private:
	template <typename InputIterator>
	void insert_impl(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag)
	{
		for (; first != last; ++first, ++position)
			position = insert(position, *first);
	}

	template <typename ForwardIterator>
	void insert_impl(iterator position, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
	{
		size_type n = std::distance(first, last);
		difference_type pos_dist = std::distance(first_, position.base());
		size_type new_size = size() + n;
		if (capacity() < new_size)
		{
			reserve(recommend_size(new_size));
			position = begin() + pos_dist;
		}
		pointer new_last = last_ + n;
		construct_range(last_, new_last);
		std::copy_backward(position.base(), last_, new_last);
		std::copy(first, last, position.base());
		last_ = new_last;
	}

public:
	template <typename InputIterator>
	typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
		insert(iterator position, InputIterator first, InputIterator last)
	{
		insert_impl(position, first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
	}

	iterator erase(iterator position)
	{
		std::copy(position.base() + 1, last_, position.base());
		pop_back();
		return (position);
	}

	iterator erase(iterator first, iterator last)
	{
		size_type erase_size = std::distance(first.base(), last.base());
		pointer new_last = last_ - erase_size;
		std::copy(last.base(), last_, first.base());
		destroy_range(new_last, last_);
		last_ = new_last;
		return (first);
	}

	void swap(vector& o)
	{
		std::swap(alloc_, o.alloc_);
		std::swap(first_, o.first_);
		std::swap(last_, o.last_);
		std::swap(reserved_last_, o.reserved_last_);
	}

	void clear()
	{
		destroy_range(first_, last_);
		last_ = first_;
	}

	allocator_type get_allocator() const
	{
		return (alloc_);
	}

private:
	// function
	void allocate(size_type n)
	{
		if (n > max_size())
			throw std::length_error("vector");
		first_ = alloc_.allocate(n);
		last_ = first_ + n;
		reserved_last_ = last_;
	}

	void deallocate()
	{
		if (first_ == NULL)
			return;
		alloc_.deallocate(first_, capacity());
		first_ = NULL;
		last_ = NULL;
		reserved_last_ = NULL;
	}

	void construct_range(pointer first, pointer last)
	{
		for (pointer p = first; p < last; ++p)
			alloc_.construct(p, value_type());
	}

	void construct_range(pointer first, pointer last, value_type& val)
	{
		for (pointer p = first; p < last; ++p)
			alloc_.construct(p, val);
	}

	template <typename ForwardIterator>
	typename ft::enable_if<!ft::is_integral<ForwardIterator>::value, void>::type
		construct_range(pointer first, pointer last, ForwardIterator val_itr)
	{
		for (pointer p = first; p < last; ++p, ++val_itr)
			alloc_.construct(p, *val_itr);
	}

	void destroy_range(pointer first, pointer last)
	{
		for (pointer p = first; p < last; ++p)
			alloc_.destroy(p);
	}

	size_type recommend_size(size_type new_size) const
	{
		size_type maxsize = max_size();
		if (maxsize < new_size)
			throw std::length_error("vector");
		size_type cap = capacity();
		if (maxsize / 2 <= cap)
			return (maxsize);
		return (std::max<size_type>(new_size, cap * 2));
	}

protected:
	// data member
	pointer first_;
	pointer last_;
	pointer reserved_last_;
	allocator_type alloc_;

}; // class vector

// Nom-member function
template <typename T, typename Allocator>
bool operator==(const ft::vector<T, Allocator> &x, const ft::vector<T, Allocator> &y)
{
	return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

template <typename T, typename Allocator>
bool operator!=(const ft::vector<T, Allocator> &x, const ft::vector<T, Allocator> &y)
{
	return !(x == y);
}

template <typename T, typename Allocator>
bool operator<(const ft::vector<T, Allocator> &x, const ft::vector<T, Allocator> &y)
{
	return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <typename T, typename Allocator>
bool operator>(const ft::vector<T, Allocator> &x, const ft::vector<T, Allocator> &y)
{
	return y < x;
}

template <typename T, typename Allocator>
bool operator>=(const ft::vector<T, Allocator> &x, const ft::vector<T, Allocator> &y)
{
	return !(x < y);
}

template <typename T, typename Allocator>
bool operator<=(const ft::vector<T, Allocator> &x, const ft::vector<T, Allocator> &y)
{
	return !(y < x);
}

template <class T, class Alloc>
void swap(ft::vector<T, Alloc> &x, ft::vector<T, Alloc> &y)
{
	x.swap(y);
}

} // namespace ft

#endif
