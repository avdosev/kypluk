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
    	//int8_t _sign = '';//знак + или - //еще рановато
    	using container_t = List<uint8_t>;
		container_t arr;
		
	public:
		
		unlimInt(llint puk = 0) {
			arr.push_back(puk%10);
			while ((puk/=10) != 0) {
				arr.push_back(puk%10);
		    }
		}
		
		unlimInt(const unlimInt & puk) {
			arr = puk.arr;
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
		
		unlimInt& fact() {
			unlimInt neoPuk; neoPuk = (*this);
			for (unlimInt i = 1; i < neoPuk; ++i )
				(*this)*=i;
			return *this;
		}
		
		//---------
		//static function
		//---------
		
		static Vector<char> to_vstring(const unlimInt& number) {
			Size_t j = number.length()-1;
			Vector<char> buf(number.length()+1);
			for (auto i = number.arr.begin(); j >= 0 and i != number.arr.end(); --j, ++i) {
				buf[j] = *i+'0';
			}
			
			buf[buf.size()-1]='\0';
			return buf;
		}
		
		static unlimInt from_string(const char * value) {
			unlimInt res;
			if (*value) {
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
			if (raz.length() != dva.length())
				return raz.length() > dva.length() ? 1 : -1;
			
			for (auto i = --raz.arr.end(), j = --dva.arr.end(); i != raz.arr.end() and j != dva.arr.end(); --i, --j)
			{
				if (*i != *j)
					return *i - *j;
			}
			
			return 0;
			
			/*//xex, stack time
			struct {
				char one, two;
			} comp = {0, 0
			};*/
			
			/*for (auto j = dva.arr.begin(), i = arr.begin(); i != arr.end(); ++i, ++j) {
				if (*i != *j) comp = {*i, *j};
		    }
			if (comp.one == comp.two)
				return 0;
			return comp.one > comp.two ? 1 : -1;*/
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
		
		unlimInt& operator += (const unlimInt &puk) {
			return add(puk);
		}

		
		unlimInt& operator = (const unlimInt& puk) {
			arr = puk.arr;
			return *this;
		}
		
		unlimInt& operator *= (const unlimInt& puk) {
			return mult(puk);
		}
		
		friend unlimInt operator + (const unlimInt& raz, const unlimInt& dvas) {
			unlimInt puk = raz;
			return puk.add(dvas);
		}

		friend unlimInt operator * (const unlimInt& raz, const unlimInt& dvas) {
			unlimInt puk = raz;
			return puk.mult(dvas);
		}
		
		bool operator != (const unlimInt& puk) const{
			return compare(*this, puk) != 0;
		}
		
		bool operator >= (const unlimInt& puk) {
			return compare(*this, puk) >= 0;
		}
		
		bool operator <= (const unlimInt& puk) {
			return compare(*this, puk) <= 0;
		}
		
		bool operator > (const unlimInt& puk) {
			return compare(*this, puk) > 0;
		}
		
		bool operator < (const unlimInt& puk) {
			return compare(*this, puk) < 0;
		}
		
		bool operator == (const unlimInt& puk) {
			return compare(*this, puk) == 0;
		}
};
/*
friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
        int norm = base / (b1.a.back() + 1);
        bigint a = a1.abs() * norm;
        bigint b = b1.abs() * norm;
        bigint q, r;
        q.a.resize(a.a.size());

        for (int i = a.a.size() - 1; i >= 0; i--) {
            r *= base;
            r += a.a[i];
            int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            int d = ((long long) base * s1 + s2) / b.a.back();
            r -= b * d;
            while (r < 0)
                r += b, --d;
            q.a[i] = d;
        }

        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return make_pair(q, r / norm);
    }
*/

} // end namespace kypluk
#endif
