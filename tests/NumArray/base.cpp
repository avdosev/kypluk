#include <num_array/num_array.h>
#include <kyplukUtility.h>

#include <iostream>
#include <array>
#include <iterator>

USE(kypluk);
USE(std);

int main() {
	using arr_t = array<int, 5>;
	using arr10 = NumArray<arr_t, int>; 
	arr10 first = arr_t{10,2, 6,8,9};
	arr10 second = arr_t{1,2,3,4,5};
	arr10 sum;
	
	cout << "first mean: " << first.mean() << std::endl;
	cout << "second mean: " << second.mean() << std::endl;
	
	sum = (second * 32 + first) / 10;
	cout << "summary mean: " << sum.mean() << std::endl;
	for (auto item : sum.data()) {
		cout << item << " ";
	}
	
	cout << std::endl;
}
