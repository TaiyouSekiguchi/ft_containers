#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed
{
	public:

		Fixed();
		Fixed( const int );
		Fixed( const float );
		Fixed( Fixed const & src );
		~Fixed();

		Fixed &				operator=( Fixed const & rhs );

		bool				operator>( Fixed const & rhs ) const;
		bool				operator<( Fixed const & rhs ) const;
		bool				operator>=( Fixed const & rhs ) const;
		bool				operator<=( Fixed const & rhs ) const;
		bool				operator==( Fixed const & rhs ) const;
		bool				operator!=( Fixed const & rhs ) const;

		const Fixed			operator+( Fixed const & rhs ) const;
		const Fixed			operator-( Fixed const & rhs ) const;
		const Fixed			operator*( Fixed const & rhs ) const;
		const Fixed			operator/( Fixed const & rhs ) const;
		const Fixed			operator+( void ) const;
		const Fixed			operator-( void ) const;

		const Fixed&		operator++();
		const Fixed			operator++( int );
		const Fixed&		operator--();
		const Fixed			operator--( int );

		int					getRawBits( void ) const;
		void				setRawBits( int const raw );
		float				toFloat( void ) const;
		int					toInt( void ) const;

		static Fixed&			min( Fixed & a, Fixed & b);
		static Fixed&			max( Fixed & a, Fixed & b);
		static const Fixed&		min( Fixed const & a, Fixed const & b);
		static const Fixed&		max( Fixed const & a, Fixed const & b);

	private:

		int					fixed_point_num;
		static const int	fractional_bits = 8;

};

std::ostream &		operator<<( std::ostream & o, Fixed const & i);

#endif
