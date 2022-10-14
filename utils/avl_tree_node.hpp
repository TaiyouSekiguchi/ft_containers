#ifndef AVL_TREE_NODE_HPP
# define AVL_TREE_NODE_HPP

# include <algorithm>

namespace ft
{

template <typename Val>
class avl_tree_node
{
	public:
		typedef avl_tree_node* 				node_pointer;
		typedef const avl_tree_node* 		const_node_pointer;
		typedef Val 						value_type;
		typedef std::size_t 				size_type;
		typedef std::ptrdiff_t 				difference_type;

		node_pointer 	parent_;
		node_pointer 	left_;
		node_pointer 	right_;
		value_type		value_;
		size_type 		height_;

		avl_tree_node()
			: parent_(NULL)
			, left_(NULL)
			, right_(NULL)
		{
		}

		explicit avl_tree_node(const value_type& val)
			: parent_(NULL)
			, left_(NULL)
			, right_(NULL)
			, value_(val)
			, height_(1)
		{
		}

		avl_tree_node(const avl_tree_node& o)
			: parent_(o.parent_)
			, left_(o.left_)
			, right_(o.right_)
			, value_(o.value_)
			, height_(o.height_)
		{
		}

		difference_type balance() const
		{
			size_type left_height = left_ ? left_->height_ : 0;
			size_type right_height = right_ ? right_->height_ : 0;
			return (left_height - right_height);
		}

		void update_height()
		{
			size_type left_height = left_ ? left_->height_ : 0;
			size_type right_height = right_ ? right_->height_ : 0;
			height_ = 1 + std::max(left_height, right_height);
		}

		bool is_left()	const { return (this == parent_->left_); }
		bool is_right()	const { return (this == parent_->right_); }

		void connect_left(node_pointer new_left_node)
		{
			left_ = new_left_node;
			if (new_left_node)
				new_left_node->parent_ = this;
		}

		void connect_right(node_pointer new_right_node)
		{
			right_ = new_right_node;
			if (new_right_node)
				new_right_node->parent_ = this;
		}

		void connect_parent(node_pointer new_parent_node, bool is_left)
		{
			parent_ = new_parent_node;
			if (is_left)
				new_parent_node->left_ = this;
			else
				new_parent_node->right_ = this;
		}

		void disconnect_parent()
		{
			if (is_left())
				parent_->left_ = NULL;
			else
				parent_->right_ = NULL;
			parent_ = NULL;
		}

		node_pointer max_node()
		{
			node_pointer node = this;
			while (node->right_)
				node = node->right_;
			return (node);
		}

		node_pointer min_node()
		{
			node_pointer node = this;
			while (node->left_)
				node = node->left_;
			return (node);
		}

		node_pointer next_node()
		{
			if (right_)
				return (right_->min_node());
			else
			{
				node_pointer node = this;
				while (node->is_right())
					node = node->parent_;
				return (node->parent_);
			}
		}

		node_pointer next_node() const
		{
			if (right_)
				return (right_->min_node());
			else
			{
				const_node_pointer node = this;
				while (node->is_right())
					node = node->parent_;
				return (node->parent_);
			}
		}

		node_pointer prev_node()
		{
			if (left_)
				return (left_->max_node());
			else
			{
				node_pointer node = this;
				while (node->is_left())
					node = node->parent_;
				return (node->parent_);
			}
		}

		node_pointer prev_node() const
		{
			if (left_)
				return (left_->max_node());
			else
			{
				const_node_pointer node = this;
				while (node->is_left())
					node = node->parent_;
				return (node->parent_);
			}
		}

}; // class avl_tree_node

} // namespace ft

#endif // AVL_TREE_NODE_HPP
