#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <iostream>
# include <iterator>
# include <limits>

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
			typedef pointer									iterator;
			typedef const_pointer							const_iterator;
			typedef std::reverse_iterator<iterator>			reverse_iterator;
			typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

			// constructor
			vector() : vector(allocator_type()) {}

			explicit vector(const allocator_type &alloc)
				: first(NULL), last(NULL), reserved_last(NULL), alloc(alloc) {}

			explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
				: vector(alloc)
			{
				resize(count, value);
			}

			template <typename InputIterator>
			vector(InputIterator first, InputIterator last, const Allocator& alloc = Allocator(), typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
				: first(NULL), last(NULL), reserved_last(NULL), alloc(alloc)
			{
				reserve(std::distance(first, last));
				for (InputIterator i = first; i != last; ++i)
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
				, alloc(traits::select_on_container_copy_construction(r.alloc))
			{
				reserve(r.size());
				for (pointer dest = first, src = r.begin(), last = r.end(); src != last; ++dest, ++src)
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
						for (const_iterator src_iter = r.begin() + r.size(), src_end = r.end(); src_iter != src_end; ++src_iter, ++last)
						{
							construct(last, *src_iter);
						}
					}
					else
					{
						destroy_until(rbegin());
						reserve(r.size());
						for (const_iterator src_iter = r.begin(), src_end = r.end(), dest_iter = begin();  src_iter != src_end; ++src_iter, ++dest_iter, ++last)
						{
							construct(dest_iter, *src_iter);
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
			const_iterator cbegin() const { return first; }
			const_iterator cend() const { return last; }
			reverse_iterator rbegin() { return reverse_iterator(last); }
			const_reverse_iterator rbegin() const { return reverse_iterator(last); }
			reverse_iterator rend() { return reverse_iterator(first); }
			const_reverse_iterator rend() const { return reverse_iterator(first); }

			// function
			size_type size() const { return std::distance(begin(), end()); }
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
					construct(last, std::move(*old_iter));
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
			// alias
			typedef std::allocator_traits<allocator_type>	traits;

			// function
			pointer allocate(size_type n)
			{
				return traits::allocate(alloc, n);
			}
			void deallocate()
			{
				traits::deallocate(alloc, first, capacity());
			}
			void construct(pointer ptr)
			{
				traits::construct(alloc, ptr);
			}
			void construct(pointer ptr, const_reference value)
			{
				traits::construct(alloc, ptr, value);
			}
			// ムーブ用
			void construct(pointer ptr, value_type &&value)
			{
				traits::construct(alloc, ptr, std::move(value));
			}
			void destroy(pointer ptr)
			{
				traits::destroy(alloc, ptr);
			}
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
