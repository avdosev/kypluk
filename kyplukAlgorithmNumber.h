#ifndef _kyplukAlgorithm_H_
#define _kyplukAlgorithm_H_

template <class type>
void xor_swap (type& raz, type& dva) {
	if (&raz == &dva) return;
	
	raz ^= dva;
	dva ^= raz;
	raz ^= dva;
}

template <class T>
T reversBit(T number, int size) {
	int psize = size >> 1;//size/2
	T xright = (number << sizeof(number)*8-psize) >> sizeof(number)*8-psize, 
	xleft = number >> psize,
	y;
	
	if (psize != 0) {
		xleft = reversBit(xleft, psize);
		xright = reversBit(xright, psize);
	}
	
	y = (xleft) | (xright << psize);
	
	return y;
}

#endif
