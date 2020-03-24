#pragma once

#include "define.h"
#include "algorithm.h"
#include <iterator>

namespace kypluk {

    template <class type>
    class VectorIterator;

template <class type>
class Vector {
	private:
        type* arr;
        size_t _size;
        size_t _real_size;
        
        void init() {
        	arr = new type[1];
        	_size = 0;
        	_real_size = 1;
		}
		
		template <class swap_type>
		friend void swap(Vector<swap_type>& raz, Vector<swap_type>& dva);
	public:
        using value_type = type;

		using Iterator = VectorIterator<value_type>;
		using ConstIterator = VectorIterator<const value_type>;

        Vector(size_t size = 0, const type& value = type()) {
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

        Vector(Vector&& other) noexcept {
            init();
            swap(*this, other);
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

		void resize(size_t count) {
        	if (_size > count) {
        		if (_real_size / (_size+1) > 1) {
        			reserve(count);
				}
			} else if (_size < count) {
				if (count > _real_size) {
					size_t dinamic_size = (_real_size * 3) / 2 + 1;
					reserve(dinamic_size > count ? dinamic_size : count);
				}
			}
			_size = count;
        }
        
        void reserve(size_t count) {
        	if (_real_size == count)
        		return;
        	
        	if (count < _real_size) {
	        	_real_size = count;
	        	if (_size > _real_size)
	        		_size = _real_size;
			} else if (count > _real_size) {
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
        
        size_t size() const {
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
	    	for (auto value : vals) {
	    		this->push_back(value);
			}
		}
	
	    void pop_back() {
	    	resize(_size-1);
	    }
	
	    type& operator[] (size_t pos) noexcept {
	        return arr[pos];
	    }
	
	    type& at(size_t pos) const {
	        if (pos >= this -> _size) {
				throw 0;
	        }
	        else {
	            return arr[pos];
	        }
	    }
	    
	    type& front() const {
	        return *begin();
	    }
	    
	    type& back() const {
	    	return *(end()-1);
		}
		
		Iterator begin() {
			return Iterator(0, this);
		}
		
		Iterator end() {
			return Iterator(_size, this);
		}

        ConstIterator begin() const {
            return ConstIterator(0, this);
        }

        ConstIterator end() const {
            return ConstIterator(_size, this);
        }
		
		const type* data () const {
			return arr;
		}

        Vector& operator = (const Vector& other) {
            delete[] arr;
            arr = new type[other.size()]();
            _real_size = _size = other.size();
            copy(other.begin(), other.end(), this->begin());
            return *this;
        }

        Vector& operator = (Vector&& other) noexcept {
            swap(*this, other);
        }
};

template <class type>
class VectorIterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = type;
        using difference_type = ptrdiff_t;
        using reference = type&;
        using pointer = type*;

	private:
		size_t index;
		pointer& vc;

	public:

		VectorIterator(size_t index, pointer& myVector) : vc(myVector), index(index) {}
		
		VectorIterator(const VectorIterator& other) {
			index = other.index;
			vc = other.vc;
		}
		
		VectorIterator& operator = (const VectorIterator& other) {
			index = other.index;
			vc = other.vc;
			return *this;
		}
		
		VectorIterator& operator ++ () {
			index++;
			return *this;
		}
		
		const VectorIterator operator ++ (int) {
			return VectorIterator(index++, vc);
		}
		
		reference operator *() const {
			return *(vc+index);
		}

		pointer operator ->() const {
		    return vc+index;
		}
		
		VectorIterator& operator -- () {
			index--;
			return *this;
		}
		
		const VectorIterator operator -- (int) {
			return VectorIterator(index--, vc);
		}
		
		VectorIterator & operator += (size_t shift) {
			index += shift;
		}
		VectorIterator & operator -= (size_t shift) {
			index -= shift;
		}
		
		VectorIterator operator + (size_t shift) {
			return VectorIterator(index + shift, vc);
		}
		VectorIterator operator - (size_t shift) {
			return VectorIterator(index - shift, vc);
		}
		
		difference_type operator - (const VectorIterator& other) {
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

        static int compare( const VectorIterator& first, const VectorIterator& second ) {
            if (first.index != second.index)
                return first.index > second.index ? 1 : -1;
            return 0;
        }
};
	
	template <class type>
	void swap(Vector<type>& raz, Vector<type>& dva) {
		swap(raz.arr, dva.arr);
		swap(raz._size, dva._size);
		swap(raz._real_size, dva._real_size);
	}
	
}

