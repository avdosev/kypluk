#include <iostream>
#include <kyplukDecimal.h>
#include <kyplukMath.h>

USE(kypluk);
USE(std);

int main() {
	decimal x = 4, eps = decimal::from_string("0.0000001");
	cout << decimal::to_vstring(exp(x, eps)).data();
}
