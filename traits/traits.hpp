#ifndef traits_hpp_
#define traits_hpp_

#include <type_traits>
#include <iterator>

namespace util{
	using std::false_type;
	using std::true_type;

	/**
	 * 萃取迭代器的value_type
	 */
	template<typename T>
	typename std::iterator_traits<T>::value_type* value_type(T);

	template<typename T>
	struct type_traits
	{

		typedef false_type is_POD_type;
		typedef false_type has_trivial_default_constructor;
		typedef false_type has_trivial_copy_constructor;
		typedef false_type has_trivial_assignment_operator;
		typedef false_type has_trivial_destructor;
	};

	template<>
	struct type_traits<char>
	{
		typedef true_type is_POD_type;
		typedef true_type has_trivial_default_constructor;
		typedef true_type has_trivial_copy_constructor;
		typedef true_type has_trivial_assignment_operator;
		typedef true_type has_trivial_destructor;
	};

	template<>
	struct type_traits<unsigned char>
	{
		typedef true_type is_POD_type;
		typedef true_type has_trivial_default_constructor;
		typedef true_type has_trivial_copy_constructor;
		typedef true_type has_trivial_assignment_operator;
		typedef true_type has_trivial_destructor;
	};

	template<>
	struct type_traits<signed char>
	{
		typedef true_type is_POD_type;
		typedef true_type has_trivial_default_constructor;
		typedef true_type has_trivial_copy_constructor;
		typedef true_type has_trivial_assignment_operator;
		typedef true_type has_trivial_destructor;
	};

	template<>
	struct type_traits<short>
	{
		typedef true_type is_POD_type;
		typedef true_type has_trivial_default_constructor;
		typedef true_type has_trivial_copy_constructor;
		typedef true_type has_trivial_assignment_operator;
		typedef true_type has_trivial_destructor;
	};

	template<>
	struct type_traits<unsigned short>
	{
		typedef true_type is_POD_type;
		typedef true_type has_trivial_default_constructor;
		typedef true_type has_trivial_copy_constructor;
		typedef true_type has_trivial_assignment_operator;
		typedef true_type has_trivial_destructor;
	};

	template<>
	struct type_traits<int>
	{
		typedef true_type is_POD_type;
		typedef true_type has_trivial_default_constructor;
		typedef true_type has_trivial_copy_constructor;
		typedef true_type has_trivial_assignment_operator;
		typedef true_type has_trivial_destructor;
	};

	template<>
	struct type_traits<unsigned int>
	{
		typedef true_type is_POD_type;
		typedef true_type has_trivial_default_constructor;
		typedef true_type has_trivial_copy_constructor;
		typedef true_type has_trivial_assignment_operator;
		typedef true_type has_trivial_destructor;
	};

	template<>
	struct type_traits<long>
	{
		typedef true_type is_POD_type;
		typedef true_type has_trivial_default_constructor;
		typedef true_type has_trivial_copy_constructor;
		typedef true_type has_trivial_assignment_operator;
		typedef true_type has_trivial_destructor;
	};

	template<>
	struct type_traits<unsigned long>
	{
		typedef true_type is_POD_type;
		typedef true_type has_trivial_default_constructor;
		typedef true_type has_trivial_copy_constructor;
		typedef true_type has_trivial_assignment_operator;
		typedef true_type has_trivial_destructor;
	};

	template<>
	struct type_traits<long long>
	{
		typedef true_type is_POD_type;
		typedef true_type has_trivial_default_constructor;
		typedef true_type has_trivial_copy_constructor;
		typedef true_type has_trivial_assignment_operator;
		typedef true_type has_trivial_destructor;
	};

	template<>
	struct type_traits<float>
	{
		typedef true_type is_POD_type;
		typedef true_type has_trivial_default_constructor;
		typedef true_type has_trivial_copy_constructor;
		typedef true_type has_trivial_assignment_operator;
		typedef true_type has_trivial_destructor;
	};

	template<>
	struct type_traits<double>
	{
		typedef true_type is_POD_type;
		typedef true_type has_trivial_default_constructor;
		typedef true_type has_trivial_copy_constructor;
		typedef true_type has_trivial_assignment_operator;
		typedef true_type has_trivial_destructor;
	};

	template<>
	struct type_traits<long double>
	{
		typedef true_type is_POD_type;
		typedef true_type has_trivial_default_constructor;
		typedef true_type has_trivial_copy_constructor;
		typedef true_type has_trivial_assignment_operator;
		typedef true_type has_trivial_destructor;
	};

	template<typename T>
	struct type_traits<T*>
	{
		typedef true_type is_POD_type;
		typedef true_type has_trivial_default_constructor;
		typedef true_type has_trivial_copy_constructor;
		typedef true_type has_trivial_assignment_operator;
		typedef true_type has_trivial_destructor;
	};

	template<typename T>
	typename std::iterator_traits<T>::value_type* value_type(T){
		return static_cast<typename std::iterator_traits<T>::value_type*>(nullptr);
	}
}

#endif