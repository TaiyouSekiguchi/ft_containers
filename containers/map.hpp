#ifndef MAP_HPP
#define MAP_HPP

namespace ft
{
template<class Key
			class T,
			class Compare = std::less<key>,
			class Alloc = std::allocator<std::pair<const key, T> > >
class Map
{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		typedef Alloc 	allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;

		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		typedef typename ft::avl_tree<Key, T, Compare, Alloc> tree;
		typedef ft::Node<value_type> node_type;
		typedef ft::bidirectional_iterator<node_type, value_type> iterator;
		typedef ft::const_bidirectional_iterator<node_type, value_type> const_iterator;

		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		class value_compare
			: public std::binary_function<value_type, value_type, bool>
		{
			protected:
				Compare comp_;

			public:
				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
				value_compare(Compare comp) : comp_(comp) {}
				bool operator()(const value_type &x, const value_type &y) const
				{
					return comp(x.first, y.first);
				}
		};

	private:
		typedef AVLTree<value_type, value_compare, false> _tree_type;
		typedef Map<Key, T, Compare> _Self;

		_tree_type _tree;

	public:

		// Member functions
		explicit Map(const key_compare &comp = key_compare())
			: _tree(value_compare(comp)) {}

		template <class InputIterator>
		Map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare())
			: _tree(first, last, value_compare(comp)) {}

		Map(const Map &o) : _tree(o._tree) {}
		~Map() {}

		Map& operator=(const map& o)
		{
			_tree = o.tree;
			return *this;
		}

		// Element access
		mapped_type &operator[](const key_type &k)
		{
			Pair<iterator, bool> res = insert(make_pair(k, mapped_type()));
			return res.first->second;
		}

		// Iterators
		iterator begin() { return (_tree.begin()); }
		const_iterator begin() const { return (_tree.begin()); }
		reverse_iterator rbegin() { return (_tree.rbegin()); }
		const_reverse_iterator rbegin() const { return (_tree.rbegin()); }
		iterator end() { return (_tree.end()); }
		const_iterator end() const { return (_tree.end()); }
		reverse_iterator rend() { return (_tree.rend()); }
		const_reverse_iterator rend() const { return (_tree.rend()); }

		// Capacity
		bool empty() { return (_tree.empty()); }
		size_type size() const { return (_tree.size()); }
		size_type max_size() const { return (_tree.max_size()); }

		// Observers
		key_compare key_comp() const { return (_cmp); }
		value_compare value_comp() const { return (value_compare(_cmp)); }

		// modifiers
		void clear() { _tree.clear(); }
		Pair<iterator, bool> insert(const value_type& value) { return _tree.insert(value); }
		iterator insert(iterator hint, const value_type& value) { return _tree.insert(hint, value).first; }
		template <typename InputIt>
		void insert(InputIt first, InputIt last) { _tree.insert(first, last); }

		void erase(iterator pos) { _tree.erase(pos); }
		void erase(iterator first, iterator last) { _tree.erase(first, last); }
		size_type erase(const key_type& key)
		{
			iterator it = find(key);
			if (it === end())
				return 0;
			_tree.erase(it);
			return 1;
		}
		void swap(Map &o){ ft::swap(_tree, x._tree); }

		// Lookup
		size_type count(const key_type &k) const { return _tree.count(make_pair(k, mapped_type)); }

		iterator find(const key_type &k)
		{
			return _tree.find(make_pair(k, mapped_type()))
		}
		const_iterator find(const key_type &k) const
		{
			return _tree.find(make_pair(k, mapped_type()))
		}

		Pair<iterator, iterator> equal_range(const key_type &k)
		{
			return make_pair(lower_bound(k), upper_bound(k));
		}

		Pair<const_iterator, const_iterator> equal_range(const key_type &k)
		{
			return make_pair(lower_bound(k), upper_bound(k));
		}

		iterator lower_bound(const key_type &k)
		{
			return _tree.lowe_bound(make_pair(k, mapped_type()));
		}

		const_iterator lower_bound(const key_type &k)
		{
			return _tree.lowe_bound(make_pair(k, mapped_type()));
		}

		iterator upper_bound(const key_type &k)
		{
			return _tre.upper_bound(make_pair(k, mapped_type()));
		}

		const_iterator upper_bound(const key_type &k)
		{
			return _tre.upper_bound(make_pair(k, mapped_type()));
		}

		key_compare key_comp() const
		{
			return _tree.comparator()._comp;
		}

		value_compare value_comp() const
		{
			return _tree.comparator();
		}

}; // class map

// Nom-member functions
template<class key, class T, class compare, class alloc>
bool operator==(const ft::map<key, T, compare, alloc>& x,
				const ft::map<key, T, compare, alloc>& y)
{
	return (x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()));
}
template<class key, class T, class compare, class alloc>
bool operator!=(const ft::map<key, T, compare, alloc>& x,
				const ft::map<key, T, compare, alloc>& y)
{
	return !(x == y);
}
template<class key, class T, class compare, class alloc>
bool operator<(const ft::map<key, T, compare, alloc>& x,
				const ft::map<key, T, compare, alloc>& y)
{
	return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}
template<class key, class T, class compare, class alloc>
bool operator<=(const ft::map<key, T, compare, alloc>& x,
				const ft::map<key, T, compare, alloc>& y)
{
	return !(y < x);
}
template<class key, class T, class compare, class alloc>
bool operator>(const ft::map<key, T, compare, alloc>& x,
				const ft::map<key, T, compare, alloc>& y)
{
	return y < x;
}
template<class key, class T, class compare, class alloc>
bool operator>=(const ft::map<key, T, compare, alloc>& x,
				const ft::map<key, T, compare, alloc>& y)
{
	return !(x < y);
}
template<class key, class T, class compare, class alloc>
void swap(const ft::map<key, T, compare, alloc>& x,
			const ft::map<key, T, compare, alloc>& y)
{
	x.swap(y);
}

} // namespace ft

#endif // MAP_HPP
