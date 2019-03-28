#ifndef _kyplukStack_H_
#define _kyplukStack_H_

#include <kyplukDefine.h>

namespace kypluk {

template <class type, class container_t>
class  Stack {
	private:
		container_t container;
	public:
		Stack() {
		
		}
		
		Stack(const Stack &other) {
			container = other.container;
		}
		
		~Stack() {
			container.clear();
		} 

		//Доступ к верхнему элементу 
		type& top() {
			return container.back();
		}
		
		//Проверяет отсутствие элементов в контейнере, используемом для реализации 
		bool empty() {
			return container.empty();
		}
		
		//Возвращает количество элементов в контейнере 
		Size_t size() {
			return container.size();
		}
		
		//вставляет элемент на верх 
		void push(const type& value) {
			container.push_back(value);
		}
		
		//удаляет верхний элемент и при этом его можно увидеть
		void pop() {
			container.pop_back();
		}
		
		void clear() {
			container.clear();
		}
		
		Stack & operator = (const Stack &copy)
		{
			this->container = other.container;
			return *this;
		}
		
};

}

#endif
