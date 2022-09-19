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
			// alias
			typedef T										value_type;
			typedef T*										pointer;
			typedef const pointer							const_pointer;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef Allocator								allocator_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t 							difference_type;
			typedef typename ft::random_access_iterator<value_type>	iterator;
			typedef typename ft::random_access_iterator<const value_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>	reverse_iterator;
			typedef typename ft::reverse_iterator<const iterator>	const_reverse_iterator;

			// constructor
			vector()
				: first(NULL), last(NULL), reserved_last(NULL), alloc(allocator_type()) {}

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

			// data member
			pointer first;
			pointer last;
			pointer reserved_last;
			allocator_type alloc;
	}; // class vector

} // namespace ft

#endif
