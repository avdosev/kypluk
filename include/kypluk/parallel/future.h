#ifndef KYPLUK_FUTURE_H
#define KYPLUK_FUTURE_H

#include <future>
#include <kypluk/parallel/thread_pool.h>

namespace kypluk {

namespace parallel {

template< class Function, class... Args>
std::future<std::invoke_result_t<std::decay_t<Function>,
        std::decay_t<Args>...>>
async( Function f, Args... args ) {
    using return_type = std::invoke_result_t<std::decay_t<Function>,
            std::decay_t<Args>...>;
    auto promise_ptr = std::make_shared<std::promise<return_type>>();
    auto future = promise_ptr->get_future();
    kypluk::parallel::detail::_thread_pool.add_task([f, args..., promise_ptr]() {
        promise_ptr->set_value(f(args...));
    });
    return future;
}

}

}

#endif //KYPLUK_FUTURE_H
