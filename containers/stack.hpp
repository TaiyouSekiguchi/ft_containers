#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:

			//Member types
			typedef Container								container_type;
			typedef typename Container::value_type			value_type;
			typedef typename Container::size_type			size_type;
			typedef typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;

		protected:
			container_type c;

		public:
			// Member function
			// constructor
			explicit stack(const container_type& container = container_type()) : c(container) {}
			stack(const stack& other) : c(other.c) {}
			// destructor
			~stack();
			// operator
			stack& operator=(const stack &other)
			{
				if (this != &other)
					c = other.c;
				return *this;
			}
			// Element access
			reference top() { return c.back(); }
			const_reference top() const { return c.back(); }
			// Capacity
			bool empty() const { return c.empty(); }
			size_type size() const { return c.size(); }
			// Modifiers
			void push(const value_type& value) { c.push_back(value); }
			void pop() { c.pop_back(); }

			template <class T_, class Container_>
			friend bool operator==(const ft::stack<T_, Container_> &x, const ft::stack<T_, Container_> &y);

			template <class T_, class Container_>
			friend bool operator!=(const ft::stack<T_, Container_> &x, const ft::stack<T_, Container_> &y);
			template <class T_, class Container_>
			friend bool operator<(const ft::stack<T_, Container_> &x, const ft::stack<T_, Container_> &y);
			template <class T_, class Container_>
			friend bool operator<=(const ft::stack<T_, Container_> &x, const ft::stack<T_, Container_> &y);
			template <class T_, class Container_>
			friend bool operator>(const ft::stack<T_, Container_> &x, const ft::stack<T_, Container_> &y);
			template <class T_, class Container_>
			friend bool operator>=(const ft::stack<T_, Container_> &x, const ft::stack<T_, Container_> &y);

	}; // class stack

	// Non-member functions
	template <class T, class Container>
	bool operator==(const ft::stack<T, Container> &x,
					const ft::stack<T, Container> &y)
	{
		return (x.c == y.c);
	}
	template <class T, class Container>
	bool operator!=(const ft::stack<T, Container> &x,
					const ft::stack<T, Container> &y)
	{
		return (x.c != y.c);
	}
	template <class T, class Container>
	bool operator<(const ft::stack<T, Container> &x,
					const ft::stack<T, Container> &y)
	{
		return (x.c < y.c);
	}
	template <class T, class Container>
	bool operator<=(const ft::stack<T, Container> &x,
					const ft::stack<T, Container> &y)
	{
		return (x.c <= y.c);
	}
	template <class T, class Container>
	bool operator>(const ft::stack<T, Container> &x,
					const ft::stack<T, Container> &y)
	{
		return (x.c > y.c);
	}
	template <class T, class Container>
	bool operator>=(const ft::stack<T, Container> &x,
					const ft::stack<T, Container> &y)
	{
		return (x.c >= y.c);
	}

} // namespace ft

#endif // STACK_HPP
