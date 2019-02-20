#ifndef _kypluk_BigInteger_
#define _kypluk_BigInteger_

//потом разберусь со всеми инклудами
#include <kyplukDefine.h>
#include <kyplukVector.h>
#include <kyplukList.h>

/*class BigInteger {
	private:
		list<uint8_t> mas;
	public:
		BigInt(unsigned arr in = 0) {
			mas.push_back(in % 10);
			while ((in /= 10) > 0)
				mas.push_back(in % 10);
		}
		
		BigInt& mult10(unsigned arr puk = 1) {
			for (short int i = 0; i < puk; i++)
				mas.push_front(0);
			return *this;
		}
		
		BigInt& mult0to9(unsigned int puk) {
			BigInt xraniliche(*this);
			(*this) = 0;
			for (int i = 0; i < puk; i++) {
				(*this) += xraniliche;
			}
			return *this;
		}
		
		BigInt& mult(const BigInt& puk) {
			BigInt xraniliche;
			xraniliche = *this;
			(*this) = 0;
			size_t j = 0;
			for (auto i = puk.mas.begin(); i != puk.mas.end(); ++i, ++j) {
				BigInt xraniliche1 = xraniliche;
				(*this) += xraniliche1.mult0to9(*i).mult10(j);
			}
			return *this;
		}
		
		static void print(const BigInt& p) {
			for_each(p.mas.rbegin(), p.mas.rend(), [](int n) { cout << n; });
		}
		
		BigInt& operator+=(const BigInt& puk) {
			if (mas.size() < puk.mas.size()) {
				size_t buf = puk.mas.size() - mas.size(); //xmm
				for (size_t i = 0; i < buf; i++)
					mas.push_back(0);
			}
			int desyatok = 0;
			auto i = mas.begin();
			for (auto j = puk.mas.begin(); i != mas.end() and j != puk.mas.end();
					 ++i, ++j) {
				*i = *i + *j + desyatok;
				desyatok = 0;
				if (*i > 9) {
					desyatok = 1; // i / 10
					*i -= 10;     // i % 10
				}
			}
			if (i != mas.end()) {
				for (; i != mas.end(); ++i) {
					if (desyatok != 0) {
						*i = *i + desyatok;
						desyatok = 0;
						if (*i > 9) {
							desyatok = 1; // i / 10
							*i -= 10;     // i % 10
						}
					}
				}
			}
			if (desyatok)
				mas.push_back(1);
			return *this;
		}
};*/
namespace kypluk {

//ebanuy rot ska
class unlimInt {
	private:
    	//char znak = '';//знак + или - //еще рановато
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
			*this = puk;
		}
		
		
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
			if ((*this)!=0)
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
		
		static Vector<char> to_cstring(const unlimInt& number) {
			Size_t j = number.length()-1;
			Vector<char> buf(number.length()+1);
			for (auto i = number.arr.begin(); j >= 0 and i != number.arr.end(); --j, ++i) {
				buf[j] = *i+'0';
			}
			
			buf[buf.size()-1]='\0';
			return buf;
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

} // end namespace kypluk
#endif
