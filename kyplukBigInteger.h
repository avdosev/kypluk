#ifndef _kypluk_BigInteger_
#define _kypluk_BigInteger_

//потом разберусь со всеми инклудами
#include <kyplukDefine.h>
#include <kyplukVector.h>
#include <kyplukList.h>
#include <kyplukPair.h>

namespace kypluk {

//ebanuy rot ska
class unlimInt {
	private:
    	//знак + или - 
    	//true - is_negative
    	//false - is_not_negative
    	bool _is_negative;
    	using container_t = List<uint8_t>;
		container_t arr;
		
	public:
		
		unlimInt(llint puk = 0) {
			_is_negative = puk < 0;
			arr.push_back(puk%10);
			while ((puk/=10) != 0) {
				arr.push_back(puk%10);
		    }
		}
		
		unlimInt(const unlimInt & puk) {
			*this = puk;
			
		}
		/*
		проблема с конвертацией типов
		хз как е рашать
		unlimInt(const char * value) {
			while (*value) {
				arr.push_back( *value - '0');
				value++;
			}
		}*/
		
		Size_t length() const {
			return arr.size();
		}
		
		unlimInt& add (const unlimInt& puk) {
			// мы напишем лишь сложение двух положительных чисел
        	// остальное мы выведем, используя смену знака и вычитание
			if (this->_is_negative) {
                if (puk._is_negative) return -(-*this + (-puk));
                else return puk - (-*this);
	        }
	        else if (puk._is_negative) return *this - (-puk);
	        
			if (arr.size() < puk.arr.size()) {
				Size_t buf = puk.arr.size()-arr.size();
				for (Size_t i = 0; i < buf; i++)
					arr.push_back(0);
			}
			
		    int desyatok = 0;
		    auto i = arr.begin();
			for (auto j = puk.arr.begin(); i != arr.end() and j != puk.arr.end(); ++i, ++j) {
		        *i = *i + *j + desyatok;
		        desyatok = 0;
		        if (*i > 9) {
		            desyatok = 1;//i / 10
		            *i -= 10;//i % 10
		        }
		    }
		    if (i != arr.end())
		    {
		    	for ( ; i != arr.end(); ++i) {
		    		if (desyatok != 0) {
				        *i = *i + desyatok;
				        desyatok = 0;
				        if (*i > 9) {
				            desyatok = 1;//i / 10
				            *i -= 10;//i % 10
				        }
				    }
			    }
		    }
		    if (desyatok)
				arr.push_back(1);
			
		    return *this;
		}
		
		unlimInt& sub (const unlimInt& puk) {
			
			if (puk._is_negative) return *this + (-puk);
	        else if (this->_is_negative) return -(-*this + puk);
	        else if (*this < puk) return -(puk - *this);
	        int carry = 0;
	        for (size_t i = 0; i < puk._digits.size() || carry != 0; ++i) {
	                this->_digits[i] -= carry + (i < puk._digits.size() ? puk._digits[i] : 0);
	                carry = this->_digits[i] < 0;
	                if (carry != 0) this->_digits[i] += big_integer::BASE;
	        }
	 
	        this->_remove_leading_zeros();
	        return *this;
			
		    return *this;
		}
		
		unlimInt& mult10(unsigned short int puk = 1) {
			if ((*this) != 0)
				for (short int i = 0; i < puk; i++) 
					arr.push_front(0);
			return *this;
		}
		
		//fix ускорь множеие
		unlimInt& mult0to9 (unsigned short int puk) {
			unlimInt xraniliche(*this);
			(*this) = 0;
			
			for (int i = 0; i < puk; i++)
			{
				(*this) += xraniliche;	
			}
			
			return *this;
		}
		
		unlimInt& mult (const unlimInt& puk) {
			unlimInt xraniliche;
			xraniliche = *this;
			(*this) = 0;
			Size_t j = 0;
			for (auto i = puk.arr.begin(); i != puk.arr.end(); ++i, ++j)
			{
				unlimInt xraniliche1 = xraniliche; 
				(*this) += xraniliche1.mult0to9(*i).mult10(j);
			}
			
			return *this;
		}
		
		
		Pair<unlimInt, unlimInt> divmod(const unlimInt &b1) {
	        int norm = base / (b1.a.back() + 1);
	        unlimInt a = this->abs() * norm;
	        unlimInt b = b1.abs() * norm;
	        unlimInt q, r;
	        q.a.resize(a.a.size());
	
	        for (int i = a.a.size() - 1; i >= 0; i--) {
	            r *= base;
	            r += a.a[i];
	            int s1 = r.arr.size() <= b.arr.size() ? 0 : r.arr[b.arr.size()];
	            int s2 = r.arr.size() <= b.arr.size() - 1 ? 0 : r.arr[b.a.size() - 1];
	            int d = ((long long) base * s1 + s2) / b.a.back();
	            r -= b * d;
	            while (r < 0)
	                r += b, --d;
	            q.a[i] = d;
	        }
	
	        q._sign = this->_sign * b1._sign;
	        r._sign = this->_sign;

	        return Pair({q, r / norm});
	    }
		
		//--------
		//dispensable methods
		//--------
		
		int sign() const {
			if ((*this) == 0) return 0; 
			return this->_is_negative ? -1 : 1;
		}
		
		unlimInt abs() const {
			unlimInt puk(*this);
			puk._is_negative = false;
			return puk;
		}
		
		bool odd() const {
        	return this->arr.front() & 1;
		}
		
		bool even() const {
		    return !this->odd();
		}
		
		//---------
		//static function
		//---------
		
		static Vector<char> to_vstring(const unlimInt& number) {
			Size_t j = number.length()-1;
			Vector<char> buf(number.length()+1+number._is_negative);
			if (number._is_negative) buf.front() = '-';
			for (auto i = number.arr.begin(); j >= 0+number._is_negative and i != number.arr.end(); --j, ++i) {
				buf[j] = *i+'0';
			}
			
			buf[buf.size()-1]='\0';
			return buf;
		}
		
		static unlimInt from_string(const char * value) {
			unlimInt res;
			if (*value) {
				if (*value == '-') {
					res._is_negative = true;
					value++;
				}
				res = *value - '0';
				value++;
			}
			while (*value) {
				res.mult10(1).add(*value - '0');
				value++;
			}
			return res;
		}
		
		static int compare(const unlimInt& raz, const unlimInt& dva) {
			if (raz._is_negative != dva._is_negative) 
				return raz.sign()-dva.sign();
			
			if (raz.length() != dva.length())
				return raz.length() > dva.length() ? 1 : -1;
			
			for (auto i = --raz.arr.end(), j = --dva.arr.end(); i != raz.arr.end() and j != dva.arr.end(); --i, --j)
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
		
		unlimInt& operator = (const unlimInt& puk) {
			arr = puk.arr;
			_is_negative = puk._is_negative;
			return *this;
		}
		
		unlimInt& operator += (const unlimInt &puk) {
			return add(puk);
		}

		unlimInt& operator -= (const unlimInt &puk) {
			return sub(puk);
		}
		
		unlimInt& operator *= (const unlimInt& puk) {
			return mult(puk);
		}
		
		friend unlimInt operator + (const unlimInt& raz, const unlimInt& dvas) {
			unlimInt puk = raz;
			return puk.add(dvas);
		}
		
		friend unlimInt operator - (const unlimInt& raz, const unlimInt& dvas) {
			unlimInt puk = raz;
			return puk.sub(dvas);
		}

		friend unlimInt operator * (const unlimInt& raz, const unlimInt& dvas) {
			unlimInt puk = raz;
			return puk.mult(dvas);
		}
		
		unlimInt operator +() const {
		    return unlimInt(*this);
		}
		 
		unlimInt operator -() const {
			unlimInt temp(*this);
			temp._is_negative = !temp._is_negative;
		    return temp;
		}
		
		bool operator != (const unlimInt& puk) const{
			return compare(*this, puk) != 0;
		}
		
		bool operator >= (const unlimInt& puk) const {
			return compare(*this, puk) >= 0;
		}
		
		bool operator <= (const unlimInt& puk) const {
			return compare(*this, puk) <= 0;
		}
		
		bool operator > (const unlimInt& puk) const {
			return compare(*this, puk) > 0;
		}
		
		bool operator < (const unlimInt& puk) const {
			return compare(*this, puk) < 0;
		}
		
		bool operator == (const unlimInt& puk) const{
			return compare(*this, puk) == 0;
		}
};

/*

const big_integer operator -(big_integer left, const big_integer& right) {
        
}


const big_integer operator /(const big_integer& left, const big_integer& right) {
        // на ноль делить нельзя
        if (right == 0) throw big_integer::divide_by_zero();
        big_integer b = right;
        b._is_negative = false;
        big_integer result, current;
        result._digits.resize(left._digits.size());
        for (long long i = static_cast<long long>(left._digits.size()) - 1; i >= 0; --i) {
                current._shift_right();
                current._digits[0] = left._digits[i];
                current._remove_leading_zeros();
                int x = 0, l = 0, r = big_integer::BASE;
                while (l <= r) {
                        int m = (l + r) / 2;
                        big_integer t = b * m;
                        if (t <= current) {
                                x = m;
                                l = m + 1;
                        }
                        else r = m - 1;
                }
 
                result._digits[i] = x;
                current = current - b * x;
        }
 
        result._is_negative = left._is_negative != right._is_negative;
        result._remove_leading_zeros();
        return result;
}
*/
} // end namespace kypluk
#endif
