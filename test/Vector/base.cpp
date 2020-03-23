#include <iostream>
#include <kyplukVector.h>

int main ( ) {

    kypluk::Vector<int> v;
    
    const int count = 10;
    v.reserve(count);

    v.push_back(25);
    v.push_back(13);
    
    std::cout << "size before insert: " << v.size() << '\n';
    
    int cs = count - v.size();
    for (int i = 0; i < cs; i++) {
    	v.push_back(i+1);
	}
 	std::cout << "size after insert: " << v.size() << '\n';
 	std::cout << "elements:\n";

    for ( int n : v ) {
        std::cout << n << '\n';
    }
}
