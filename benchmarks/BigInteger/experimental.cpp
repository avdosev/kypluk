#include <iostream>
#include <ctime>
#include <kyplukBigInteger.h>
#include <experimental/kyplukBigInteger.h>
#include <kyplukMath.h>


using namespace kypluk;
using namespace std;

template<typename num_t> 
void test_add() {
	List<num_t> numbers; 
	numbers.push_back(num_t::from_string("9"));
	numbers.push_back(num_t::from_string("9999"));
	numbers.push_back(num_t::from_string("999999999"));
	numbers.push_back(num_t::from_string("9999999999999999"));
	numbers.push_back(num_t::from_string("9999999999999999999999999"));
	

	time_t start,stop;
	for (auto number : numbers) {
		num_t puk1;
		
		cout << num_t::to_vstring(number).data() << ":\n";
		
		start = clock();
		
		for (auto i = 0; i < 10000000; i++) 
			puk1.add(number);
		
		stop = clock();
		
		cout << "add time: " << ((stop-start)/1000.0) << " second\n";

		cout << "\n\n";
	}
}

template<typename num_t> 
void test_mult() {
	List<num_t> numbers; 
	numbers.push_back(num_t::from_string("9"));
	numbers.push_back(num_t::from_string("9999"));
	numbers.push_back(num_t::from_string("999999999"));

	time_t start,stop;
	for (auto number : numbers) {
		num_t puk1(1);
		
		cout << num_t::to_vstring(number).data() << ":\n";
		
		start = clock();
		
		for (auto i = 0; i < 1000; i++) 
			puk1.mult(number);
		
		stop = clock();
		
		cout << "mult time: " << ((stop-start)/1000.0) << " second\n";

		cout << "\n\n";
	}
}

template<typename num_t> 
void test_pow() {
	List<num_t> numbers; 
	numbers.push_back(num_t::from_string("9"));
	numbers.push_back(num_t::from_string("9999"));
	numbers.push_back(num_t::from_string("999999999"));

	time_t start,stop;
	for (auto number : numbers) {
		num_t puk1(1);
		
		cout << num_t::to_vstring(number).data() << ":\n";
		
		start = clock();
		
		pow<num_t>(number, 1000);
		
		stop = clock();
		
		cout << "pow time: " << ((stop-start)/1000.0) << " second\n";

		cout << "\n\n";
	}
}

int main() {
	cout << "add:\n";
	cout << "on list:\n";
	test_add<unlimInt>();
	cout << "\n\n\n";
	cout << "on vector:\n";
	test_add<kypluk::experience::unlimInt>();
	cout << "\n\n\nmuliply:\n";
	cout << "on list:\n";
	test_mult<unlimInt>();
	cout << "\n\n\n";
	cout << "on vector:\n";
	test_mult<kypluk::experience::unlimInt>();
	cout << "\n\n\npower:\n";
	cout << "on list:\n";
	test_pow<unlimInt>();
	cout << "\n\n\n";
	cout << "on vector:\n";
	test_pow<kypluk::experience::unlimInt>();
}
