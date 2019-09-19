#pragma once

#include "kyplukDefine.h"

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
		
		Array (const Array& other) {
			for (int i = 0; i < _size; i++) {
				arr[i] = other[arr];
			}
		}
		
		/* FIX ME */
		/* needing special class RandomIterator for this class */
		type* begin() {
			return arr;
		}
		
		type* end() {
			return arr+_size;
		}
		
		const type* begin() const {
			return arr;
		}
		
		const type* end() const {
			return arr+_size;
		}
		
		type* data() {
			return arr;
		}
		
		const type* data() const {
			return arr;
		}
		
		Size_t size() {
			return _size;
		}
		
		type& operator [] (Size_t pt) {
			return *(arr+pt);
		} 
		
		const type& operator [] (Size_t pt) const {
			return *(arr+pt);
		} 
};
