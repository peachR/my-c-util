#include <iostream>
#include <iterator>
#include "allocator/allocator.hpp"
#include "tool/display.hpp"

int main(){
	using namespace std;
	util::allocator<int> alloc;
	int* p = alloc.allocate(5);
	for(int i = 1;i <=5;++i){
		alloc.construct(p + i - 1, i);
	}

	cout << "address: " << p << ", value: " << *p << endl;

	util::display_coll(p, p + 5);

	alloc.destory(p);
	alloc.deallocate(p);

	int* buff = alloc.allocate(10);
	util::uninitialized_fill_n(buff, 10, 100);
	util::display_coll(buff, buff + 10);

	alloc.destory(buff);
	alloc.deallocate(buff);

	int* q = alloc.allocate(5);
	util::uninitialized_fill(q, std::next(q,5), 99);
	util::display_coll(q, std::next(q,5));
	alloc.destory(q);
	alloc.deallocate(q);

	return 0;
}