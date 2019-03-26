#include <iostream>

#include <kyplukDecimal.h>

using decimal = kypluk::Decimal<10>;
using namespace kypluk;

int main() {
	
	unlimInt one = unlimInt::from_string("1");
	std::cout << decimal::to_vstring(one).data() << endl;
	
	
	decimal chek = decimal::from_string("132.4568");
	decimal chek2 = decimal::from_string("0.0512");
	std::cout << decimal::to_vstring(chek).data() << endl;
	std::cout << decimal::to_vstring(chek2).data() << endl;
	
	
	std::cout << "kypluk:  " << decimal::to_vstring(chek2 / chek).data() << endl;
	std::cout << "reality: " << (0.0512/132.4568) << endl;
	
	std::cout << "kypluk:  " << decimal::to_vstring(chek / chek2).data() << endl;
	std::cout << "reality: " << (132.4568/0.0512) << endl;
}
