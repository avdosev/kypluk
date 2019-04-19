#pragma once

#include <kyplukDefine.h>
#include <kyplukAlgorithm.h>

namespace kypluk {

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
type pow(type base, type power) {
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

template <class type>
type sqrt (type number, type eps)
{
	type left = 0, right = number, mid = ((right - left) / 2) + left;
	while (true) {
		if (abs(sqr(mid) - number) <= eps)
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
		
		mid = ((right - left) / 2) + left;
		
	}
}

// teylor, darova

template <class num_t>
num_t exp(num_t x, num_t eps) {
	num_t pred_value = 1, next_value = 1+x;
	num_t power = x;
	num_t iterable = 1;
	num_t fact = 1;
	while (abs(next_value-pred_value) > eps) {
		pred_value = next_value;
		power *= x;
		iterable += 1;
		fact *= iterable;
		next_value += power/fact;
	}
	return next_value;
}

template <class num_t>
num_t sin (num_t alpha, num_t eps) {
	num_t power = alpha*alpha*alpha;
	num_t fact = 3*2;
	num_t pred_value = alpha, next_value = alpha - power/fact;
	num_t iterable = 2;
	num_t minus = 1;
	while (abs(next_value-pred_value) > eps) {
		pred_value = next_value;
		power *= alpha * alpha;
		iterable += 2;
		fact *= iterable * (iterable+1);
		next_value += minus*power/fact;
		minus = -minus;
	}
	return next_value;
}

template <class num_t>
num_t cos (num_t alpha, num_t eps) {
	num_t power = alpha*alpha;
	num_t fact = 2;
	num_t pred_value = 1, next_value = 1 - power/fact;
	num_t iterable = 1;
	num_t minus = 1;
	while (abs(next_value-pred_value) > eps) {
		pred_value = next_value;
		power *= alpha * alpha;
		iterable += 2;
		fact *= iterable * (iterable+1);
		next_value += minus*power/fact;
		minus = -minus;
	}
	return next_value;
}

}
