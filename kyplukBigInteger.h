#pragma once

//потом разберусь со всеми инклудами
#include <kyplukDefine.h>
#include <kyplukVector.h>
#include <kyplukList.h>

#include <kyplukUtility.h>

namespace kypluk {

//ebanuy rot ska
class unlimInt {
	private:
    	using base_t = uint8_t;
    	using container_t = Vector<base_t>;
		
		static const base_t base = 10;
    	//знак + или - 
    	//true - is_negative
    	//false - is_not_negative
    	bool _is_negative;
		container_t arr;
		
		void remove_leading_zeros() {
			while (!arr.empty() and arr.back() == 0)
				arr.pop_back();
			if (arr.empty()) {
				arr.push_back(0);
				_is_negative = false;
			}
		}
		
	public:
		class division_by_zero : public logic_error {};
		
		unlimInt(llint other = 0) {
			_is_negative = other < 0;
			if (_is_negative) other = -other;
			arr.push_back(other%10);
			while ((other/=10) != 0) {
				arr.push_back(other%10);
		    }
		}
		
		unlimInt(const unlimInt & other) {
			*this = other;
		}
		
		~unlimInt() {
			arr.clear();
		}
		
		Size_t length() const {
			return arr.size();
		}
		
		unlimInt& add (const unlimInt& other) {
			// мы напишем лишь сложение двух положительных чисел
        	// остальное мы выведем, используя смену знака и вычитание
			if (this->negative()) {
                if (other.negative()) return this->neg().add(-other).neg();
                else return *this = other - this->neg();
	        }
	        else if (other.negative()) return this->sub(-other);
	        
			if (arr.size() < other.arr.size()) {
				Size_t bufSize = other.arr.size()-arr.size();
				//arr.reserve(arr.size()+bufSize+1);				
				for (Size_t i = 0; i < bufSize; i++)
					arr.push_back(0);
			}
		    
            base_t desyatok = 0;
			for (auto i = this->arr.begin(), j = other.arr.begin(); i != this->arr.end(); ++i) {
		        *i = *i + desyatok + ( j == other.arr.end() ? 0 : *j );
		        
		        if (*i >= base) {
		            desyatok = 1;//i / 10
		            *i -= base;//i % 10
		        } else {
		        	desyatok = 0;
				}
				
		        if (j != other.arr.end()) ++j;
		    }
		    
		    if (desyatok)
				arr.push_back(1);
			
		    return *this;
		}
		
		unlimInt& sub (const unlimInt& other) {
			
			if (other.negative()) return this->add(-other);
	        else if (this->negative()) return this->neg().add(other).neg();
	        else if (*this < other) return *this = -(other - *this);
	        
			bool carry = false;
	        for (auto i = this->arr.begin(), j = other.arr.begin(); j != other.arr.end() || carry != 0; ++i) {
                *i -= carry + (j != other.arr.end() ? *j : 0);
                carry = *i > base;
                if (carry) *i += base;
                if (j != other.arr.end()) ++j;
	        }
	 
	        this->remove_leading_zeros();
			
		    return *this;
		}
		
		/*unlimInt& mult10(unlimInt other = 1) {
			if ((*this) != 0) {
				//container_t temp()
				for (unlimInt i = 0; i != other; ++i) 
					arr.push_front(0);
			}
			return *this;
		}*/
		
		unlimInt& mult10(Size_t other = 1) {
			if ((*this) != 0) {
				container_t temp(other, 0);
				swap(temp, arr);
				arr.push_back(temp);
				/*for (unlimInt i = 0; i != other; ++i) 
					arr.push_front(0);*/
			}
			return *this;
		}
		
		//fix ускорь множеие
		unlimInt& mult0to9 (base_t other) {
			if (other == 0) (*this) = 0;
			else {
				base_t carry = 0;
				for (base_t& item : this->arr) {
					item = item * other + carry;
					carry = item / base;
					item %= base;
				}
				if (carry) this->arr.push_back(carry);	
			}
			return *this;
		}
		
		unlimInt& mult (unlimInt other) {
			unlimInt xraniliche = *this;
			bool thisNegative = this->_is_negative;
			xraniliche._is_negative = false;
			(*this) = 0;
			//пред расчеты
			Vector<unlimInt> mult_temp(base, xraniliche);
			for (base_t i = 0; i < base; i++) {
				mult_temp[i].mult0to9(i);
			}
			Vector<Size_t> first_size(base, 0);
			for (base_t i = 0; i < base; i++) {
				first_size[i] = mult_temp[i].arr.size();
			}
			
			Size_t j = 0;
			for (auto i = other.arr.begin(); i != other.arr.end(); ++i, ++j)
			{
				(*this) += mult_temp[*i].mult10(j-(mult_temp[*i].arr.size()-first_size[*i]));
			}
			
			//boolean xor
			this->_is_negative = (!other._is_negative && thisNegative) || (other._is_negative && !thisNegative);
			
			return *this;
		}
		
		
		Pair<unlimInt, unlimInt> divmod(const unlimInt &b1) const {
            if (b1 == 0) throw division_by_zero();
	        
			base_t norm = base / (b1.arr.back() + 1);
	        unlimInt a = this->abs() * norm;
	        unlimInt b = b1.abs() * norm;
	        unlimInt q, r;
	        //q.arr.resize(arr.arr.size());
	        q.arr = container_t(a.arr.size());
	
	        for (auto i = --a.arr.end(), j = --q.arr.end(); i < a.arr.end(); --i, --j) {
	            r *= base;
	            r += *i;
	            base_t s1 = r.arr.size() <= b.arr.size() ? 0 : r.arr.at(b.arr.size());
	            base_t s2 = r.arr.size() <= b.arr.size() - 1 ? 0 : r.arr.at(b.arr.size() - 1);
                int d = ( base * s1 + s2) / b.arr.back();
	            r -= b * d;
	            while (r < 0) {
	                r += b;
					--d;
				}
	            *j = d;
	        }
	
	        q._is_negative = this->_is_negative || b1._is_negative;
	        r._is_negative = this->_is_negative;
	        
	        q.remove_leading_zeros();
        	r.remove_leading_zeros();

	        return Pair<unlimInt, unlimInt>({q, r.divbase(norm)});
	    }
	    
        unlimInt divbase(int8_t v) const {
	    	unlimInt copy = *this;
	    	if (v < 0) {
            	copy._is_negative = true;
				v = -v;
            }
            base_t rem = 0;
	        for (auto i = --copy.arr.end(); i < copy.arr.end(); --i) {
	            base_t cur = *i + rem * base;
                *i = cur / v;
                rem = cur % v;
	        }
	        copy.remove_leading_zeros();
	        return copy;
		}
		
		//--------
		//dispensable methods
		//--------
		
		int sign() const {
			if (this->negative())
				return -1;
			return (*this) == 0 ? 0 : 1; 
		}
		
		unlimInt abs() const {
			unlimInt other(*this);
			other._is_negative = false;
			return other;
		}
		
		bool odd() const {
        	return this->arr.front() & 1;
		}
		
		bool even() const {
		    return !this->odd();
		}
		
		inline bool negative() const {
			return this->_is_negative;
		}
		
		unlimInt& neg() {
			this->_is_negative = !(this->_is_negative);
			return *this;
		}
		
		bool zero() {
			return *this == 0;
		}
		
		//---------
		//static function
		//---------
		
		static Vector<char> to_vstring(const unlimInt& number) {
			Size_t j = number.length()-1+number._is_negative;
			Vector<char> buf(number.length()+1+number._is_negative);
			if (number._is_negative) buf.front() = '-';
			for (auto i = number.arr.begin(); j >= 0+number._is_negative and i != number.arr.end(); --j, ++i) {
				buf[j] = *i+'0';
			}
			
			buf.back() = '\0';
			return buf;
		}
		
		static unlimInt from_string(const char * value) {
			unlimInt res;
			bool is_ngt = false;
			if (*value) {
				if (*value == '-') {
					is_ngt = true;
					value++;
				}
				res = *value - '0';
				value++;
			}
			while (*value) {
				res.mult10(1).add(*value - '0');
				value++;
			}
			res._is_negative = is_ngt;
			return res;
		}
		
		static int compare(const unlimInt& raz, const unlimInt& dva) {
			if (raz._is_negative != dva._is_negative) 
				return dva._is_negative - raz._is_negative;
			
			if (raz.length() != dva.length())
				return raz.length() > dva.length() ? 1 : -1;
			
			for (auto i = --raz.arr.end(), j = --dva.arr.end(); i < raz.arr.end() and j < dva.arr.end(); --i, --j)
			{
				if (*i != *j)
					return (*i - *j) * (raz._is_negative ? -1 : 1);
			}
			
			return 0;
		}
		
		//---------
		//operators
		//---------
		
		unlimInt& operator ++ () {
			if (++(*arr.begin()) > 9) {
				*arr.begin() -= 10;
				add(unlimInt(10));
			}
			
			return *this;
		}
		
		unlimInt& operator = (const unlimInt& other) {
			arr = other.arr;
			_is_negative = other._is_negative;
			return *this;
		}
		
		unlimInt& operator += (const unlimInt &other) {
			return add(other);
		}

		unlimInt& operator -= (const unlimInt &other) {
			return sub(other);
		}
		
		unlimInt& operator *= (const unlimInt& other) {
			return mult(other);
		}
		
		unlimInt& operator /= (const unlimInt& other) {
			return *this = this->divmod(other).first;
		}
		
		friend const unlimInt operator + (const unlimInt& raz, const unlimInt& dvas) {
			unlimInt other = raz;
			return other.add(dvas);
		}
		
		friend const unlimInt operator - (const unlimInt& raz, const unlimInt& dvas) {
			unlimInt other = raz;
			return other.sub(dvas);
		}

		friend const unlimInt operator * (const unlimInt& raz, const unlimInt& dvas) {
			unlimInt other = raz;
			return other.mult(dvas);
		}
		
		friend const unlimInt operator / (const unlimInt& raz, const unlimInt& dvas) {
			return raz.divmod(dvas).first;
		}
		
		friend const unlimInt operator % (const unlimInt& raz, const unlimInt& dvas) {
			return raz.divmod(dvas).second;
		}
		
		const unlimInt operator +() const {
		    return unlimInt(*this);
		}
		 
		const unlimInt operator -() const {
			unlimInt temp(*this);
			temp.neg();
		    return temp;
		}
		
		bool operator != (const unlimInt& other) const{
			return compare(*this, other) != 0;
		}
		
		bool operator >= (const unlimInt& other) const {
			return compare(*this, other) >= 0;
		}
		
		bool operator <= (const unlimInt& other) const {
			return compare(*this, other) <= 0;
		}
		
		bool operator > (const unlimInt& other) const {
			return compare(*this, other) > 0;
		}
		
		bool operator < (const unlimInt& other) const {
			return compare(*this, other) < 0;
		}
		
		bool operator == (const unlimInt& other) const{
			return compare(*this, other) == 0;
		}
};
using BigInteger = unlimInt;
/*
fast factor
http://www.luschny.de/math/factorial/binarysplitfact.html
*/ 

} // end namespace kypluk
