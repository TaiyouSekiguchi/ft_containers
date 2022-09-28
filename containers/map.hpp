#ifndef MAP_HPP
#define MAP_HPP

#include <iterator>
#include "../utils/algorithm.hpp"

namespace ft
{
template<class key,
			class T,
			class compare = std::less<key>,
			class alloc = std::allocator<std::pair<const key, T> > >
class map
{
	friend class node;
	friend class value_compare;

	public:
		typedef key											key_type;
		typedef T											mapped_type;
		typedef std::pair<const key, T>						value_type;
		typedef compare										key_compare;
		typedef alloc										allocator_type;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef std::size_t									size_type;

		class value_compare
			: public std::binary_function<value_type, value_type, bool>
		{
			protected:
				compare comp;
				value_compare(compare c) : comp(c) {}

			public:
				bool operator()(const value_type &x, const value_type &y) const
				{
					return comp(x.first, y.first);
				}
		};

	private:
		struct node
		{
			value_type*		value;
			size_type		height;
			node*			parent;
			node*			left;
			node* 			right;
			int				balance;

			node()
				: value(0), parent(0), left(0), right(0), height(0), balance(0) {}
			node(value_type &v, node &p, node &l, node &r)
				: value(v), parent(p), left(l), right(r), height(0) { update_balance(); }
			~node() { if (value != 0) delete value; }

			size_t left_height() { return left != 0 ? left->height : 0; }
			size_t right_height() { return right != 0 ? right->height : 0; }
			void update_balance()
			{
				size_type lh = 0;
				size_type rh = 0;
				if (left) lh = left->height;
				if (right) rh = right->height;
				height = std::max(lh, rh) + 1;
				balance = (int)(lh - rh);
			}

			void _print()
			{
				std::cout << value->first << "<->" << value->seconde << "-height:" << height;
				if (parent != 0)
					std::cout << "-parent:" << parent->value->first << "-left:" << std::endl;
				if (left != 0 && left->height > 0)
					left->_print();
				if (right != 0 && right->height > 0)
					right->_print();
			}

		}; // struct node

	public:
		class const_iterator;
		class iterator
			: public std::iterator<std::bidirectional_iterator_tag, node>
		{
			friend class map;
			friend class const_iterator;

			public:
				iterator(node* n) : node_(n) {}
				iterator() : node_(0) {}
				~iterator() {}
				iterator(const iterator &it) { node_ = it.node_; }
				iterator& operator=(const iterator& it)
				{
					node_ = it.node_;
					return *this;
				}
				iterator& operator++()
				{
					if (node_->right != 0)
					{
						node_ = node_->right;
						while (node_->left != 0)
							node_ = node_->left;
					}
					else
					{
						node *temp;
						do {
							temp = node_;
							node_ = node_->parent;
							if (node_ != 0 && node_->left == temp)
								break;
						} while (node_->parent != 0);
					}
					return *this;
				}

				iterator operator++(int)
				{
					iterator ret = *this;
					if (node_->right != 0)
					{
						node_ = node_->right;
						while (node_->left != 0)
							node_ = node_->left;
					}
					else
					{
						node *temp;
						do {
							temp = node_;
							node_ = node_->parent;
							if (node_ != 0 && node_->left == temp)
								break;
						} while (node_->parent != 0);
					}
					return ret;
				} // iterator operator++(int)

				iterator& operator--()
				{
					if (node_->left != 0)
					{
						node_ = node_->left;
						while (node_->right != 0)
							node_ = node_->right;
					}
					else
					{
						node *temp;
						do {
							temp = node_;
							node_ = node_->parent;
							if (node_ != 0 && node_->right == temp)
								break;
						} while (node_->parent != 0 && node_ == node_->parent->left);
					}
					return *this;
				} // iterator& operator--()

				iterator operator--(int)
				{
					iterator ret = *this;
					if (node_->left != 0)
					{
						node_ = node_->left;
						while (node_->right != 0)
							node_ = node_->right;
					}
					else
					{
						node *temp;
						do
						{
							temp = node_;
							node_ = node_->parent;
							if (node_ != 0 && node_->right == temp)
								break;
						} while (node_->parent != 0 && node_ == node_->parent->left);
					}
					return ret;
				} // iterator operator--(int)

				typename map::reference operator*() const { return *(node_->value); }
				typename map::pointer operator->() const { return node_->value; }
				bool operator==(const iterator& it) const { return node_ == it.node_; }
				bool operator!=(const iterator& it) const { return node_ != it.node_; }

			private:
				node* node_;
		}; // class iterator

		typedef iterator avliter;
		class const_iterator
			: public std::iterator<std::bidirectional_iterator_tag, node>
		{
			public:
				const_iterator(node* n) : node_(n) {}
				const_iterator() : node_(0) {}
				~const_iterator() {}
				const_iterator(const const_iterator& it)
				{
					node_ = it.node_;
				}
				const_iterator& operator=(const avliter& it)
				{
					node_ = it.node_;
					return *this;
				}
				const_iterator& operator=(const const_iterator& it)
				{
					node_ = it.node_;
					return *this;
				}
				const_iterator& operator++()
				{
					if (node_->right != 0)
					{
						node_ = node_->right;
						while (node_->left != 0)
							node_ = node_->left;
					}
					else
					{
						node *temp;
						do {
							temp = node_;
							node_ = node_->parent;
							if (node_ != 0 && node_->left == temp)
								break;
						} while (node_->parent != 0);
					}
					return *this;
				}

				const_iterator operator++(int)
				{
					const_iterator ret = *this;
					if (node_->right != 0)
					{
						node_ = node_->right;
						while (node_->left != 0)
							node_ = node_->left;
					}
					else
					{
						node *temp;
						do {
							temp = node_;
							node_ = node_->parent;
							if (node_ != 0 && node_->left == temp)
								break;
						} while (node_->parent != 0);
					}
					return ret;
				}
				const_iterator &operator--()
				{
					if (node_->left != 0)
					{
						node_ = node_->left;
						while (node_->right != 0)
							node_ = node_->right;
					}
					else
					{
						node *temp;
						do
						{
							temp = node_;
							node_ = node_->parent;
							if (node_ != 0 && node_->right == temp)
								break;
						} while (node_->parent != 0 && node_ == node_->parent->left);
					}
					return *this;
				}

				const_iterator operator--(int)
				{
					const_iterator ret = *this;
					if (node_->left != 0)
					{
						node_ = node_->left;
						while (node_->right != 0)
							node_ = node_->right;
					}
					else
					{
						node *temp;
						do
						{
							temp = node_;
							node_ = node_->parent;
							if (node_ != 0 && node_->right == temp)
								break;
						} while (node_->parent != 0 && node_ == node_->parent->left);
					}
					return ret;
				}
				const_reference operator*() const { return *(node_->value); }
				const_pointer operator->() const { return node_->value; }
				bool operator==(const iterator &it) const { return node_ == it.node_; }
				bool operator==(const const_iterator &it) const { return node_ == it.node_; }
				bool operator!=(const avliter &it) const { return node_ != it.node_; }
				bool operator!=(const const_iterator &it) const { return node_ != it.node_; }
			private:
				node *node_;
		}; // class const_iterator

	public:
		typedef std::reverse_iterator<iterator>			reverse_iterator;
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::iterator_traits<iterator> 			difference_type;

	private:
		node 			*root_;
		node 			*min_node_;
		node			*max_node_;
		node			*left_barrier_;
		node			*right_barrier_;
		key_compare		key_compare_;
		size_type		node_count_;

	public:
		// Member functions
		explicit map(const key_compare &comp = key_compare())
			: key_compare_(comp)
			, node_count_(0)
		{
			initialize();
		}

		template<class InputIterator>
		map(InputIterator first,
			InputIterator last,
			const key_compare& comp = key_compare())
			: key_compare_(comp)
			, node_count_(0)
		{
			initialize();
			insert(first, last);
		}

		map(const map<key, T>& other)
		{
			node_count_ = 0;
			initialize();
			insert(other.begin(), other.end());
		}

		~map()
		{
			free_mem(root_);
		}

		map& operator=(const map& other)
		{
			clear();
			const_iterator it;
			for (it = other.begin(); it != other.end(); it++)
				insert(*it);
			return *this;
		}

		allocator_type get_allocator() const { return allocator_type(); }

		// Element access
		mapped_type at(const key_type& k)
		{
			iterator res = find(k);
			if (res ==end())
				throw std::out_of_range("key doesn't exist");
			return res.node_->value->second;
		}

		mapped_type& operator[](const key_type& k)
		{
			iterator i = lower_bound(k);
			if (i == end() || key_comp()(k, i->first))
				i = (insert(value_type(k, mapped_type()))).first;
			return i->second;
		}

		// Iterators
		iterator begin() { return iterator(min_node_); }
		const_iterator begin() const { return const_iterator(min_node_); }
		iterator end() { return iterator(right_barrier_); }
		const_iterator end() const { return const_iterator(right_barrier_); }
		reverse_iterator rbegin() { return reverse_iterator(iterator(max_node_)); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(iterator(max_node_)); }
		reverse_iterator rend() { return reverse_iterator(left_barrier_); }
		const_reverse_iterator rend() const { return const_reverse_iterator(left_barrier_); }

		// Capacity
		bool empty() const { return (node_count_ == 0); }
		size_type size() const { return node_count_; }
		size_type max_size() const { return get_allocator().size(); }

		// Modifiers
		void clear()
		{
			node_count_ = 0;
			free_mem(root_);
			initialize();
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (; first != last; ++first)
				insert(*first);
		}
		iterator insert(iterator _where, const value_type& val)
		{
			std::pair<iterator, bool> res = insert(val);
			if (res.second)
				return res.first;
			else
				return end();
		}
		std::pair<iterator, bool> insert(const value_type& val)
		{
			remove_barrier();
			typedef std::pair<iterator, bool> _Res;
			std::pair<iterator, iterator> _res = get_insert_pos(val.first);

			if (_res.first != 0)
			{
				_Res result = _Res(insert_impl(_res.second.node_, val), true);
				add_barrier();
				return result;
			}
			add_barrier();
			return _Res(_res.second, false);
		}
		void erase(iterator i)
		{
			node *a = i.node_;
			iterator j = i;
			if (a->left != 0)
			{
				j--;
				node *b = j.node_;
				value_type *temp = a->value;
				a->value = b->value;
				b->value = temp;
				node *parent = b->parent;
				if (parent->left == b)
					parent->left = 0;
				else
					parent->right = 0;
				b->parent = 0;
				delete b;
				rebalance(parent);
			}
			else if (a->right != 0)
			{
				j++;
				node *b = j.node_;
				value_type *temp = a->value;
				a->value = b->value;
				b->value = temp;
				node *parent = b->parent;
				if (parent->left == b)
					parent->left = 0;
				else
					parent->right = 0;
				b->parent = 0;
				delete b;
				rebalance(parent);
			}
			else
			{
				node *parent = a->parent;
				if (parent->left == a)
					parent->left = 0;
				else
					parent->right = 0;
				a->parent = 0;
				delete a;
				rebalance(parent);
			}
		}
		template <class InputIterator>
		void erase(InputIterator first, InputIterator last)
		{
			for (; first != last; ++first)
				erase(first);
		}
		size_type erase(const key_type &k)
		{
			iterator temp = find(k);
			if (temp == end())
				return 0;
			else
			{
				erase(temp);
				return 1;
			}
		}
		void swap(map<key_type, mapped_type>& m)
		{
			node *mroot = m.root_;
			node *mmin_node_ = m.min_node_;
			node *mmax_node_ = m.max_node_;
			node *mleft_barrier = m.left_barrier_;
			node *mright_barrier = m.right_barrier_;
			size_type mnode_count_ = m.node_count_;

			m.root_ = root_;
			m.min_node_ = min_node_;
			m.max_node_ = max_node_;
			m.left_barrier_ = left_barrier_;
			m.right_barrier_ = right_barrier_;
			m.node_count_ = node_count_;

			root_ = mroot;
			min_node_ = mmin_node_;
			max_node_ = mmax_node_;
			left_barrier_ = mleft_barrier;
			right_barrier_ = mright_barrier;
			node_count_ = mnode_count_;
		}

		// Lookup
		size_type count(const key_type& k) const
		{
			const_iterator f = find(k);
			const_iterator e = end();
			return f == e ? 0 : 1;
		}
		iterator find(const key_type& k)
		{
			iterator j = lower_bound(k);
			return (j == end() || key_compare_(k, j->first)) ? end() : j;
		}
		const_iterator find(const key_type& k) const
		{
			const_iterator j = lower_bound(k);
			const_iterator e = end();
			return (j == e || key_compare_(k, j->first)) ? e : j;
		}
		std::pair<iterator, iterator>
		equal_range(const key_type& k)
		{
			iterator x = begin();
			iterator y = end();
			while (x != 0)
			{
				if (key_compare_(x->first, k))
					x = x.node_->right;
				else if (key_compare_(k, x->first))
				{
					y = x;
					x = x.node_->left;
				}
				else
				{
					iterator xu(x), yu(y);
					y = x;
					x = x.node_->left;
					xu = xu.node_->right;
					return std::pair<iterator, iterator>(lower_bound(x, y, k), upper_bound(xu, yu, k));
				}
			}
			return std::pair<iterator, iterator>(iterator(y), iterator(y));
		}
		std::pair<const_iterator, const_iterator>
		equal_range(const key_type& k) const
		{
			iterator x = begin();
			iterator y = end();
			while (x != 0)
			{
				if (key_compare_(x->first, k))
					x = x.node_->right;
				else if (key_compare_(k, x->first))
				{
					y = x;
					x = x.node_->left;
				}
				else
				{
					iterator xu(x), yu(y);
					y = x;
					x = x.node_->left;
					xu = xu.node_->right;
					return std::pair<iterator, iterator>(lower_bound(x, y, k), upper_bound(xu, yu, k));
				}
			}
			return std::pair<iterator, iterator>(iterator(y), iterator(y));
		}
		iterator lower_bound(const key_type& k)
		{
			if (size() == 0)
				return end();
			node *x = root_;
			node *y = end().node_;
			while (x != 0 && x != left_barrier_ && x != right_barrier_)
			{
				if (key_compare_(x->value->first, k))
				{
					x = x->right;
				}
				else
				{
					y = x;
					x = x->left;
				}
			}
			return iterator(y);
		}
		const_iterator lower_bound(const key_type& k) const
		{
			if (size() == 0)
				return end();
			node *x = root_;
			//node *y = end().node_;
			node *y = right_barrier_;
			while (x != 0 && x != left_barrier_ && x != right_barrier_)
			{
				if (key_compare_(x->value->first, k))
				{
					x = x->right;
				}
				else
				{
					y = x;
					x = x->left;
				}
			}
			return const_iterator(y);
		}
		iterator upper_bound(const key_type& k)
		{
			if (size() == 0)
				return end();
			node* x = root_;
			node *y = end().node_;
			while (x != 0 && x != right_barrier_ && x != left_barrier_)
			{
				if (key_compare()(k, x->value->first))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return iterator(y);
		}
		const_iterator upper_bound(const key_type& k) const
		{
			if (size() == 0)
				return end();
			node* x = root_;
			node *y = end().node_;
			while (x != 0 && x != right_barrier_ && x != left_barrier_)
			{
				if (key_compare()(k, x->value->first))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return const_iterator(y);
		}

		// Observers
		key_compare key_comp() { return key_compare(); }
		// value_comp

		// delete...
		std::pair<iterator, bool> emplace(const value_type& val) { return insert(val); }
		std::pair<iterator, bool> emplace_hint(const_iterator where, const value_type& val) { return insert(val); }
		std::pair<iterator, bool> emplace_hint(iterator where, const value_type& val) { return insert(val); }
		void _print()
		{
			root_->_print();
		}

	private:
		// Helper functions
		void initialize()
		{
			root_ = new node();
			min_node_ = 0;
			max_node_ = 0;
			left_barrier_ = new node();
			left_barrier_->height = 0;
			left_barrier_->parent = root_;
			right_barrier_ = new node();
			right_barrier_->height = 0;
			right_barrier_->parent = root_;
			root_->left = left_barrier_;
			root_->right = right_barrier_;
			root_->height = 0;
		}

		void free_mem(node* node_)
		{
			if (node_ != 0 && node_->left != 0)
				free_mem(node_->left);
			if (node_ != 0 && node_->right != 0)
				free_mem(node_->right);
			if (node_ != 0)
				delete node_;
		}

		void remove_barrier()
		{
			if (size() > 0)
			{
				min_node_->left = 0;
				left_barrier_->parent = 0;
				max_node_->right = 0;
				right_barrier_->parent = 0;
			}
		}

		void add_barrier()
		{
			if (size() > 0)
			{
				min_node_->left = left_barrier_;
				left_barrier_->parent = min_node_;
				max_node_->right = right_barrier_;
				right_barrier_->parent = max_node_;
			}
		}

		std::pair<iterator, iterator>
		get_insert_pos(const key_type& k)
		{
			typedef std::pair<iterator, iterator> _Res;
			if (size() == 0)
				return _Res(iterator(root_), iterator(root_));
			iterator f = find(k);
			if (f != end())
				return _Res(0, f);
			iterator x = root_->parent;
			iterator y = root_;
			bool comp = true;
			while (y != 0)
			{
				x = y;
				comp = key_compare_(k, y.node_->value->first);
				y = comp ? y.node_->left : y.node_->right;
			}
			iterator j = iterator(x);
			return _Res(j, j);
		}

		iterator insert_impl(node* p, const value_type& v)
		{
			value_type *value = new value_type(v.first, v.second);
			if (size() == 0)
			{
				root_->value = value;
				root_->update_balance();
				++node_count_;
				min_node_ = root_;
				max_node_ = root_;
				return iterator(root_);
			}
			else
			{
				node *z = new node;
				z->value = value;
				z->height = 1;
				if (p->parent == 0)
				{
					z->parent = p;
					if (key_compare_(value->first, p->value->first))
						p->left = z;
					else
						p->right = z;
					p->update_balance();
				}
				else
				{
					bool insert_left = (p == root_ || key_compare_(value->first, p->value->first));
					z->parent = p;
					insert_and_rebalance(insert_left, z, p);
				}
				++node_count_;
				if (min_node_ == 0 || min_node_->value->first > z->value->first)
					min_node_ = z;
				if (max_node_ == 0 || max_node_->value->first < z->value->first)
					max_node_ = z;
				return iterator(z);
			}
		}

		node* right_rotation(node* a)
		{
			node* parent = a->parent;
			node *b = a->right;
			if (b->left_height() < b->right_height())
			{
				if (root_ == a)
					root_ = b;
				node *t1 = b->left;
				if (parent != 0)
				{
					bool is_left_child = (a == parent->left);
					if (is_left_child)
					{
						parent->left = b;
						parent->right = b;
					}
				}
				b->parent = parent;
				b->left = a;
				a->parent = b;
				a->right = t1;
				if (t1)
					t1->parent = a;
				a->update_balance();
				b->update_balance();
				return b;
			}
			else
			{
				node *c = b->left;
				if (root_ == a)
					root_ = c;
				node* t1 = c->left;
				node *t2 = c->right;
				if (parent != 0)
				{
					bool is_left_child = (a == parent->left);
					if (is_left_child)
						parent->left = c;
					else
						parent->right = c;
				}
				c->parent = parent;
				c->left = a;
				a->parent = c;
				c->right = b;
				b->parent = c;
				a->right = t1;
				if (t1)
					t1->parent = a;
				b->left = t2;
				if (t2)
					t2->parent = b;
				b->update_balance();
				a->update_balance();
				c->update_balance();
				return c;
			}
		}

		node *left_rotation(node* a)
		{
			node *parent = a->parent;
			node *b = a->left;
			if (b->right_height() < b->left_height())
			{
				if (root_ == a)
					root_ = b;
				node *t1 = b->right;
				if (parent != 0)
				{
					bool is_left_child = (a == parent->left);
					if (is_left_child)
						parent->left = b;
					else
						parent->right = b;
				}
				b->parent = parent;
				b->right = a;
				a->parent = b;
				a->left = t1;
				if (t1)
					t1->parent = a;
				a->update_balance();
				b->update_balance();
				return b;
			}
			else
			{
				node *c = b->right;
				if (root_ == a)
					root_ = c;
				node* t2 = c->left;
				node* t1 = c->right;
				if (parent != 0)
				{
					bool is_left_child = (a == parent->left);
					if (is_left_child)
						parent->left = c;
					else
						parent->right = c;
				}
				c->parent = parent;
				c->left = b;
				b->parent = c;
				c->right = a;
				a->parent = c;
				b->right = t2;
				if (t2)
					t2->parent = b;
				a->left = t1;
				if (t1)
					t1->parent = a;
				a->update_balance();
				b->update_balance();
				c->update_balance();
				return c;
			}
		}

		void rebalance(node* p)
		{
			node *temp = p;
			while (temp != 0)
			{
				temp->update_balance();
				if (temp->balance < -1)
					temp = right_rotation(temp);
				else if (temp->balance > 1)
					temp = left_rotation(temp);
				temp = temp->parent;
			}
		}

		void insert_left_and_rebalance(node *new_node, node* p)
		{
			p->left = new_node;
			rebalance(p);
		}

		void insert_right_and_rebalance(node *new_node, node *p)
		{
			p->right = new_node;
			rebalance(p);
		}

		void insert_and_rebalance(bool insert_left, node* new_node, node *p)
		{
			if (insert_left)
				insert_left_and_rebalance(new_node, p);
			else
				insert_right_and_rebalance(new_node, p);
		}

		iterator lower_bound(iterator first, iterator last, const key_type& k)
		{
			while (first != 0)
			{
				if (key_compare()(first->first, k))
					first = first.node_->right;
				else
				{
					last = first;
					first = first.node_->left;
				}
			}
			return iterator(last);
		}

		iterator upper_bound(iterator first, iterator last, const key_type& k)
		{
			while (first != 0)
			{
				if (key_compare()(k, first->first))
				{
					last = first;
					first = first.node_->left;
				}
				else
					first = first.node_->right;
			}
			return iterator(last);
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
