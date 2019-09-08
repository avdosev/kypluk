#pragma once

#include <kyplukVector.h>
namespace kypluk {

template <class type, class container_t = Vector<type>>
class  Queue {
	private:
		container_t container;
	public:
		Queue() {
			
		}
		
		Queue(const Queue& other) {
			container = other;
		}
		
		~Queue() {
			container.clear()
		}
		
		bool empty() {
			return container.empty()
		}
		 
		Size_t size() {
			return container.size();
		}
		
		void push(const type& value) {
			cotainer.push_back(value);
		}
		
		void pop() {
			container.pop_back();	
		}
		 
		type& front() {
			return container.front();
		}
		
		type& back() {
			return container.back();
		}
		
		void clear() {
			container.clear();
		}
		
		Queue & operator = (const Queue &other) {
			this->container = other.container;
		}
		
};

}
