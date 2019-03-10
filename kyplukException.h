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

class LogicError : public Exception {};   //исключение, которое возникает при наличии логических ошбок к коде программы
class RuntimeError : public Exception {}; //общий тип исключений, которые возникают во время выполнения

/*
out_of_range: исключение, которое возникает при попытке доступа к элементам вне допустимого диапазона
length_error: исключение, которое возникает при попытке создать объект большего размера, чем допустим для данного типа
domain_error: исключение, которое возникает, если для некоторого значения, передаваемого в функцию, не определено результата
invalid_argument: исключение, которое возникает при передаче в функцию некорректного аргумента

range_error: исключение, которое возникает, когда полученный результат превосходит допустимый диапазон
overflow_error: исключение, которое возникает, если полученный результат превышает допустимый диапазон
underflow_error: исключение, которое возникает, если полученный в вычислениях результат имеет недопустимые отрицательное значение (выход за нижнюю допустимую границу значений)
*/

}

#endif
