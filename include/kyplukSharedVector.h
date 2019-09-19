#pragma once

#include "kyplukVector.h"
#include "kyplukSmartPtr.h"

namespace kypluk {

template <class type>
class SharedVector : public Vector <SharedPtr<type>> vc; {
	private:
		class SharedVectorIterator;
		friend class SharedVectorIterator;
		using ptr = SharedPtr<type>;	
	public:
		using Iterator = SharedVectorIterator;
		
		SharedVector() {
			
		}
		
		Iterator begin() {
			return Iterator(0, &vc);
		}
		
		Iterator end() {
			return Iterator(vc.size(), &vc);
		}
};

template <class type>
class SharedVector<type>::SharedVectorIterator : Vector<SharedPtr<type>>::Iterator {
	private:
		using ptr = SharedPtr<type>;
		Size_t index;
		Vector<ptr>* vc;
		static int compare( const SharedVectorIterator& first,  const SharedVectorIterator& second ) {
			return first.index - second.index;
		}
	public:
		SharedVectorIterator(Size_t index, Vector<ptr> *myVector) {
			this->index = index;
			vc = myVector;
		}
		
		SharedVectorIterator( const SharedVectorIterator& other) {
			index = other.index;
			vc = other.vc;
		}
		
		bool operator > (const SharedVectorIterator& other) const {
		    return SharedVectorIterator::compare(*this, other) > 0;
		}
		bool operator >= (const SharedVectorIterator& other) const {
		    return SharedVectorIterator::compare(*this, other) >= 0;
		}
		bool operator < (const SharedVectorIterator& other) const {
		    return SharedVectorIterator::compare(*this, other) < 0;
		}
		bool operator <= (const SharedVectorIterator& other) const {
		    return SharedVectorIterator::compare(*this, other) <= 0;
		}
		bool operator == (const SharedVectorIterator& other) const {
		    return SharedVectorIterator::compare(*this, other) == 0;
		}
		bool operator != (const SharedVectorIterator& other) const {
		    return SharedVectorIterator::compare(*this, other) != 0;
		}
};

}
