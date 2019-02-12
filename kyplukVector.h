#ifndef _kypluk_Vector_
#define _kypluk_Vector_

#include <kyplukDefine.h>
#include <kyplukAlgorithm.h>
#include <kyplukSmartPtr.h>

template <class type>
class Vector {
	private:
        type* arr;
        size_t size;
        size_t real_size;
//        class vectorIterator;
//        friend class vectorIterator;
		void reborn() {
			realSize = (realSize*3)/2 +1;
	        type* temp = new type[real_size];
	        copy(this->begin(), this->end(), temp);
	        delete arr[];
	        arr = temp;
		}
		
		bool check_reborn(Size_t add_size) {
			return (size+add_size > real_size);	
		}
		
	public:

        Vector(size_t size = 0, const type& value = type()) {
            this->size = real_size = size;
            arr = new type[size];
        }

		void resize(Size_t count) { 
            if (this->size < count) {
        		this->size=count;
	        } elif (this->size > count){
	        	real_size = count;
	        	type* temp = new type[real_size];
	        	copy(this->begin(), this->end(), temp);
	        }
        }
        
        Size_t size() const {
	        return this->size;
	    }
	
	    void Vector::push_back(const type& val) {
	    	while (check_reborn(1)) reborn();
	        vector[size++] = val;
	    }
	
	    void Vector::pop_back() {
	    	if (!size)
	        	arr[--size] = type();
	    }
	
	    type& Vector::operator[] (Size_t pos)  {
	        return arr[pos];
	    }
	
	    const type& at(type pos) const {
	        if (pos >= this->size) {
	            throw 0;
	        }
	        else {
	            return vector[pos];
	        }
	    }
	    
	    type& front() {
	        return *begin();
	    }
	    
	    type& back() {
	    	return *end()-1;
		}
};

#endif
