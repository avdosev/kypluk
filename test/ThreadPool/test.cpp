#include <kypluk/test.h>
#include <kypluk/parallel/thread_pool.h>
#include <kypluk/parallel/future.h>

class test_async final : public test  {
    public:
        void check_simple() {
            int val = 12;
            auto future = kypluk::parallel::async([](int i){
                return i;
            }, val);
            EQUAL(future.get(), val);
        }

        void run() override {
            check_simple();
        }
};

int main() {
    test_async().run();
}
