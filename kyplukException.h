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

class logic_error : public Exception {};   
class runtime_error : public Exception {}; 


class out_of_range : public logic_error {}; 
class length_error : public logic_error {};
class domain_error : public logic_error {}; 
class invalid_argument : public logic_error {};

class range_error : public runtime_error {}; 
class overflow_error : public runtime_error {}; 
class underflow_error : public runtime_error {}; 

}

#endif
