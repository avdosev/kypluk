#ifndef _kypluk_Vector_
#define _kypluk_Vector_

#include <kyplukDefine.h>
#include <kyplukAlgorithm.h>
#include <kyplukSmartPtr.h>

namespace kypluk {

template <class type>
class Vector {
	private:
        type* arr;
        size_t _size;
        size_t real_size;
//        class vectorIterator;
//        friend class vectorIterator;
		void reborn() {
			real_size = (real_size*3)/2 +1;
	        type* temp = new type[real_size];
	        copy(this->begin(), this->end(), temp);
	        delete[] arr;
	        arr = temp;
		}
		
		bool check_reborn(Size_t add_size) {
			return (_size+add_size > real_size);	
		}
		
		template <class swap_type>
		friend void swap(Vector<swap_type>& raz, Vector<swap_type>& dva);
	public:

        Vector(size_t size = 0, const type& value = type()) {
            _size = real_size = size;
            if (!real_size) real_size = 1;
            arr = new type[real_size];
            for (type& item : *this) {
            	item = value;
			}
        }
        
        ~Vector() {
        	delete[] arr;
		}

		void resize(Size_t count) { 
            if (_size < count) {
        		_size=count;
	        } elif (_size > count){
	        	real_size = count;
	        	type* temp = new type[real_size];
	        	copy(this->begin(), this->end(), temp);
	        }
        }
        
        Size_t size() const {
	        return this->_size;
	    }
	
	    void push_back(const type& val) {
	    	while (check_reborn(1)) reborn();
	        arr[_size++] = val;
	    }
	
	    void pop_back() {
	    	if (_size)
	        	arr[--_size] = type();
	    }
	
	    type& operator[] (Size_t pos)  {
	        return arr[pos];
	    }
	
	    const type& at(type pos) const {
	        if (pos >= this->_size) {
	            throw 0;
	        }
	        else {
	            return arr[pos];
	        }
	    }
	    
	    type& front() {
	        return *begin();
	    }
	    
	    type& back() {
	    	return *(end()-1);
		}
		
		type* begin() {
			return arr;
		}
		
		type* end() {
			return arr+_size;
		}
		
		const type* begin() const{
			return arr;
		}
		
		const type* end() const {
			return arr+_size;
		}
};

	template <class type>
	void swap(Vector<type>& raz, Vector<type>& dva) {
		swap(raz.arr, dva.arr);
		swap(raz._size, dva._size);
		swap(raz.real_size, dva.real_size);
	}
	
}
#endif
