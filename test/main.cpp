#include "trit.h"
#include <iostream>
int main() {
    test_trit()
        .run();
    using kypluk::trit;
    using namespace kypluk::trit_const;
    auto check = [](trit t){
        std::cout << t.is(trit::logical::False) << " " << t.is(trit::logical::True) << " " << t.is(trit::logical::None) << std::endl;
    };
    check(!_false);
    check(!none);
    check(!_true);
}

