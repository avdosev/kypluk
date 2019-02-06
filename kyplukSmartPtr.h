#ifndef _kypluk_SmartPtr_
#define _kypluk_SmartPtr_

#include <kyplukDefine.h>

template <class type>
class UniquePtr {
	private:
		using pointer = *type;
		pointer ptr;
	public
		pointer release() {
			pointer temp = ptr;
			ptr = NULL;
			return temp;
		} 
		void reset(pointer ptr = NULL) {
			if (this->ptr) delete this->ptr;
			this->ptr = ptr;
		}
		
		swap(UniquePtr &other)
		
		pointer get() {
			return ptr;
		}
		
		operator bool () {
			return prt != NULL;
		}
};

template <class type>
class SharedPtr {
	private:
		struct Node {
			Size_t size;
			type* value;
			Node(type *value = NULL) {
				this->value = value;
				size = 0; 
			}
		};
		Node * node;
	public:
		SharedPtr(type *value) {
			node = new Node(value);
		}
		SharedPtr(const SharedPtr & other) {
			node = other.node;
			other.node->size++;
		}
};

#endif
