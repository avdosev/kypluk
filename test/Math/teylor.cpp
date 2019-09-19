#include <iostream>
#include <kyplukDecimal.h>
#include <kyplukMath.h>

USE(kypluk);
USE(std);

int main() {
	decimal eps = decimal::from_string("0.0001");
	decimal x = 13;
	cout << "exp\n";
	cout << decimal::to_vstring(exp(x, eps)).data() << "\n";
	cout << "sin\n";
	cout << decimal::to_vstring(sin(x, eps)).data() << "\n";
	cout << "cos\n";
	cout << decimal::to_vstring(cos(x, eps)).data() << "\n";
}
