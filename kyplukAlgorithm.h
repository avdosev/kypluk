#ifndef _kyplukAlgorithm_H_
#define _kyplukAlgorithm_H_

#include <kyplukDefine.h>
#include <kyplukIterator.h>

template <class type>
void swap (type& raz, type& dva) {
	type temp = raz;
	raz = dva;
	dva = temp;
}

template <class type>
int compare (const type& raz, const type& dva)
{
	if (raz > dva)
		return 1;
	elif (raz < dva)
		return -1;
	else
		return 0;
}

#endif
