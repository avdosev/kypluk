#pragma once

#include "define.h"
#include "algorithm.h"
#include <iterator>
#include <exception>

namespace kypluk {

template <class type>
class VectorIterator;

template <class type>
class Vector {
	private:
        type* arr = nullptr;
        size_t _size = 0;
        size_t _real_size = 0;
        
        void reset() noexcept {
        	arr = nullptr;
        	_size = 0;
        	_real_size = 0;
		}
		
		template <class swap_type>
		friend void swap(Vector<swap_type>& raz, Vector<swap_type>& dva);
	public:
        using value_type = type;

		using Iterator = VectorIterator<value_type>;
		using ConstIterator = VectorIterator<const value_type>;

        Vector(size_t size = 0, const type& value = type()) : _size(size), _real_size(size) {
            if (_real_size == 0) return;
            arr = new type[_real_size];
            for (type& item : *this) {
            	item = value;
			}
        }

        Vector(const Vector& other) {
            *this = other;
        }

        Vector(Vector&& other) noexcept {
            reset();
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
        	clear();
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
        	if (arr != nullptr) {
        	    copy(this->begin(), this->end(), temp);
        	    delete[] arr;
        	}
			arr = temp;
		}
		
		void clear() {
			delete[] arr;
            reset();
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
				throw std::out_of_range("index out of range");
	        }
	        else {
	            return arr[pos];
	        }
	    }
	    
	    const type& front() const {
	        return *begin();
	    }
	    
	    const type& back() const {
	    	return *(end()-1);
		}

	    type& front() {
	        return *begin();
	    }

	    type& back() {
	    	return *(end()-1);
		}

		Iterator begin() {
			return Iterator(0, &this->arr);
		}
		
		Iterator end() {
			return Iterator(_size, &this->arr);
		}

        ConstIterator begin() const {
            return ConstIterator(0, &this->arr);
        }

        ConstIterator end() const {
            return ConstIterator(_size, &this->arr);
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
            return *this;
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
		pointer const* vc = nullptr;
		size_t index = 0;

	public:

		VectorIterator(size_t index, pointer const* myVector) : vc(myVector), index(index) {}
		
		VectorIterator(const VectorIterator& other) : vc(other.vc), index(other.index) {}
		
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
			return *(*vc+index);
		}

		pointer operator ->() const {
		    return *vc+index;
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

