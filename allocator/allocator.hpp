#ifndef allocator_hpp_
#define allocator_hpp_

#include <new>//placement new
#include <cstddef>//ptrdiff_t, size_t
#include <cstdlib>//exit
#include <iostream>//cerr
#include <limits>//nemeric_limits
#include <memory>//unique_ptr
#include <type_traits>
#include "../traits/traits.hpp"

namespace util{
	template<typename T>
	class oom_allocate{
	public:
		typedef size_t size_type;
		typedef T value_type;
		typedef T* pointer;

		virtual pointer operator()(size_type, pointer)const = 0;

	};

	template<typename T>
	class oom_err: public oom_allocate<T>{
		typedef size_t size_type;
		typedef T value_type;
		typedef T* pointer;
	public:
		virtual pointer operator()(size_type, pointer)const{
			std::cerr << "out of memory\n";
			exit(1);
			return static_cast<pointer>(nullptr);
		}
	};

	template<typename T, typename Handler = oom_err<T>>
	inline T* allocate(size_t n, T* t){
		std::set_new_handler(nullptr);
		T* tmp = static_cast<T*>(::operator new(static_cast<size_t>(n * sizeof(T))));
		if(tmp == nullptr){
			std::unique_ptr<Handler> handler(new Handler());
			return handler->operator()(n, t);
		}
		return tmp;
	}

	template<typename T>
	inline void deallocate(T* buffer){
		::operator delete(buffer);
	}

	template<typename T1, typename T2>
	inline void construct(T1* buffer, const T2& x){
		new(buffer) T1(x);
	}

	template<typename T>
	inline void destory(T* buffer){
		buffer->~T();
	}

	template<typename ForwardIterator, typename T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first, size_t n, const T& x, std::false_type){
		ForwardIterator it = first;
		for(int i = 0;i < n;++i){
			construct(&*it, x);
			it++;
		}
		return it;
	}

	template<typename ForwardIterator, typename T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first, size_t n, const T& x, std::true_type){
		return std::fill_n(first, n, x); 
	}

	template<typename ForwardIterator, typename T, typename T1>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first, size_t n, const T& x, T1*){
		typedef typename type_traits<T1>::is_POD_type is_POD;
		return uninitialized_fill_n(first, n, x, is_POD());
	}

	template<typename ForwardIterator, typename T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first, size_t n, const T& x){
		return uninitialized_fill_n(first, n, x, value_type(first));
	}

	template<typename InputIterator, typename ForwardIterator>
	inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, std::false_type){
		for(auto it = first;it != last;++it){
			construct(&*it, *result);
			++result;
		}
		return result;
	}

	template<typename InputIterator, typename ForwardIterator>
	inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, std::true_type){
		return std::copy(first, last, result);
	}

	template<typename InputIterator, typename ForwardIterator, typename T>
	inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T*){
		typedef typename type_traits<T>::is_POD_type is_POD;
		return uninitialized_copy(first, last, result, is_POD());
	}

	template<typename InputIterator, typename ForwardIterator>
	inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result){
		return uninitialized_copy(first, last, result, value_type(first));
	}

	template<typename InputIterator, typename T>
	inline void uninitialized_fill(InputIterator first, InputIterator last, const T& x, std::true_type){
		std::fill(first, last, x);
	}

	template<typename InputIterator, typename T>
	inline void uninitialized_fill(InputIterator first, InputIterator last, const T& x, std::false_type){
		for(auto it = first;it != last;++it){
			construct(&*it, x);
		}
	}

	template<typename InputIterator, typename T, typename T1>
	inline void uninitialized_fill(InputIterator first, InputIterator last, const T& x, T1*){
		typedef typename type_traits<T1>::is_POD_type is_POD;
		uninitialized_fill(first, last, x, is_POD());
	}

	template<typename InputIterator, typename T>
	inline void uninitialized_fill(InputIterator first, InputIterator last, const T& x){
		uninitialized_fill(first, last, x, value_type(first));
	}

	template<typename T>
	class allocator{
	public:
		typedef T value_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;

		allocator(){}
		allocator(const allocator&)=default;

		pointer allocate(size_type n = 1)const{
			return util::allocate(n, static_cast<T*>(nullptr));
		}

		void deallocate(pointer buffer, size_type n = 1)const{
			util::deallocate(buffer);
		}

		void construct(pointer buffer, const_reference x)const{
			util::construct(buffer, x);
		}

		void destory(pointer p)const{
			util::destory(p);
		}

		size_type max_size()const{
			return static_cast<size_type>(std::numeric_limits<int>::max() / sizeof(value_type));
		}

		pointer address(reference x)const{
			return static_cast<pointer>(&x);
		}

		const_pointer address(const_reference x)const{
			return static_cast<const_pointer>(&x);
		}		
	};
}

#endif