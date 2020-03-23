#include <kypluk/BigInteger.h>
#include <iostream>
using namespace kypluk;

#define TOSTR(num) kypluk::unlimInt::to_vstring(num).data()

int main() {
	unlimInt one = 1, two = 2, tre = 3333;
	std::cout << TOSTR(tre+tre) << endl;
	std::cout << TOSTR(one-one) << endl;
}
