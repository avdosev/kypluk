#include <iostream>

#include <kyplukDecimal.h>

using decimal = kypluk::Decimal<10>;
using namespace kypluk;

int main() {
	
	unlimInt one = unlimInt::from_string("1");
	std::cout << decimal::to_vstring(one).data() << endl;
	
	decimal chek2 = one;
	std::cout << decimal::to_vstring(chek2).data() << endl;
	chek2*=decimal(5000);
	std::cout << decimal::to_vstring(chek2).data() << endl;
	chek2*=chek2;
	std::cout << decimal::to_vstring(chek2).data() << endl;
}
