#pragma once

#include <kyplukDefine.h>
#include <kyplukAlgorithm.h>

namespace kypluk {

template <class type>
class Vector {
	private:
        type* arr;
        Size_t _size;
        Size_t _real_size;
        class VectorIterator;
        friend class VectorIterator;
        
        void init() {
        	arr = new type[1];
        	_size = 0;
        	_real_size = 1;
		}
		
		template <class swap_type>
		friend void swap(Vector<swap_type>& raz, Vector<swap_type>& dva);
	public:
		using Iterator = VectorIterator;
        Vector(Size_t size = 0, const type& value = type()) {
            _size = _real_size = size;
            if (!_real_size) _real_size = 1;
            arr = new type[_real_size];
            for (type& item : *this) {
            	item = value;
			}
        }

        Vector(const Vector& other) {
            init();
            *this = other;
        }
        
        template <class ConstIterator>
        Vector(ConstIterator begin, ConstIterator end) {
            _size = _real_size = distance(begin, end);
            if (!_real_size) _real_size = 1;
            arr = new type[_real_size];
            for (type& item : *this) {
            	item = *begin++;
			}
        }
        
        ~Vector() {
        	delete[] arr;
		}

		void resize(Size_t count) { 
        	if (_size > count) {
        		if (_real_size / (_size+1) > 1) {
        			reserve(count);
				}
			} elif (_size < count) {        	
				if (count > _real_size) {
					Size_t dinamic_size = (_real_size*3)/2 + 1;
					reserve(dinamic_size > count ? dinamic_size : count);
				}
			}
			_size = count;
        }
        
        void reserve(Size_t count) {
        	if (_real_size == count)
        		return;
        	
        	if (count < _real_size) {
	        	_size = _real_size = count;
			} elif (count > _real_size) {
        		_real_size = count;	
			}
			 
        	type* temp = new type[_real_size];
        	copy(this->begin(), this->end(), temp);
        	delete[] arr;
			arr = temp; 
		}
		
		void clear() {
			delete[] arr;
			init();
		}
        
        Size_t size() const {
	        return this->_size;
	    }
	    
	    bool empty() const {
			return size() == 0;
		}
	
	    void push_back(const type& val) {
	    	resize(_size+1);
	        back() = val;
	    }
	    
	    void push_back(const Vector& vals) {
	    	reserve(_size+vals.size());
	    	for (const auto& value : vals) {
	    		this->push_back(value);
			}
		}
	
	    void pop_back() {
	    	resize(_size-1);
	    }
	
	    type& operator[] (Size_t pos)  {
	        return arr[pos];
	    }
	
	    type& at(Size_t pos) const {
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
	    
	    type& front() const {
	        return *begin();
	    }
	    
	    type& back() const {
	    	return *(end()-1);
		}
		
		Iterator begin() const {
			return Iterator(0, this);
		}
		
		Iterator end() const {
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
            _real_size = _size = other.size();
            copy(other.begin(), other.end(), this->begin());
            return *this;
        }
};

template <class type>
class Vector<type> :: VectorIterator {
	private:
		Size_t index;
		Vector* vc;
		static int compare( const VectorIterator& first, const VectorIterator& second ) {
			if (first.index != second.index)
				return first.index > second.index ? 1 : -1;
			return 0;
		}
	public:
		VectorIterator(Size_t index, Vector<type> *myVector) {
			this->index = index;
			vc = myVector;
		}
		
		VectorIterator(Size_t index, const Vector<type> *myVector) {
			this->index = index;
			//חא ועמ ÿ בû גתובאכ
			vc = const_cast<Vector<type>*>(myVector);
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
		
		type & operator * () const {
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
		swap(raz._real_size, dva._real_size);
	}
	
}

