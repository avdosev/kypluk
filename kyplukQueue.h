#ifndef _kyplukQueue_H_
#define _kyplukQueue_H_

#include <kyplukDefine.h>

template <class container_t>
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
		
		//�������� �� �������
		bool empty() {
			return container.empty()
		}
		
		//���������� ���������� ��������� � ���������� 
		Size_t size() {
			return container.size();
		}
		
		//���������� � ������� ������ ��������
		void push(const type& value) {
			cotainer.push_back(value);
		}
		
		//���� ��� ������������ ������� ������ �������
		void pop() {
			container.pop_back();	
		}
		 
		//���������� � ������� �������� �������
		type& front() {
			return container.front();
		}
		
		//���������� � ���������� ��������
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

#endif
