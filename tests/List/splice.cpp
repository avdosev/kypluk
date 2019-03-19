#include <iostream>

#include <kyplukList.h>

using namespace std;
using namespace kypluk;

int main() {
	List<int> puk;
	for (int i = 1; i < 10; i++)
		puk.push_back(i);
	
	cout << "elements: \n";
	for (int item : puk) {
		cout << item << ", ";
	}
	cout << "\n";
	
	cout << *puk.mid() << std::endl;
}
