#include <kyplukList.h>
#include <iostream>

using namespace std;

int copcns = 0;
int copoper = 0;

struct test {
	int number;
	test() {
		number = 1;
	}
	test(const test& other) {
		cout << "copy construct\n";
		copcns++;
	}
	test& operator = (const test& other) {
		cout << "operator = \n";
		copoper++;
		return *this;
	}
};

int main() {
	kypluk::List<test> one(5), two(10);
	kypluk::swap(one, two);
	cout << "one size: " << one.size() << std::endl;
	cout << "two size: " << two.size() << std::endl;
	cout << copcns << " " << copoper << endl; 
}
