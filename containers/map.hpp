#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include "../utils/pair.hpp"
#include "../utils/iterator.hpp"
#include "../utils/avl_tree.hpp"
#include "../utils/algorithm.hpp"

namespace ft
{

template <typename Key, typename Val, typename Compare>
class map_value_compare
{
	private:
		typedef Compare		key_compare;

		key_compare			comp_;

	public:
		map_value_compare() : comp_() {}
		explicit map_value_compare(key_compare c) : comp_(c) {}

		bool operator()(const Val& x, const Val& y) const
		{
			return (comp_(x.first, y.first));
		}
		bool operator()(const Val& x, const Key& y) const
		{
			return (comp_(x.first, y));
		}
		bool operator()(const Key& x, const Val& y) const
		{
			return (comp_(x, y.first));
		}
}; // class map_value_compare

template<class Key,
			class T,
			class Compare = std::less<Key>,
			class Alloc = std::allocator<std::pair<const Key, T> > >
class map
{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef pair<const key_type, mapped_type>			value_type;
		typedef Compare										key_compare;

		class value_compare
			: public std::binary_function<value_type, value_type, bool>
		{
			friend class map;

			protected:
				Compare comp_;
				explicit value_compare(Compare c) : comp_(c) {}

			public:
				typedef bool			result_type;
				typedef value_type		first_argument_type;
				typedef value_type		second_argument_type;
				bool operator()(const value_type &x, const value_type &y) const
				{
					return comp_(x.first, y.first);
				}
		};

		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;


		private:
			typedef map_value_compare<key_type, value_type, key_compare> map_value_compare;
			typedef avl_tree<key_type, value_type, map_value_compare, allocator_type> tree_type;

			tree_type tree_;

		public:
			typedef typename tree_type::iterator iterator;
			typedef typename tree_type::const_iterator const_iterator;
			typedef ft::reverse_iterator<iterator>	reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: tree_(map_value_compare(comp), alloc) {}

			template <typename InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				: tree_(map_value_compare(comp), alloc)
			{
				insert(first, last);
			}

			map(const map &o) : tree_(o.tree_)
			{
			}

			~map()
			{
			}

			map &operator=(const map &o)
			{
				tree_ = o.tree_;
				return *this;
		}

		// Element access
		mapped_type &operator[](const key_type &k)
		{
			return (tree_.insert(value_type(k, mapped_type())).first->second);
		}

		// Iterators
		iterator begin() { return (tree_.begin()); }
		const_iterator begin() const { return (tree_.begin()); }
		iterator end() { return (tree_.end()); }
		const_iterator end() const { return (tree_.end()); }

		reverse_iterator rbegin() { return (reverse_iterator(tree_.end())); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(tree_.end())); }

		reverse_iterator rend() { return (reverse_iterator(tree_.begin())); }
		const_reverse_iterator rend() const { return (const_reverse_iterator(tree_.begin())); }

		// Capacity
		bool empty() const { return (tree_.size() == 0); }
		size_type size() const { return (tree_.size()); }
		size_type max_size() const { return (tree_.max_size()); }

		// Observers
		key_compare key_comp() const
		{
			return (key_compare());
		}
		value_compare value_comp() const
		{
			return (value_compare(key_compare()));
		}

		// modifiers
		void clear()
		{
			tree_.clear();
		}

		pair<iterator, bool> insert(const value_type& val)
		{
			return (tree_.insert(val));
		}

		iterator insert(iterator position, const value_type& value)
		{
			return tree_.insert(position, value);
		}

		template <typename InputIt>
		void insert(InputIt first, InputIt last)
		{
			tree_.insert(first, last);
		}

		void erase(iterator pos)
		{
			tree_.erase(pos);
		}

		void erase(iterator first, iterator last)
		{
			tree_.erase(first, last);
		}

		size_type erase(const key_type &k)
		{
			return (tree_.erase(k));
		}

		void swap(map &o)
		{
			tree_.swap(o.tree_);
		}

		// Lookup
		size_type count(const key_type &k) const
		{
			return (tree_.count(k));
		}

		iterator find(const key_type &k)
		{
			return (tree_.find(k));
		}
		const_iterator find(const key_type &k) const
		{
			return (tree_.find(k));
		}

		pair<iterator, iterator> equal_range(const key_type &k)
		{
			return (tree_.equal_range(k));
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return (tree_.equal_range(k));
		}

		iterator lower_bound(const key_type &k)
		{
			return (tree_.lower_bound(k));
		}

		const_iterator lower_bound(const key_type &k) const
		{
			return (tree_.lower_bound(k));
		}

		iterator upper_bound(const key_type &k)
		{
			return (tree_.upper_bound(k));
		}

		const_iterator upper_bound(const key_type &k) const
		{
			return (tree_.upper_bound(k));
		}

		allocator_type get_allocator() const
		{
			return (allocator_type());
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
void swap(ft::map<key, T, compare, alloc>& x,
			ft::map<key, T, compare, alloc>& y)
{
	x.swap(y);
}

} // namespace ft

#endif // MAP_HPP
