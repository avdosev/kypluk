#pragma once

#include <kyplukBigInteger.h>

namespace kypluk {
	
template <Size_t accuracy>
class Decimal {
	private:
		unlimInt dec;
		static const unlimInt base;
	public:	
		Decimal() {}
		
		Decimal(unlimInt puk) {
			swap(dec, puk.mult10(accuracy));
		}

        Decimal(llint value) {
            dec = value;
            dec.mult10(accuracy);
        }
		
		Decimal(const Decimal& other) {
			*this = other;
		}
		
		//-----------
		//static function
		//-----------
		
		static Vector<char> to_vstring(const Decimal& number, char point = '.') {
			Vector<char> temp = unlimInt::to_vstring(number.dec);
			Size_t charsAfterPoint = accuracy;
            if (temp.size()-2 < charsAfterPoint)  {
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
		    temp[temp.size()-2-charsAfterPoint] = point;

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
                bf = *value - '0';
				value++;
			}
			Size_t acc = accuracy;
			bool point_cheked = false;
			
			for (; *value; value++) {
				if (point_cheked) {
					if (acc) acc--;
				}
					
				if (*value <= '9' && *value >= '0') 
                    bf.mult10(1).add(*value - '0');
                else if (*value == '.' || *value == ',') {
					point_cheked = true;
				}
					
			}
			if (acc) bf.mult10(acc);
			if (is_ngt) bf.neg();
			
			return res;
		}
		
		//-----------
		//operator
		//-----------
		
		Decimal& operator = (const Decimal& other) {
			this->dec = other.dec;
			return *this;
		}
		
		Decimal& operator += (const Decimal& other) {
			dec += other.dec;
			return *this;
		}
		
		Decimal& operator -= (const Decimal& other) {
			dec -= other.dec;
			return *this;
		}
		
		Decimal& operator *= (const Decimal& other) {
			dec *= other.dec;
			dec /= base;
			return *this;
		}
		
		Decimal& operator /= (const Decimal& other) {
			dec *= base;
			dec /= other.dec;
			return *this;
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
			temp.dec.neg();
		    return temp;
		}
};
	//Hack
	template <Size_t accuracy>
	const unlimInt Decimal<accuracy>::base = unlimInt(1).mult10(accuracy);

    using decimal = Decimal<12>;
}
