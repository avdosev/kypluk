#include <kypluk/big_integer.h>
#include <kypluk/test.h>

using namespace kypluk;

class test_bigint final : test {
    public:
        void test_sum() {
            BigInt one = 1, two = 2, three = 3, tre = 3333;
            EQUAL(one+one, two)
            EQUAL(one+two, three)

            NOT_EQUAL(one+two, tre)

            BigInt hundred = 100, two_hundred = 200, fourteen = 14, forty_two = 42;

            EQUAL(hundred+hundred, two_hundred)
            EQUAL(fourteen+fourteen+fourteen, forty_two)
        }

        void test_sub() {
            BigInt one = 1, two = 2, three = 3;
            EQUAL(two-one, one)
            EQUAL(three-one, two)
            EQUAL(three-two, one)

            NOT_EQUAL(two-one, two)

            BigInt hundred = 100, two_hundred = 200, fourteen = 14, forty_two = 42;

            EQUAL(two_hundred-hundred, hundred)
            EQUAL(fourteen+fourteen, forty_two-fourteen)
        }

        void run() override {
            test_sum();
            test_sub();
        }
};


int main() {
	test_bigint().run();
}
