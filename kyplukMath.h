#ifndef _kyplukmath_h_
#define _kyplukmath_h_

#include <kyplukDefine.h>

namespace kypluk {

const double pi = 3.141592653589;
const double e  = 2.718281828459;

template <class puk>
puk fact(puk n) {
    puk temp = 1;
    while (n > 0) {
        temp*=n;
        n -= 1;
    }
    return temp;
}

template<class puk>
puk pow(const puk& base, const puk& power) {
    if (power == 0)
        return 1;
    else if (power.odd()) {
        return pow<puk>(base, power-1)*base;
    } else {
        auto pw = pow<puk>(base, power/2);
        return pw * pw;
    }
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
int sign(f chislo) {
	if (chislo>0)
		return 1;
	elif (chislo<0)
		return -1;
	return 0;
}

}

#endif
