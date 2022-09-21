#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <iostream>
# include <limits>

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
			typedef Allocator::pointer										pointer;
			typedef Allocator::const_pointer								const_pointer;
			typedef typename ft::random_access_iterator<value_type>			iterator;
			typedef typename ft::random_access_iterator<const value_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const iterator>			const_reverse_iterator;

			// Member funcitons
			// constructor
			vector()
				: first_(NULL)
				, last_(NULL)
				, reserved_last_(NULL)
				, alloc_(allocator_type()) {}

			explicit vector(const allocator_type &alloc)
				: first(NULL), last(NULL), reserved_last(NULL), alloc(alloc) {}

			explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
				: first(NULL), last(NULL), reserved_last(NULL), alloc(alloc)
			{
				resize(count, value);
			}

			template <typename InputIterator>
			vector(InputIterator first, InputIterator last, const Allocator& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
				: first(NULL), last(NULL), reserved_last(NULL), alloc(alloc)
			{
				reserve(ft::distance(first, last));
				for (pointer i = first; i != last; ++i)
				{
					push_back(*i);
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
				: first(NULL)
				, last(NULL)
				, reserved_last(NULL)
				, alloc((r.alloc))
			{
				reserve(r.size());
				pointer dest = first;
				for (const_iterator src = r.begin(), last = r.end(); src != last; ++dest, ++src)
				{
					construct(dest, *src);
				}
				last = first + r.size();
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
						last = first + r.size();
						for (const_iterator src_iter = r.begin() + r.size(), src_end = r.end(); src_iter != src_end; ++src_iter, ++last)
						{
							construct(last, *src_iter);
						}
					}
					else
					{
						destroy_until(rbegin());
						reserve(r.size());
						for (const_iterator src_iter = r.begin(), src_end = r.end(); src_iter != src_end; ++src_iter, ++last)
						{
							construct(last, *src_iter);
						}
					}
				return *this;
			}

			// operator
			reference operator [](size_type i) { return first[i]; }
			const_reference operator [](size_type i) const { return first[i]; }

			// iterator
			iterator begin() { return first; }
			const_iterator begin() const { return first; }
			iterator end() { return last; }
			const_iterator end() const { return last; }
			reverse_iterator rbegin() { return reverse_iterator(last); }
			const_reverse_iterator rbegin() const { return reverse_iterator(last); }
			reverse_iterator rend() { return reverse_iterator(first); }
			const_reverse_iterator rend() const { return reverse_iterator(first); }

			// function
			size_type size() const { return end() - begin(); }
			bool empty() const { return begin() == end(); }
			size_type capacity() const { return reserved_last - first; }
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

				return first[i];
			}
			const_reference at(size_type i) const
			{
				if (i >= size())
					throw std::out_of_range("index is out of range.");

				return first[i];
			}
			reference front() { return *first; }
			const_reference front() const { return *first; }
			reference back() { return *(last - 1); }
			const_reference back() const { return *(last - 1); }
			pointer data() { return first; }
			const_pointer data() const { return first; }
			void clear() { destroy_until(rend()); }
			void reserve(size_type sz)
			{
				if (sz <= capacity())
					return;

				pointer ptr = allocate(sz);

				pointer old_first = first;
				pointer old_last = last;
				size_type old_capacity = capacity();

				first = ptr;
				last = first;
				reserved_last = first + sz;

				//std::scope_exit e([&] { traits::deallocate(alloc, old_first, old_capacity); });

				for (pointer old_iter = old_first; old_iter != old_last; ++old_iter, ++last)
				{
					construct(last, *old_iter);
				}

				for (reverse_iterator riter = reverse_iterator(old_last), rend = reverse_iterator(old_first); riter != rend; ++riter)
				{
					destroy(&*riter);
				}
				alloc.deallocate(old_first, old_capacity);
			}
			void resize(size_type sz)
			{
				if (sz < size())
				{
					size_type diff = size() - sz;
					destroy_until(rbegin() + diff);
					last = first + sz;
				}
				else if (sz > size())
				{
					reserve(sz);
					for (; last != reserved_last; ++last)
					{
						construct(last);
					}
				}
			}
			void resize(size_type sz, const_reference value)
			{
				// 現在の要素数より少ない
				if (sz < size())
				{
					size_type diff = size() - sz;
					destroy_until(rbegin() + diff);
					last = first + sz;
				}
				// 現在の要素数より大きい
				else if (sz > size())
				{
					reserve(sz);
					for (; last != reserved_last; ++last)
					{
						construct(last, value);
					}
				}
			}

			void push_back(const_reference value)
			{
				// 予約メモリーが足りなければ拡張
				if (size() + 1 > capacity())
				{
					// 現在のストレージサイズ
					size_type c = size();
					// 0の場合は1に
					if (c == 0)
						c = 1;
					else
						// それ以外の場合は2倍する
						c *= 2;

					reserve(c);
				}
				construct(last, value);
				++last;
			}

			void assign(size_type count, const T &value)
			{
				if (count > capacity())
				{
					clear();
					deallocate();

					first = allocate(count);
					last = first;
					reserved_last = first + count;
					for (size_type i = 0; i < count; ++i)
						construct(last++, value);
				}
				else if (count > size())
				{
					pointer ptr = first;
					for (size_type i = 0; i < count; ++i)
					{
						if (i < size())
							*(ptr++) = value;
						else
							construct(last++, value);
					}
				}
				else
				{
					clear();
					for (size_type i = 0; i < count; ++i)
						construct(last++, value);
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

					first = allocate(count);
					last = first;
					reserved_last = first + count;
					for (InputIt head = src_first; head != src_last; ++head)
						construct(last++, *head);
				}
				else if (count > size())
				{
					pointer ptr = first;
					for (size_type i = 0; i < count; ++i)
					{
						if (i < size())
							*(ptr++) = *src_first++;
						else
							construct(last++, *src_first++);
					}
				}
				else
				{
					clear();
					for (InputIt head = src_first; head != src_last; ++head)
						construct(last++, *head);
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
				for (; last != first + new_size; ++last)
					construct(last);

				iterator tail = last - 1;
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
				for (; last != first + new_size; ++last)
					construct(last);

				iterator tail = last - 1;
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
				for (; last != first + new_size; ++last)
					construct(last);

				iterator tail = last - 1;
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
				// The iterator first does not need to be dereferenceable if first==last:
				// erasing an empty range is a no-op.
				if (first == last)
					return NULL;

				difference_type offset = pos - begin();

				for (iterator src = pos + 1; src < end(); ++src)
				{
					*(src - 1) = *src;
				}
				destroy(--last);
				return (begin() + offset);
			}
			void swap(vector &other)
			{
				pointer save_first = other.first;
				pointer save_last = other.last;
				pointer save_reserved_last = other.reserved_last;
				allocator_type save_alloc = other.alloc;

				other.first = this->first;
				other.last = this->last;
				other.reserved_last = this->reserved_last;
				other.alloc = this->alloc;

				this->first = save_first;
				this->last = save_last;
				this->reserved_last = save_reserved_last;
				this->alloc = save_alloc;
			}

		private:

			// function
			pointer allocate(size_type n) { return alloc.allocate(n); }
			void deallocate() { alloc.deallocate(first, capacity()); }
			void construct(pointer ptr) { alloc.construct(ptr, 0); }
			void construct(pointer ptr, const_reference value)
			{
				alloc.construct(ptr, value);
			}
			void destroy(pointer ptr) { alloc.destroy(ptr); }
			void destroy_until(reverse_iterator rend)
			{
				for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --last)
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

} // namespace ft

namespace std
{
	template <class T, class Alloc>
	void swap(ft::vector<T, Alloc> &lhs, ft::vector<T, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
} // namespace std

#endif
