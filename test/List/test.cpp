#include <kypluk/test.h>
#include <kypluk/list.h>

using namespace kypluk;

class test_list : test {
    public:
        void check_swap() {
            List<int> one(5), two(10);
            kypluk::swap(one, two);

            EQUAL(one.size(), 10)
            EQUAL(two.size(), 5)
        }


        void check_initialize() {
            List<int> lst;
            for (int i = 0; i < 10; i++)
                lst.push_back(i);

            EQUAL(lst.size(), 10)

            int i = 0;
            for (int item : lst) {
                EQUAL(item, i)
                i++;
            }
        }


        void run() override {
            check_swap();
        }
};

int main() {
    test_list().run();
}
