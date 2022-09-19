template <typename Array>
struct array_iterator
{
	public:
		// constructor
		array_iterator(Array &a, std::size_t i)
			: a(a), i(i) {}

		// operator
		Array::reference operator *() { return a[i]; }
		array_iterator &array_iterator::operator ++()
		{
			i++;
			return *this;
		}
		array_iterator array_iterator::operator++(int)
		{
			array_iterator copy = *this;
			++*this;
			return copy;
		}
		array_iterator &array_iterator::operator--()
		{
			--i;
			return *this;
		}
		array_iterator array_iterator::operator--(int)
		{
			array_iterator copy = *this;
			--*this;
			return copy;
		}
		bool array_iterator::operator==(array_iterator const &right)
		{
			return i == right.i;
		}
		bool array_iterator::operator!=(array_iterator const &right)
		{
			return i != right.i;
		}
		array_iterator &operator+=(std::size_t n)
		{
			i += n;
			return *this;
		}

		array_iterator operator+(std::size_t n) const
		{
			array_iterator copy = *this;
			copy += n;
			return copy;
		}

	private:
		// data member
		Array &a;
		std::size_t i;
};

template <typename T, std::size_t N>
struct array
{
	public:
		// alias
		typedef value_type      = T;
		typedef reference       = T &;
		typedef const_reference = const T &;
		typedef size_type       = std::size_t;
		typedef iterator        = array_iterator<array>;

		// operator
		reference operator[](size_type i)
		{
			return storage[i];
		}

		const_reference operator[]( size_type i) const
		{
			return storage[i];
		}

		// iterator
		iterator begin() { return array_iterator(*this, 0); }
		iterator end() { return array_iterator(*this, N); }

		// function
		reference front(void) { return storage[0]; }
		const_reference front(void) const { return storage[0]; }
		reference back(void) { return storage[N - 1]; }
		const_reference back(void) const { return storage[N - 1]; }

		private:
			// data member
			value_type storage[N];
};
