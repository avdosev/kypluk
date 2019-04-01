#include <iostream>
#include <ctime>
#include <kyplukBigInteger.h>
#include <kyplukBigIntegerONVECTOR.h>
#include <kyplukSmartPtr.h>


using namespace kypluk;
using namespace std;

template<typename num_t> 
void test() {
	List<num_t> numbers; 
	numbers.push_back(num_t::from_string("9"));
	numbers.push_back(num_t::from_string("9999"));
	numbers.push_back(num_t::from_string("999999999"));
	numbers.push_back(num_t::from_string("9999999999999999"));
	numbers.push_back(num_t::from_string("9999999999999999999999999"));
	

	time_t start,stop;
	for (auto number : numbers) {
		UniquePtr<num_t> puk1(new num_t);
		
		cout << num_t::to_vstring(number).data() << ":\n";
		
		start = clock();
		
		for (auto i = 0; i < 10000000; i++) 
			puk1->add(number);
		
		stop = clock();
		
		cout << "add time: " << ((stop-start)/1000.0) << " second\n";
		
//		start = clock();
//		for (auto i = 0; i < 10000000; i++)
//			puk2->add_test(number);
//		
//		stop = clock();
//		
//		cout << "add_test time: " << ((stop-start)/1000.0) << " second\n";
//		
//		if (*puk1 != *puk2) {
//			cout << "failed\n";
//		}

		cout << "\n\n";
		puk1.reset();
	}
}

int main() {
	test<unlimInt>();
	cout << "\n\n\n";
	test<kypluk::experience::unlimInt>();
}
