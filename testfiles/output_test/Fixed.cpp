#include "Fixed.hpp"

Fixed::Fixed( void )
	: fixed_point_num( 0 )
{
	//std::cout << "Default constructor called" << std::endl;

	return ;
}

Fixed::Fixed( const int i )
{
	//std::cout << "Int constructor called" << std::endl;
	this->fixed_point_num = (int)(i * (1 << this->fractional_bits));

	return ;
}

Fixed::Fixed( const float f )
{
	//std::cout << "Float constructor called" << std::endl;
	this->fixed_point_num = (int)(std::roundf(f * (1 << this->fractional_bits)));

	return ;
}

Fixed::Fixed( Fixed const & src )
{
	//std::cout << "Copy constructor called" << std::endl;
	*this = src;

	return ;
}

Fixed::~Fixed( void )
{
	//std::cout << "Destructor called" << std::endl;

	return ;
}

Fixed &		Fixed::operator=( Fixed const & rhs )
{
	//std::cout << "Copy assignment operator called" << std::endl;
	if ( this != &rhs )
		this->fixed_point_num = rhs.getRawBits();

	return *this;
}

bool		Fixed::operator>( Fixed const & rhs ) const
{
	return ( this->fixed_point_num > rhs.getRawBits() );
}

bool		Fixed::operator<( Fixed const & rhs ) const
{
	return ( this->fixed_point_num < rhs.getRawBits() );
}

bool		Fixed::operator>=( Fixed const & rhs ) const
{
	return ( !(*this < rhs) );
}

bool		Fixed::operator<=( Fixed const & rhs ) const
{
	return ( !(*this > rhs) );
}

bool		Fixed::operator==( Fixed const & rhs ) const
{
	return ( this->fixed_point_num == rhs.getRawBits() );
}

bool		Fixed::operator!=( Fixed const & rhs ) const
{
	return ( !(*this == rhs) );
}

const Fixed		Fixed::operator+( Fixed const & rhs ) const
{
	Fixed	tmp;

	tmp.setRawBits( ( this->fixed_point_num + rhs.getRawBits() ) );
	return tmp;
}

const Fixed		Fixed::operator-( Fixed const & rhs ) const
{
	Fixed	tmp;

	tmp.setRawBits( ( this->fixed_point_num - rhs.getRawBits() ) );
	return tmp;
}

const Fixed		Fixed::operator*( Fixed const & rhs ) const
{
	Fixed	tmp;
	long	calc;

	calc = (long)this->fixed_point_num * (long)rhs.getRawBits();
	tmp.setRawBits( calc >> this->fractional_bits );

	return (tmp);
}

const Fixed		Fixed::operator/( Fixed const & rhs ) const
{
	Fixed	tmp;
	long	calc;

	if ( rhs.getRawBits() == 0 )
	{
		std::cerr << "Division by ZERO is error" << std::endl;
		std::exit(1);
	}

	calc = (long)this->fixed_point_num << this->fractional_bits;
	tmp.setRawBits( calc / rhs.getRawBits() );

	return tmp;
}

const Fixed		Fixed::operator+( void ) const
{
	return ( *this );
}

const Fixed		Fixed::operator-( void ) const
{
	Fixed	tmp;

	tmp.fixed_point_num = -this->fixed_point_num;

	return ( tmp );
}

const Fixed&	Fixed::operator++( void )
{
	++( this->fixed_point_num );

	return ( *this );
}

const Fixed		Fixed::operator++( int )
{
	const Fixed	tmp = *this;

	++( *this );

	return ( tmp );
}

const Fixed&	Fixed::operator--( void )
{
	--( this->fixed_point_num );

	return ( *this );
}

const Fixed		Fixed::operator--( int )
{
	const Fixed	tmp = *this;

	--( *this );

	return ( tmp );
}

int			Fixed::getRawBits( void ) const
{
	return (this->fixed_point_num);
}

void		Fixed::setRawBits( int const raw )
{
	this->fixed_point_num = raw;
}

float		Fixed::toFloat( void ) const
{
	return ((float)(this->fixed_point_num) / (float)(1 << fractional_bits));
}

int			Fixed::toInt( void ) const
{
	return ((int)(this->fixed_point_num) / (int)(1 << fractional_bits));
}

std::ostream &		operator<<( std::ostream & o, Fixed const & i)
{
	o << i.toFloat();

	return o;
}

Fixed&			Fixed::min( Fixed & a, Fixed & b)
{
	std::cout << "not const" << std::endl;
	if (a < b)
		return (a);
	else
		return (b);
}

Fixed&			Fixed::max( Fixed & a, Fixed & b)
{
	std::cout << "not const" << std::endl;
	if (a > b)
		return (a);
	else
		return (b);
}

const Fixed&	Fixed::min( Fixed const & a, Fixed const & b)
{
	std::cout << "const" << std::endl;
	if (a < b)
		return (a);
	else
		return (b);
}

const Fixed&	Fixed::max( Fixed const & a, Fixed const & b)
{
	std::cout << "const" << std::endl;
	if (a > b)
		return (a);
	else
		return (b);
}
