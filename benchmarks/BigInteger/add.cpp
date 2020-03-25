#include <iostream>
#include <chrono>
#include <kypluk/big_integer.h>
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

	for (auto number : numbers) {
		BigInt num;
		
		cout << kypluk::to_string(number) << ":\n";
		
		auto start = chrono::steady_clock::now();
		
		for (auto i = 0; i < 10000000; i++) 
			num += number;
		
		auto elapsed = chrono::steady_clock::now() - start;
		
		cout << "add time: " << std::chrono::duration_cast<chrono::milliseconds>(elapsed).count() / 1000. << " second\n";
        cout << kypluk::to_string(num) << std::endl;
		cout << "\n\n";
	}
}
