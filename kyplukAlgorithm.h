#ifndef _kyplukAlgorithm_H_
#define _kyplukAlgorithm_H_

#include <kyplukDefine.h>

namespace kypluk {

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

        return 0;
    }

    template <class Iterator, class UnaryFunction>
    void for_each(Iterator begin, Iterator end, UnaryFunction func) {
        for (auto it = begin; it != end; ++it) {
            func(*it);
        }
    }

    template <class Iterator>
    uint distance(Iterator begin, Iterator end) {
        uint res = 0;
        while (begin != end) {
            ++begin;
            res++;
        }
        return res;
    }

    template <class InputIterator, class OutputIterator>
    OutputIterator copy(InputIterator begin, InputIterator end, OutputIterator c_begin) {
        while (begin != end) {
            *c_begin++ = *begin++;
        }
        return c_begin;
    }
    
    template<class InputIt, class OutputIt, class UnaryFunc>
	OutputIt copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate pred)
	{
	    while (first != last) {
	        if(pred(*first))
	            *d_first++ = *first;
	         first++;
	    }
	    return d_first;
	}

    template <class type>
    type max (type raz, type dva) {
        return raz > dva ? raz : dva;
    }
    template <class type>
    type min (type raz, type dva) {
        return raz < dva ? raz : dva;
    }

}
#endif
