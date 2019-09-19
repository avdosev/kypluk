#include <kyplukDecimal.h>

#include <iostream>

template <class f_t>
f_t func(f_t z, f_t y) {
	return 108 - (815 - (1500/z))/y;
}

using decimal = kypluk::Decimal<1000>;

int main() {
	decimal la1 = 4, la2 = decimal::from_string("4.25");
	for (int i = 0; i < 100; i++) {
		auto next = func(la1, la2);
		std::cout << "iteration: " << i << " -  " << decimal::to_vstring(la1).data() << std::endl;
		la1 = la2;
		la2 = next;
	}
}
