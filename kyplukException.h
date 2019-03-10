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

class LogicError : public Exception {};   //����������, ������� ��������� ��� ������� ���������� ����� � ���� ���������
class RuntimeError : public Exception {}; //����� ��� ����������, ������� ��������� �� ����� ����������

/*
out_of_range: ����������, ������� ��������� ��� ������� ������� � ��������� ��� ����������� ���������
length_error: ����������, ������� ��������� ��� ������� ������� ������ �������� �������, ��� �������� ��� ������� ����
domain_error: ����������, ������� ���������, ���� ��� ���������� ��������, ������������� � �������, �� ���������� ����������
invalid_argument: ����������, ������� ��������� ��� �������� � ������� ������������� ���������

range_error: ����������, ������� ���������, ����� ���������� ��������� ����������� ���������� ��������
overflow_error: ����������, ������� ���������, ���� ���������� ��������� ��������� ���������� ��������
underflow_error: ����������, ������� ���������, ���� ���������� � ����������� ��������� ����� ������������ ������������� �������� (����� �� ������ ���������� ������� ��������)
*/

}

#endif
