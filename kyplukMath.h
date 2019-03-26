#ifndef _kyplukmath_h_
#define _kyplukmath_h_

#include <kyplukDefine.h>

namespace kypluk {

const double pi = 3.141592653589;
const double e  = 2.718281828459;

template <class type>
type fact(type n) {
    type temp = 1;
    while (n > 0) {
        temp*=n;
        n -= 1;
    }
    return temp;
}

template<class type>
type pow(const type& base, const type& power) {
    if (power == 0)
        return 1;
    else if (power.odd()) {
        return pow<type>(base, power-1)*base;
    } else {
        auto pw = pow<type>(base, power/2);
        return pw * pw;
    }
}

template <class type>
type sqr (type chislo) {
	return chislo * chislo;
}
template <class type>
type abs (type chislo) {
	return chislo < 0 ? -chislo : chislo;
}

template <class type>
int sign(type chislo) {
	if (chislo>0)
		return 1;
	elif (chislo<0)
		return -1;
	return 0;
}

}

#endif
