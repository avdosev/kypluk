#ifndef _kypluk_Vector_
#define _kypluk_Vector_

#include <kyplukDefine.h>
#include <kyplukAlgorithm.h>

namespace kypluk {

template <class type>
class Vector {
	private:
        type* arr;
        Size_t _size;
        Size_t real_size;
        class VectorIterator;
        friend class VectorIterator;
        
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
		using Iterator = VectorIterator;
        Vector(Size_t size = 0, const type& value = type()) {
            _size = real_size = size;
            if (!real_size) real_size = 1;
            arr = new type[real_size];
            for (type& item : *this) {
            	item = value;
			}
        }

        Vector(const Vector& other) {
            arr = new type[1];
            *this = other;
        }
        
        template <class ConstIterator>
        Vector(ConstIterator begin, ConstIterator end) {
            _size = real_size = distance(begin, end);
            if (!real_size) real_size = 1;
            arr = new type[real_size];
            for (type& item : *this) {
            	item = *begin++;
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
	        	--_size;
	    }
	
	    type& operator[] (Size_t pos)  {
	        return arr[pos];
	    }
	
	    type& at(Size_t pos) {
	        if (pos >= this -> _size) {
				throw 0;
	        }
	        else {
	            return arr[pos];
	        }
	    }
  
	    Vector slice(Size_t first, Size_t last) {
	    	return this->filter([&first, &last](const type& itm, Size_t current_index){
	    		return first >= current_index and current_index < last;
			});
		}
		
		//callback(item, i)
		template <class Func>
		Vector filter(Func check) {
			Vector res;
			for (Size_t index = 0; index < size(); index++) {
				if (check(*this[index], index)) res.push_back();
			}
			return res;
		}
		
		//callback(item, i)
		template <class Func>
		Vector& map(Func query) {
			Vector res;
			for (Size_t index = 0; index < size(); index++) {
				res.push_back(query(*this[index], index));
			}
			return res;
		}
		
		//callback(item, i)
		template <class Func>
		void for_each(Func query) {
			for (Size_t index = 0; index < size(); index++) {
                query((*this)[index], index);
			}
		}
	    
	    type& front() {
	        return *begin();
	    }
	    
	    type& back() {
	    	return *(end()-1);
		}
		
		Iterator begin() {
			return Iterator(0, this);
		}
		
		Iterator end() {
			return Iterator(_size, this);
		}
		
		const type* data () const {
			return arr;
		}
		
		void reverse() {
			reverse(begin(), end());
        }

        Vector& operator = (const Vector& other) {
            delete[] arr;
            arr = new type[other.size()]();
            real_size = _size = other.size();
            copy(other.data(), other.data()+other.size(), this->begin());
            return *this;
        }
};

template <class type>
class Vector<type> :: VectorIterator {
	private:
		Size_t index;
		Vector* vc;
		static int compare( const VectorIterator& first,  const VectorIterator& second ) {
			return first.index - second.index;
		}
	public:
		VectorIterator(Size_t index, Vector<type> *myVector) {
			this->index = index;
			vc = myVector;
		}
		
		VectorIterator(const VectorIterator& other) {
			index = other.index;
			vc = other.vc;
		}
		
		VectorIterator& operator = (const VectorIterator& other) {
			index = other.index;
			vc = other.vc;
			return *this;
		}
		
		VectorIterator & operator ++ () {
			index++;
			return *this;
		}
		
		VectorIterator operator ++ (int) {
			return VectorIterator(index++, vc);
		}
		
		type & operator * () {
			return vc->at(index);
		}
		
		VectorIterator& operator -- () {
			index--;
			return *this;
		}
		
		VectorIterator operator -- (int) {
			return VectorIterator(index--, vc);
		}
		
		VectorIterator & operator += (Size_t shift) {
			index += shift;
		}
		VectorIterator & operator -= (Size_t shift) {
			index -= shift;
		}
		
		VectorIterator operator + (Size_t shift) {
			return VectorIterator(index + shift, vc);
		}
		VectorIterator operator - (Size_t shift) {
			return VectorIterator(index - shift, vc);
		}
		
		llint operator - (const VectorIterator& other) {
			return index - other.index;
		}
		
		bool operator > (const VectorIterator& other) const {
		    return VectorIterator::compare(*this, other) > 0;
		}
		bool operator >= (const VectorIterator& other) const {
		    return VectorIterator::compare(*this, other) >= 0;
		}
		bool operator < (const VectorIterator& other) const {
		    return VectorIterator::compare(*this, other) < 0;
		}
		bool operator <= (const VectorIterator& other) const {
		    return VectorIterator::compare(*this, other) <= 0;
		}
		bool operator == (const VectorIterator& other) const {
		    return VectorIterator::compare(*this, other) == 0;
		}
		bool operator != (const VectorIterator& other) const {
		    return VectorIterator::compare(*this, other) != 0;
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
