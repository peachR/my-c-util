#ifndef display_hpp_
#define display_hpp_

#include <iterator>
#include <type_traits>
#include <iostream>

namespace util{
	template<typename T>
	struct display
	{
		typedef T first_argument_type;
		typedef void result_type;

		result_type operator()(const first_argument_type& x, std::ostream& os = std::cout)const{
			os << x << "\n";
		}

	};

	template<typename Cotainer>
	std::ostream& display_coll(const Cotainer& coll, std::ostream& os = std::cout){
		for(const auto& x : coll){
			os << x << " ";
		}
		os << "\n";
		return os;
	}

	template<typename InputIterator>
	std::ostream& display_coll(InputIterator first, InputIterator end, std::ostream& os = std::cout){
		for(auto it = first;it != end;++it){
			os << *it << " ";
		}
		os << "\n";
		return os;
	}

	template<typename T>
	void show(const T& x){
		std::cout << x << "\n";
	}

	template<typename T, typename... Args>
	void show(const T& x,const Args&... args){
		std::cout << x << " ";
		show(args...);
	}


};

#endif