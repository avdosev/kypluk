#ifndef _kyplukQueue_H_
#define _kyplukQueue_H_

#include <kyplukDefine.h>

template <class type>
class  Queue {
	private:
		struct Node {	
			Node * back = NULL;
			type znach;
		};
		
		void copy(const Queue& for_copy) {
			clear();
			
			Node * iter = for_copy.head;
			while (iter!=NULL)
			{
				push(iter -> znach);
				iter = iter -> back;
			}
		}
		
		Size_t _size = 0;
		Node * head = NULL, * end = NULL;
		
	public:
		Queue() {
			_size = 0;
		}
		
		Queue(const Queue& for_copy) {
			copy(for_copy);
		}
		
		~Queue() {
			clear();
		}
		
		bool is_empty()
		//проверка на пустоту
		{
			return _size == 0;
		}
		
		Size_t size()
		//Возвращает количество элементов в контейнере 
		{
			return _size;
		}
		
		void push(const type& znach)
		//добавления в очередь нового элемента
		{
			if (_size != 0)
			{
				end -> back = new Node;
				end = end -> back;
			}
			else 
			{
				head = new Node;
				end = head;
			}
			
			end -> znach = znach;
			_size++;
		}
		
		const type pop()
		//Если нам понадобилось удалить первый элемент
		{
			Node * tmp = head;
			if (_size != 0)
			{
				head = head -> back;
				type res = tmp -> znach;
				delete tmp;
				_size--;
				return res;
			}
		}
		 
		type& front()
		//обратиться к первому элементу очереди
		{
			return head->znach;
		}
		
		type& back() 
		//обратиться к последнему элементу
		{
			return end->znach;
		}
		
		void clear() {
			Node * iter = head;
			if (_size != 0)
			{
				Node * puk = iter;
				while (iter -> back != NULL)
				{
					puk = puk -> back;
					delete iter;
					iter = puk;
				}
				delete puk;
			}
			
			_size = 0;
		}
		
		Queue & operator = (const Stack <type> &copy)
		{
			this->copy(copy);
			return *this;
		}
		
};

#endif
