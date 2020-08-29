#include <kypluk/test.h>
#include <kypluk/parallel/algorithm.h>
#include <vector>
#include <functional>
#include <random>

class test_algorithm final : public test  {
public:
    void check_reduce() {
        std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto res = kypluk::parallel::reduce(vec, std::plus<>(), 0);
        EQUAL(res, 45);
        res = kypluk::parallel::reduce(vec, [](auto acc, auto val){
            return std::min(acc, val);
        }, std::numeric_limits<decltype(vec)::value_type>::max());
        EQUAL(res, 1);
    }

    void check_massive_reduce() {
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, 9);
        std::vector<int> nums(1000);
        for (auto& item : nums) {
            item = dist(rd);
        }
        using kypluk::parallel::async;
        auto fut1 = async([&nums]{
            return kypluk::parallel::reduce(nums, std::plus<>(), 0);
        });
        auto fut2 = async([&nums]{
            return kypluk::parallel::reduce(nums, std::minus<>(), 0);
        });
        NOT_EQUAL(fut1.get(), 0); // value not use
        NOT_EQUAL(fut2.get(), 0); // value not use
    }

    void check_for_n() {
        std::vector<int> vec(100000, 0);
        kypluk::parallel::for_n(vec.size(), [&vec](size_t i){
            vec[i] += 1;
        });
        for (auto item: vec) {
            EQUAL(item, 1);
        }
    }

    void run() override {
        check_reduce();
        check_massive_reduce();
        check_for_n();
    }
};

int main() {
    test_algorithm().run();
}
