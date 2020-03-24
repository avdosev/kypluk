#include <iostream>
#include <ctime>
#include <kypluk/big_integer.h>
#include <kypluk/smart_ptr.h>
#include <kypluk/list.h>

using namespace kypluk;
using namespace std;

int main() {
	List<BigInt> numbers;
	numbers.push_back(BigInt::from_string("9"));
	numbers.push_back(BigInt::from_string("9999"));
	numbers.push_back(BigInt::from_string("999999999"));
	numbers.push_back(BigInt::from_string("9999999999999999"));
	numbers.push_back(BigInt::from_string("9999999999999999999999999"));

	time_t start,stop;
	for (auto number : numbers) {
		UniquePtr<BigInt> puk1(new BigInt), puk2(new BigInt);
		
		cout << BigInt::to_vstring(number).data() << ":\n";
		
		start = clock();
		
		for (auto i = 0; i < 10000000; i++) 
			puk1->add(number);
		
		stop = clock();
		
		cout << "add time: " << ((stop-start)/1000.0) << " second\n";
		
//		start = clock();
//		for (auto i = 0; i < 10000000; i++)
//			puk2->add_test(number);
//		
		stop = clock();
		
		cout << "add_test time: " << ((stop-start)/1000.0) << " second\n";
		
		if (*puk1 != *puk2) {
			cout << "failed\n";
		}

		cout << "\n\n";
		puk1.reset(); puk2.reset();
	}
}
