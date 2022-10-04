#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <limits>
# include <memory>

# include "../utils/algorithm.hpp"
# include "../utils/iterator.hpp"
# include "../utils/random_access_iterator.hpp"
# include "../utils/util.hpp"

namespace ft {

template <typename T, typename Allocator = std::allocator<T> >
class vector
{
	public:
		// Member types
		typedef T														value_type;
		typedef Allocator												allocator_type;
		typedef std::size_t												size_type;
		typedef std::ptrdiff_t 											difference_type;
		typedef value_type&												reference;
		typedef const value_type&										const_reference;
		typedef typename Allocator::pointer								pointer;
		typedef typename Allocator::const_pointer						const_pointer;
		typedef typename ft::random_access_iterator<value_type>			iterator;
		typedef typename ft::random_access_iterator<const value_type>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		// Member functions
		// constructor
		vector()
			: first_(NULL)
			, last_(NULL)
			, reserved_last_(NULL)
			, alloc_(allocator_type()) {}

		explicit vector(const allocator_type &alloc)
			: first_(NULL)
			, last_(NULL)
			, reserved_last_(NULL)
			, alloc_(alloc) {}

		explicit vector(size_type count,
						const T& value = T(),
						const Allocator& alloc = Allocator())
			: first_(NULL)
			, last_(NULL)
			, reserved_last_(NULL)
			, alloc_(alloc)
		{
			resize(count, value);
		}

		template <typename InputIt>
		vector(InputIt first, InputIt last,
				const Allocator& alloc = Allocator(),
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
			: first_(NULL)
			, last_(NULL)
			, reserved_last_(NULL)
			, alloc_(alloc)
		{
			reserve(ft::distance(first, last));
			for (InputIt ite = first; ite != last; ++ite, ++last_)
			{
				construct(last_, *ite);
			}
		}

		// destructor
		~vector()
		{
			clear();
			deallocate();
		}

		// copy
		vector(const vector &r)
			: first_(NULL)
			, last_(NULL)
			, reserved_last_(NULL)
			, alloc_((r.alloc_))
		{
			reserve(r.size());
			pointer dest = first_;
			for (const_iterator src = r.begin(), last_ = r.end(); src != last_; ++dest, ++src)
			{
				construct(dest, *src);
			}
			last_ = first_ + r.size();
		}

		vector &operator=(const vector &r)
		{
			if (this == &r)
				return *this;

			if (size() == r.size())
			{
				std::copy(r.begin(), r.end(), begin());
			}
			else
				if (capacity() >= r.size())
				{
					std::copy(r.begin(), r.begin() + r.size(), begin());
					last_ = first_ + r.size();
					for (const_iterator src_iter = r.begin() + r.size(), src_end = r.end(); src_iter != src_end; ++src_iter, ++last_)
					{
						construct(last_, *src_iter);
					}
				}
				else
				{
					destroy_until(rbegin());
					reserve(r.size());
					for (const_iterator src_iter = r.begin(), src_end = r.end(); src_iter != src_end; ++src_iter, ++last_)
					{
						construct(last_, *src_iter);
					}
				}
			return *this;
		}

		// operator
		reference operator [](size_type i) { return first_[i]; }
		const_reference operator [](size_type i) const { return first_[i]; }

		// iterator
		iterator begin() { return first_; }
		const_iterator begin() const { return first_; }
		iterator end() { return last_; }
		const_iterator end() const { return last_; }
		reverse_iterator rbegin() { return reverse_iterator(last_); }
		const_reverse_iterator rbegin() const { return reverse_iterator(last_); }
		reverse_iterator rend() { return reverse_iterator(first_); }
		const_reverse_iterator rend() const { return reverse_iterator(first_); }

		// function
		size_type size() const { return end() - begin(); }
		bool empty() const { return begin() == end(); }
		size_type capacity() const { return reserved_last_ - first_; }
		size_type max_size() const
		{
			size_t div = sizeof(value_type);
			if (div == 1)
				++div;
			return std::numeric_limits<size_type>::max() / div;
		}
		reference at(size_type i)
		{
			if (i >= size())
				throw std::out_of_range("index is out of range.");

			return first_[i];
		}
		const_reference at(size_type i) const
		{
			if (i >= size())
				throw std::out_of_range("index is out of range.");

			return first_[i];
		}
		reference front() { return *first_; }
		const_reference front() const { return *first_; }
		reference back() { return *(last_ - 1); }
		const_reference back() const { return *(last_ - 1); }
		pointer data() { return first_; }
		const_pointer data() const { return first_; }
		void clear() { destroy_until(rend()); }
		void reserve(size_type sz)
		{
			if (sz <= capacity())
				return;

			pointer old_first = first_;
			pointer old_last = last_;
			size_type old_capacity = capacity();

			pointer ptr = allocate(sz);
			first_ = ptr;
			last_ = first_;
			reserved_last_ = first_ + sz;

			for (pointer old_iter = old_first; old_iter != old_last; ++old_iter, ++last_)
			{
				construct(last_, *old_iter);
			}

			for (reverse_iterator riter = reverse_iterator(old_last), rend = reverse_iterator(old_first); riter != rend; ++riter)
			{
				destroy(&*riter);
			}
			alloc_.deallocate(old_first, old_capacity);
		}

		void resize(size_type sz)
		{
			if (sz < size())
			{
				size_type diff = size() - sz;
				destroy_until(rbegin() + diff);
				last_ = first_ + sz;
			}
			else if (sz > size())
			{
				reserve(sz);
				for (; last_ != reserved_last_; ++last_)
				{
					construct(last_);
				}
			}
		}

		void resize(size_type sz, const_reference value)
		{
			if (sz < size())
			{
				size_type diff = size() - sz;
				destroy_until(rbegin() + diff);
				last_ = first_ + sz;
			}
			else if (sz > size())
			{
				reserve(sz);
				for (; last_ != reserved_last_; ++last_)
				{
					construct(last_, value);
				}
			}
		}

		void push_back(const_reference value)
		{
			if (size() + 1 > capacity())
			{
				size_type c = size();
				if (c == 0)
					c = 1;
				else
					c *= 2;

				reserve(c);
			}
			construct(last_, value);
			++last_;
		}

		void pop_back(void)
		{
			destroy(--last_);
		}

		void assign(size_type count, const T &value)
		{
			if (count > capacity())
			{
				clear();
				deallocate();

				first_ = allocate(count);
				last_ = first_;
				reserved_last_ = first_ + count;
				for (size_type i = 0; i < count; ++i)
					construct(last_++, value);
			}
			else if (count > size())
			{
				pointer ptr = first_;
				for (size_type i = 0; i < count; ++i)
				{
					if (i < size())
						*(ptr++) = value;
					else
						construct(last_++, value);
				}
			}
			else
			{
				clear();
				for (size_type i = 0; i < count; ++i)
					construct(last_++, value);
			}
		}

		template <class InputIt>
		void assign(InputIt src_first, InputIt src_last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value,
											InputIt>::type * = NULL)
		{
			size_type count = src_last - src_first;
			if (count > capacity())
			{
				clear();
				deallocate();

				first_ = allocate(count);
				last_ = first_;
				reserved_last_ = first_ + count;
				for (InputIt head = src_first; head != src_last; ++head)
					construct(last_++, *head);
			}
			else if (count > size())
			{
				pointer ptr = first_;
				for (size_type i = 0; i < count; ++i)
				{
					if (i < size())
						*(ptr++) = *src_first++;
					else
						construct(last_++, *src_first++);
				}
			}
			else
			{
				clear();
				for (InputIt head = src_first; head != src_last; ++head)
					construct(last_++, *head);
			}
		}
		iterator insert(iterator pos, const T &value)
		{
			size_type count = 1;
			difference_type offset = pos - begin();

			size_type c = capacity();
			size_type pre_c = c;
			size_type new_size = size() + count;
			while (new_size > c)
			{
				if (c == 0)
					c = 1;
				else
					c = c << 1;
				if ((c >> 1) != pre_c)
					throw std::overflow_error("vector::insert");
				pre_c = c;
			}
			reserve(c);
			for (; last_ != first_ + new_size; ++last_)
				construct(last_);

			iterator tail = last_ - 1;
			iterator range_end = begin() + offset + count - 1;
			// pos + count - 1 までmemmove
			for (; tail > range_end; --tail)
				*tail = *(tail - count);
			iterator range_begin = begin() + offset - 1;
			for (; tail > range_begin; --tail)
				*tail = value;

			return begin() + offset;
		}

		void insert(iterator pos, size_type count, const T &value)
		{
			if (count < 0)
				throw std::length_error("negative length.");
			if (count == 0)
				return;

			difference_type offset = pos - begin();
			size_type c = capacity();
			size_type pre_c = c;
			size_type new_size = size() + count;
			while (c < new_size)
			{
				if (c == 0)
					c = 1;
				else
					c = c << 1;
				if ((c >> 1) != pre_c)
					throw std::overflow_error("vector::insert");
				pre_c = c;
			}
			reserve(c);
			for (; last_ != first_ + new_size; ++last_)
				construct(last_);

			iterator tail = last_ - 1;
			iterator range_end = begin() + offset + count - 1;
			// pos + count - 1 までmemmove
			for (; tail > range_end; --tail)
				*tail = *(tail - count);
			iterator range_begin = begin() + offset - 1;
			for (; tail > range_begin; --tail)
				*tail = value;
		}

		template <class InputIt>
		void insert(iterator pos, InputIt src_first, InputIt src_last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value,
											InputIt>::type * = NULL)
		{
			difference_type count = src_last - src_first;
			if (count < 0)
				throw std::length_error("negative length.");
			if (count == 0)
				return;

			difference_type offset = pos - begin();
			size_type c = capacity();
			size_type pre_c = c;
			size_type new_size = size() + count;
			while (c < new_size)
			{
				if (c == 0)
					c = 1;
				else
					c = c << 1;
				if ((c >> 1) != pre_c)
					throw std::overflow_error("vector::insert");
				pre_c = c;
			}
			reserve(c);
			for (; last_ != first_ + new_size; ++last_)
				construct(last_);

			iterator tail = last_ - 1;
			iterator range_end = begin() + offset + count - 1;
			// pos + count - 1 までmemmove
			for (; tail > range_end; --tail)
				*tail = *(tail - count);
			iterator range_begin = begin() + offset - 1;
			--src_last;
			for (; src_last > src_first - 1; --src_last)
				*tail-- = *src_last;
		}

		iterator erase(iterator pos)
		{
			if (first_ == last_)
				return NULL;

			difference_type offset = pos - begin();

			for (iterator src = pos + 1; src < end(); ++src)
			{
				*(src - 1) = *src;
			}
			destroy(--last_);
			return (begin() + offset);
		}

		iterator erase(iterator first, iterator last)
		{
			if (first_ == last_)
				return NULL;

			difference_type return_diff = first - begin();
			difference_type destroy_diff = last - first;

			for (iterator dst = first, src = last; src < end(); ++dst, ++src)
			{
				*dst = *src;
			}
			destroy_until(rbegin() + destroy_diff);

			return (begin() + return_diff);
		}

		void swap(vector &other)
		{
			pointer save_first = other.first_;
			pointer save_last = other.last_;
			pointer save_reserved_last = other.reserved_last_;
			allocator_type save_alloc = other.alloc_;

			other.first_ = this->first_;
			other.last_ = this->last_;
			other.reserved_last_ = this->reserved_last_;
			other.alloc_ = this->alloc_;

			this->first_ = save_first;
			this->last_ = save_last;
			this->reserved_last_ = save_reserved_last;
			this->alloc_ = save_alloc;
		}

		allocator_type get_allocator() const
		{
			return (alloc_);
		}

	private:

		// function
		pointer allocate(size_type n) { return alloc_.allocate(n); }
		void deallocate() { alloc_.deallocate(first_, capacity()); }
		void construct(pointer ptr) { alloc_.construct(ptr); }
		//void construct(pointer ptr) { alloc_.construct(ptr, 0); }
		void construct(pointer ptr, const_reference value) { alloc_.construct(ptr, value); }
		void destroy(pointer ptr) { alloc_.destroy(ptr); }
		void destroy_until(reverse_iterator rend)
		{
			for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --last_)
			{
				destroy(&*riter);
			}
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
bool operator==(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y)
{
	return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}
template <typename T, typename Allocator>
bool operator!=(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y)
{
	return !(x == y);
}
template <typename T, typename Allocator>
bool operator<(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y)
{
	return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}
template <typename T, typename Allocator>
bool operator>(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y)
{
	return y < x;
}
template <typename T, typename Allocator>
bool operator>=(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y)
{
	return !(x < y);
}
template <typename T, typename Allocator>
bool operator<=(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y)
{
	return !(y < x);
}

} // namespace ft

namespace std
{
	template <class T, class Alloc>
	void swap(ft::vector<T, Alloc> &x, ft::vector<T, Alloc> &y)
	{
		x.swap(y);
	}
} // namespace std

#endif
