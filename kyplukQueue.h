#ifndef _kyplukQueue_H_
#define _kyplukQueue_H_

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
		
		//проверка на пустоту
		bool empty() {
			return container.empty()
		}
		
		//Возвращает количество элементов в контейнере 
		Size_t size() {
			return container.size();
		}
		
		//добавления в очередь нового элемента
		void push(const type& value) {
			cotainer.push_back(value);
		}
		
		//Если нам понадобилось удалить первый элемент
		void pop() {
			container.pop_back();	
		}
		 
		//обратиться к первому элементу очереди
		type& front() {
			return container.front();
		}
		
		//обратиться к последнему элементу
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

#endif
