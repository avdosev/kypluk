#pragma once

#include "define.h"

template <class type, size_t _size>
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
		
		size_t size() const {
			return _size;
		}
		
		type& operator [] (size_t pt) {
			return *(arr+pt);
		} 
		
		const type& operator [] (size_t pt) const {
			return *(arr+pt);
		} 
};
