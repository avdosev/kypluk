#include <iostream>

#include <kyplukDecimal.h>
#include <kyplukVector.h>
#include <kyplukMath.h>

#include <cmath>
#include <cstdio>

using namespace kypluk;

int main() {
	Vector<decimal> test_cases;
	test_cases.push_back(decimal(1));
	test_cases.push_back(decimal(2));
	test_cases.push_back(decimal(4));
	test_cases.push_back(decimal(5));
	test_cases.push_back(decimal(25));
	test_cases.push_back(decimal(144));
	test_cases.push_back(decimal(1596));
	test_cases.push_back(decimal::from_string("156.365"));
	
	decimal eps = decimal::from_string("0.0000000001");
	
	for (decimal test_case : test_cases) { 
		decimal res = sqrt<decimal>(test_case, eps);
		std::cout << "sqr: " << decimal::to_vstring(test_case).data() << endl << "sqrt: " << decimal::to_vstring(res).data() << endl << endl;
	}	
}
