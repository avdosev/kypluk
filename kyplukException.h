#ifndef _kypluk_Exception_
#define _kypluk_Exception_

#include <kyplukVector.h>

namespace kypluk {

class Exception {
	private:
		using vstring = Vector<char>;
		vstring _what;
	public:
		Exception(const char* what_arg = "") {
			unsigned lenarg = 0;
			auto ptr = what_arg;
			while (*ptr++) lenarg++;
			_what = vstring(what_arg, what_arg+lenarg+1);
		}
		
		Exception(const Exception& other) {
			*this = other;
		}
		
		Exception& operator = (const Exception& other) {
			this->_what = other._what;
			return *this;
		}
		
		const char* what() const {
			return _what.data();
		}
};

class logic_error : public Exception {};   //����������, ������� ��������� ��� ������� ���������� ����� � ���� ���������
class runtime_error : public Exception {}; //����� ��� ����������, ������� ��������� �� ����� ����������

//���������� ������
class logic_error : public out_of_range{}; //����������, ������� ��������� ��� ������� ������� � ��������� ��� ����������� ���������
class logic_error : public length_error{}; //����������, ������� ��������� ��� ������� ������� ������ �������� �������, ��� �������� ��� ������� ����
class logic_error : public domain_error{}; //����������, ������� ���������, ���� ��� ���������� ��������, ������������� � �������, �� ���������� ����������
class logic_error : public invalid_argument{}; //����������, ������� ��������� ��� �������� � ������� ������������� ���������

//������� ������
class runtime_error : public range_error{}; //����������, ������� ���������, ����� ���������� ��������� ����������� ���������� ��������
class runtime_error : public overflow_error{}; //����������, ������� ���������, ���� ���������� ��������� ��������� ���������� ��������
class runtime_error : public underflow_error{}; //����������, ������� ���������, ���� ���������� � ����������� ��������� ����� ������������ ������������� �������� (����� �� ������ ���������� ������� ��������)


}

#endif
