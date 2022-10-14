#ifndef UTIL_HPP
#define UTIL_HPP

namespace ft
{

template <typename _Tp, _Tp __v>
struct integral_constant
{
	static const _Tp value = __v;
	typedef _Tp value_type;
	typedef integral_constant<_Tp, __v> type;
	const value_type operator()() const { return value; }
};

typedef integral_constant<bool, true> true_type;

typedef integral_constant<bool, false> false_type;

template <typename, typename>
struct is_same : public false_type
{
};

template <typename _Tp>
struct is_same<_Tp, _Tp> : public true_type
{
};

template <typename T>
struct remove_const
{
	typedef T type;
};

template <typename T>
struct remove_const<T const>
{
	typedef T type;
};
template <typename T>
struct remove_volatile
{
	typedef T type;
};

template <typename T>
struct remove_volatile<T volatile>
{
	typedef T type;
};

template <typename T>
struct remove_cv
{
	typedef typename remove_const<typename remove_volatile<T>::type>::type type;
};

template <typename>
struct __is_integral_helper : public false_type
{
};

template <>
struct __is_integral_helper<bool> : public true_type
{
};

template <>
struct __is_integral_helper<char> : public true_type
{
};

template <>
struct __is_integral_helper<signed char> : public true_type
{
};

template <>
struct __is_integral_helper<unsigned char> : public true_type
{
};

template <>
struct __is_integral_helper<wchar_t> : public true_type
{
};

// template <>
// struct __is_integral_helper<char16_t> : public true_type {};

// template <>
// struct __is_integral_helper<char32_t> : public true_type {};

template <>
struct __is_integral_helper<short> : public true_type
{
};

template <>
struct __is_integral_helper<unsigned short> : public true_type
{
};

template <>
struct __is_integral_helper<int> : public true_type
{
};

template <>
struct __is_integral_helper<unsigned int> : public true_type
{
};

template <>
struct __is_integral_helper<long> : public true_type
{
};

template <>
struct __is_integral_helper<unsigned long> : public true_type
{
};

template <>
struct __is_integral_helper<long long> : public true_type
{
};

template <>
struct __is_integral_helper<unsigned long long> : public true_type
{
};

template <typename T>
struct is_integral
	: public __is_integral_helper<typename remove_cv<T>::type>::type
{
};

template <bool B, class T = void>
struct enable_if
{
};

template <class T>
struct enable_if<true, T>
{
	typedef T type;
};

}; // namespace ft

#endif
