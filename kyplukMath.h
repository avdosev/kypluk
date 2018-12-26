#ifndef _kyplukmath_h_
#define _kyplukmath_h_

#include <kyplukDefine.h>

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

template <class type>
type max (type raz, type dva) {
	return raz > dva ? raz : dva;
}
template <class type>
type min (type raz, type dva) {
	return raz < dva ? raz : dva;
}

template <class f>
short int sign(f chislo) {
	if (chislo>0)
		return 1;
	elif (chislo<0)
		return -1;
	return 0;
}

template <class f>
f pow (f chislo, unsigned int stepen) {
	if (stepen == 0) 
		return 1;
	elif (stepen & 1) //stepen%2
		return chislo * pow(chislo, stepen-1);
	else
		return sqr(pow(chislo, stepen/2));
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

double sqrt (double number)
{
	double left = 0.0, right = number, mid = ((right - left) / 2.0) + left;
	while (true) {
		if (abs(sqr(mid) - number) <= 0.00001)
		{
			return mid;
		}
		
		if ((sqr(mid) - number) > 0)
		{
			right = mid;
		}
		elif ((sqr(mid) - number) < 0)
		{
			left = mid;
		}
		
		mid = ((right - left) / 2.0) + left;
		
	}
}

#endif
