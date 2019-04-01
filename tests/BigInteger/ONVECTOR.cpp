#include <iostream>
#include <ctime>
#include <kyplukBigIntegerONVECTOR.h>


using namespace kypluk;
using namespace kypluk::experience;
using namespace std;

int main() {
	Vector<unlimInt> numbers; 
	auto one = unlimInt::from_string("45646510");
	auto two = unlimInt::from_string("254654659");

	cout << unlimInt::to_vstring(one.add(two)).data() << std::endl;

}
