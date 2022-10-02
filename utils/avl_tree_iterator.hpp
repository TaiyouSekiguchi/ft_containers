#ifndef AVL_TREE_ITERATOR_HPP
#define AVL_TREE_ITERATOR_HPP

#include "avl_tree_node.hpp"

namespace ft
{

	template<typename Val, typename Node>
	class avl_tree_iterator
		: public std::iterator<std::bidirectional_iterator_tag, Val>
	{
		public:
			typedef typename std::iterator<std::bidirectional_iterator_tag, Val>::iterator_category iterator_category;
			typedef typename std::iterator<std::bidirectional_iterator_tag, Val>::value_type value_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, Val>::difference_type diference_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, Val>::pointer pointer;
			typedef typename std::iterator<std::bidirectional_iterator_tag, Val>::reference reference;

		private:
			typedef Node node_type;
			typedef node_type *node_pointer;

			node_pointer node_;

		public:
			avl_tree_iterator() : node_(NULL) {}
			template<typename T2, typename Node2>
			avl_tree_iterator(const avl_tree_iterator<T2, Node2>& o)
				: node_(o.base()) {}
			explicit avl_tree_iterator(node_pointer node)
				: node_(node) {}

			avl_tree_iterator& operator=(const avl_tree_iterator& o)
			{
				if (this != &o)
					node_ = o.node_;
				return (*this);
			}
			virtual ~avl_tree_iterator() {}

			reference operator*() const { return (node_->value_); }
			pointer operator->() const { return (&(node_->value_)); }
			avl_tree_iterator& operator++()
			{
				node_ = node_->next_node();
				return (*this);
			}
			avl_tree_iterator operator++(int)
			{
				avl_tree_iterator ret(*this);
				node_ = node_->next_node();
				return (ret);
			}
			avl_tree_iterator& operator--()
			{
				node_ = node_->prev_node();
				return (*this);
			}
			avl_tree_iterator operator--(int)
			{
				avl_tree_iterator ret(*this);
				node_ = node_->prev_node();
				return (ret);
			}
			node_pointer base() const
			{
				return (node_);
			}
	}; // class avl_tree_iterator

template<typename T1, typename Node1, typename T2, typename Node2>
bool operator==(const avl_tree_iterator<T1, Node1>& x, const avl_tree_iterator<T2, Node2>& y)
{
	return (x.base() == y.base());
}

template<typename T1, typename Node1, typename T2, typename Node2>
bool operator!=(const avl_tree_iterator<T1, Node1>& x, const avl_tree_iterator<T2, Node2>& y)
{
	return (!(x == y));
}

} // namespace ft

#endif // AVL_TREE_ITERATOR_HPP
