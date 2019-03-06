#ifndef _kypluk_Decimal_
#define _kypluk_Decimal_

#include <kyplukBigInteger.h>

namespace kypluk {
	
template <unsigned accuracy>
class Decimal {
	private:
		unlimInt dec;
		static unlimInt base;
	public:
		Decimal() {}
		
		Decimal(unlimInt puk) {
			dec = puk.mult10(accuracy);
		}
		
		Decimal(const Decimal& other) {
			*this = other;
		}
		
		//-----------
		//static function
		//-----------
		
		static Vector<char> to_vstring(const Decimal& number) {
			Vector<char> temp = unlimInt::to_vstring(number.dec);
			unsigned charsAfterPoint = accuracy;
		    if (temp.size()-2 < charsAfterPoint)  {
		        //temp = (charsAfterPoint-temp.Length+1)*'0'+temp;
		        Vector<char> tttempo(charsAfterPoint-(temp.size()-2), '0');
		        for (auto item : temp) {
		            tttempo.push_back(item);
		        }
		        temp = tttempo;
		    }
		
		    temp.push_back('\0');
		    for (uint i = 0; i < charsAfterPoint; i++) {
		        temp[temp.size()-2-i] = temp[temp.size()-2-(i+1)];
		    }
		    temp[temp.size()-2-charsAfterPoint] = ',';

		    return temp;
		}
		
		static Decimal from_string(const char * value) {
			Decimal res;
			unlimInt& bf = res.dec;
			bool is_ngt = false;
			if (*value) {
				if (*value == '-') {
					is_ngt = true;
					value++;
				}
				res = *value - '0';
				value++;
			}
			unsigned acc = accuracy;
			bool point_cheked = false;
			while (*value || acc) {
				if (*value <= '9' && *value >= '0') 
					res.mult10(1).add(*value - '0');
				else if (*value == '.') {
					
				}
				
				if (value) value++;
				if (point_cheked) {
					acc--;
					if (!value) res.mult10(1);
				}
				
			}
			if (is_ngt) 
			return res;
		}
		
		//-----------
		//operator
		//-----------
		
		Decimal& operator = (const Decimal& other) {
			this->dec = other.dec;
		}
		
		Decimal& operator += (const Decimal& other) {
			dec += other.dec;
		}
		
		Decimal& operator -= (const Decimal& other) {
			dec -= other.dec;
		}
		
		Decimal& operator *= (const Decimal& other) {
			dec *= other.dec;
			dec /= base;
		}
		
		Decimal& operator /= (const Decimal& other) {
			dec *= base;
			dec /= other.dec;
		}
		
		friend const Decimal operator + (const Decimal& raz, const Decimal& dvas) {
			Decimal puk = raz;
			return puk += dvas;
		}
		
		friend const Decimal operator - (const Decimal& raz, const Decimal& dvas) {
			Decimal puk = raz;
			return puk -= dvas;
		}

		friend const Decimal operator * (const Decimal& raz, const Decimal& dvas) {
			Decimal puk = raz;
			return puk *= dvas;
		}
		
		friend const Decimal operator / (const Decimal& raz, const Decimal& dvas) {
			Decimal puk = raz;
			return puk /= dvas;
		}
		
		bool operator != (const Decimal& puk) const{
			return unlimInt::compare(this->dec, puk.dec) != 0;
		}
		
		bool operator >= (const Decimal& puk) const {
			return unlimInt::compare(this->dec, puk.dec) >= 0;
		}
		
		bool operator <= (const Decimal& puk) const {
			return unlimInt::compare(this->dec, puk.dec) <= 0;
		}
		
		bool operator > (const Decimal& puk) const {
			return unlimInt::compare(this->dec, puk.dec) > 0;
		}
		
		bool operator < (const Decimal& puk) const {
			return unlimInt::compare(this->dec, puk.dec) < 0;
		}
		
		bool operator == (const Decimal& puk) const{
			return unlimInt::compare(this->dec, puk.dec) == 0;
		}
		
		const Decimal operator +() const {
		    return *this;
		}
		 
		const Decimal operator -() const {
			Decimal temp = *this;
			temp.dec = -temp.dec;
		    return temp;
		}
};
	//Hack
	template <unsigned accuracy>
	unlimInt Decimal<accuracy>::base = unlimInt(1).mult10(unlimInt(accuracy));
}

#endif
