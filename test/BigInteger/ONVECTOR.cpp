#include <iostream>
#include <ctime>
#include <experimental/kyplukBigInteger.h>


using namespace kypluk;
using namespace kypluk::experience;
using namespace std;

int main() {
	
	auto one = unlimInt::from_string("1");
	auto two = unlimInt::from_string("254654659");

	cout << unlimInt::to_vstring(one/2).data() << std::endl;

}
