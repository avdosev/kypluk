#ifndef _kypluk_Array_
#define _kypluk_Array_

#include <kyplukDefine.h>

template <class type, Size_t _size>
class Array {
	private:
		type arr[_size];
	public:
		Array(type value) {
			for (type& item : *this) {
				item = value;
			}
		}
		
		//TO DO
		Array (const Array& other) {
			
		}
		
		type* begin() {
			return arr;
		}
		
		type* end() {
			return arr+_size;
		}
		
		type* data() {
			return arr;
		}
		
		Size_t size() {
			return _size;
		}
};


#endif
