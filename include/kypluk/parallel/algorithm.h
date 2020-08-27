#ifndef KYPLUK_PARALLEL_ALGORITHM_H
#define KYPLUK_PARALLEL_ALGORITHM_H

#include <kypluk/parallel/future.h>
#include <vector>
#include <algorithm>

namespace kypluk {

namespace parallel {

template <typename Range, typename F, typename AccType>
AccType reduce(Range&& range, F function, AccType&& default_value) {
    auto previous_value = default_value;
    for (auto it = range.begin(); it != range.end(); ++it) {
        previous_value = kypluk::parallel::async(function, previous_value, *it).get();
    }
    return previous_value;
}

template <typename Function>
void for_n(size_t n, Function function) {
    size_t concurrency = detail::_thread_pool.concurrency();
    size_t sections_count = std::max<size_t>(n / concurrency, 1);
    std::vector<std::future<void>> sections;
    sections.reserve(sections_count);
    for (size_t i = 0; i < sections_count; ++i) {
        sections.emplace_back(kypluk::parallel::async([n, concurrency, &function](size_t thread_id){
            size_t max_iter = std::min(n, (thread_id+1)*concurrency);
            for (size_t j = thread_id*concurrency; j < max_iter; ++j) {
                function(j);
            }
        }, i));
    }
    for (auto& section: sections)
        section.wait();
}

}

}

#endif // KYPLUK_PARALLEL_ALGORITHM_H
