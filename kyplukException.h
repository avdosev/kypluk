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

class logic_error : public Exception {};   //исключение, которое возникает при наличии логических ошбок к коде программы
class runtime_error : public Exception {}; //общий тип исключений, которые возникают во время выполнения

//логические ошибки
class logic_error : public out_of_range{}; //исключение, которое возникает при попытке доступа к элементам вне допустимого диапазона
class logic_error : public length_error{}; //исключение, которое возникает при попытке создать объект большего размера, чем допустим для данного типа
class logic_error : public domain_error{}; //исключение, которое возникает, если для некоторого значения, передаваемого в функцию, не определено результата
class logic_error : public invalid_argument{}; //исключение, которое возникает при передаче в функцию некорректного аргумента

//рантайм ошибки
class runtime_error : public range_error{}; //исключение, которое возникает, когда полученный результат превосходит допустимый диапазон
class runtime_error : public overflow_error{}; //исключение, которое возникает, если полученный результат превышает допустимый диапазон
class runtime_error : public underflow_error{}; //исключение, которое возникает, если полученный в вычислениях результат имеет недопустимые отрицательное значение (выход за нижнюю допустимую границу значений)


}

#endif
