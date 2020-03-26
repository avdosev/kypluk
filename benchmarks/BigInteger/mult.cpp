#include <iostream>
#include <ctime>
#include <functional>
#include <kypluk/big_integer.h>
#include <kypluk/math.h>


using namespace kypluk;
using namespace std;

template <class type>
type fact_tree(const type& n)
{
	if (n < 0)
		return 0;
	if (n == 0)
		return 1;
	if (n == 1 || n == 2)
		return n;
	function <type(type, type)> prod_tree = [&prod_tree](const type& l, const type& r) -> type{
		if (l > r)
		return 1;
		if (l == r)
			return l;
		if (r - l == 1)
			return r * l;
		type m = (l + r) / 2;
		type one, two;
		//omp_set_nested(true);
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				one = prod_tree(l, m);
			}
			#pragma omp section
			{
				two = prod_tree(m + 1, r);
			}
		}
		one *= two;		
		
		return one;
	};
	return prod_tree(2, n);
}

int main() {
	Vector<BigInt> number;
	number.push_back(BigInt::from_string("500") );
	number.push_back(BigInt::from_string("1000"));
	number.push_back(BigInt::from_string("1235"));
	number.push_back(BigInt::from_string("2000"));
	number.push_back(BigInt::from_string("3000"));
	number.push_back(BigInt::from_string("4000"));

	BigInt puk1, puk2, puk3;
	time_t start,stop;
	for (size_t i = 0; i < number.size(); i++) {
		cout << kypluk::to_string(number[i]) << ":\n";
		
		start = clock();
		
		puk1 = fact(number[i]);
		
		stop = clock();
		
		cout << "native time: " << ((stop-start)/1000.0) << " second\n";
		
		start = clock();
		
		puk2 = fact_tree(number[i]);
		
		stop = clock();
		cout << "fact tree time: " << ((stop-start)/1000.0) << " second\n";
		
		if (puk1 != puk2) {
			cout << "failed fact tree\n";
		}

		cout << "\n\n";
	}
	BigInt t1 = 12352, t2 = 10000;
	start = clock();
		
	puk1 = pow<BigInt>(t1, t2);
		
	stop = clock();
	cout << "numbers: " << kypluk::to_string(t1) << " ^ " << kypluk::to_string(t2) << std::endl;
	cout << kypluk::to_string(puk1) << std::endl;
	cout << "pow time: " << ((stop-start)/1000.0) << " second\n";
}
