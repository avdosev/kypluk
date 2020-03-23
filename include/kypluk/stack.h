#pragma once

#include "define.h"

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

		//������ � �������� �������� 
		type& top() {
			return container.back();
		}
		
		//��������� ���������� ��������� � ����������, ������������ ��� ���������� 
		bool empty() {
			return container.empty();
		}
		
		//���������� ���������� ��������� � ���������� 
		Size_t size() {
			return container.size();
		}
		
		//��������� ������� �� ���� 
		void push(const type& value) {
			container.push_back(value);
		}
		
		//������� ������� ������� � ��� ���� ��� ����� �������
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
