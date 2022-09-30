#ifndef AVLTREE_HPP
#define AVLTREE_HPP

namespace ft
{
	template <typename E, typename Compare, bool AllowDuplicate>
	class AVLTree;

	template <typename E, typename Compare, bool AllowDuplicate, typename Node>
	class AVLTreeIterator
	{
	}; //class AVLTreeIterator


	template <typename E, typename Compare, bool AllowDuplicate>
	class AVLTree
	{

		private:
			struct node
			{
				E el;
				node* parent;
				node *left;
				node *right;
				difference_type height;

			}

	}; //class AVLTree

} // namespace ft

#endif // AVLTREE_HPP
