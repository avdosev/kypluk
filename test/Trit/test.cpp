#include "kypluk/test.h"

#include <kypluk/trit.h>
#include <iostream>

class test_trit final : public test  {
    public:
        void check_not() {
            using kypluk::trit;
            EQUAL(!trit(trit::logical::False), trit::logical::True);
            EQUAL(!trit(trit::logical::None), trit::logical::None);
            EQUAL(!trit(trit::logical::True), trit::logical::False);
        }

        void check_and() {
            using kypluk::trit;
            using namespace kypluk::trit_const;

            EQUAL(False && False, False);
            EQUAL(False && None, False);
            EQUAL(False && True, False);

            EQUAL(None && False, False);
            EQUAL(None && None, None);
            EQUAL(None && True, None);

            EQUAL(True && False, False);
            EQUAL(True && None, None);
            EQUAL(True && True, True);
        }

        void check_or() {
            using kypluk::trit;
            using namespace kypluk::trit_const;

            EQUAL(_false || _false, _false);
            EQUAL(_false || none, none);
            EQUAL(_false || _true, _true);

            EQUAL(none || _false, none);
            EQUAL(none || none, none);
            EQUAL(none || _true, _true);

            EQUAL(_true || _false, _true);
            EQUAL(_true || none, _true);
            EQUAL(_true || _true, _true);
        }

        void run() override {
            check_not();
            check_and();
            check_or();
        }
};

int main() {
    test_trit().run();
}