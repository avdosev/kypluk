#ifndef _kyplukmath_h_
#define _kyplukmath_h_

#include <kyplukDefine.h>

namespace kypluk {

const double pi = 3.141592653589;
const double e  = 2.718281828459;

unsigned long long int factorial (unsigned short int x) {
	return x==0 ? 1 : x * factorial (x - 1);
}
template <class f>
f sqr (f chislo) {
	return chislo * chislo;
}
template <class f>
f abs (f chislo) {
	return chislo < 0 ? -chislo : chislo;
}

template <class f>
short int sign(f chislo) {
	if (chislo>0)
		return 1;
	elif (chislo<0)
		return -1;
	return 0;
}

double sin (double alpha) {
	double betha = (alpha*pi)/180.0;
	double predtoch = betha, result = 0.0;
	for (int i = 1, j = 0; abs(predtoch) > 0.000001; i+=2, j++) {
		predtoch = (pow(betha, i)/factorial(i));
		result += ((pow(-1, j)) * predtoch);
	}
	return result;
}

double cos (double alpha) {
	double betha = (alpha*pi)/180.0;
	double predtoch = betha, result = 0.0;
	for (int i = 0, j = 0; abs(predtoch) > 0.000001; i+=2, j++) {
		predtoch = (pow(betha, i)/factorial(i));
		result += ((pow(-1, j)) * predtoch);
	}
	return result;
}

}

#endif
