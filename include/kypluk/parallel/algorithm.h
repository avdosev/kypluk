#ifndef KYPLUK_PARALLEL_ALGORITHM_H
#define KYPLUK_PARALLEL_ALGORITHM_H

#include <kypluk/parallel/future.h>

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

}

}

#endif // KYPLUK_PARALLEL_ALGORITHM_H
