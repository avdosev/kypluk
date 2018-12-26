#ifndef _kyplukStack_H_
#define _kyplukStack_H_

#include <kyplukDefine.h>

template <class type>
class  Stack {
	private:
		
		struct node {	
			node *next = NULL;
			type znach;
		};
		
		node head;
		Size_t _size;
		
		void copy(const Stack <type> &copy)
		{
			clear();
			_size = copy._size;
			node *nextnode = copy.head.next, *copynode = head.next;
			
			while (nextnode!=NULL)
			{
				copynode = new node;
				copynode->znach = nextnode->znach;
				copynode=copynode->next;
				nextnode=nextnode->next;
			}
		}
		
	public:
		Stack() {
			_size = 0;
		}
		
		/*
		копируем все элементы в новый стек
		*/
		Stack(const Stack <type> &copy) {
			this->copy(copy);
		}
		
		~Stack() {
			clear();
		} 

		type& top() 
		//Доступ к верхнему элементу 
		{
			return head.next->znach;
		}
		
		bool is_empty()
		//Проверяет отсутствие элементов в контейнере, используемом для реализации 
		{
			return _size == 0;
		}
		
		Size_t size()
		//Возвращает количество элементов в контейнере 
		{
			return _size;
		}
		
		void push(type znach) 
		//вставляет элемент на верх 
		{
			node* predhead = head.next;
			head.next = new node;
			head.next->znach = znach;
			head.next->next = predhead;
			_size++;
		}
		
		type pop()
		//удаляет верхний элемент и при этом его можно увидеть
		{
			type temp = head.next->znach;
			node* predhead = head.next->next;
			delete head.next;
			head.next = predhead;
			_size--;
			return temp;
		}
		
		void clear()
		//full clear
		{
			if (_size!=0)
			{
				node * puk = head.next;
				if (puk!=NULL) {
					while (puk->next!=NULL) {
						node* sled_element = puk;
						puk = puk->next;				
						delete sled_element;
					}
					delete puk;
					_size=0;
				}
			}
		}
		
		Stack & operator = (const Stack <type> &copy)
		{
			this->copy(copy);
			return *this;
		}
		
};

#endif
