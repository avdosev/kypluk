#ifndef KYPLUK_THREAD_POOL_H
#define KYPLUK_THREAD_POOL_H

#include <thread>
#include <functional>
#include <vector>
#include <chrono>
#include <queue>
#include <mutex>
#include <atomic>
#include <memory>

namespace kypluk {

namespace parallel {

class thread_pool;

class worker {
    public:
        worker(thread_pool& pool) {
            stop = std::make_shared<std::atomic<bool>>(false);

            thread = std::thread([this, &pool]{
                run(stop, pool);
            });
        }

        worker(worker&& moveable) : stop(moveable.stop), thread(std::move(moveable.thread))
        {}



        worker(const worker&) = delete;
        worker &operator= (const worker&) = delete;

        ~worker() {
            *stop = true;
            thread.detach();
        }
    private:
        static void run(std::shared_ptr<std::atomic<bool>> stop_flag, thread_pool& pool);

        std::shared_ptr<std::atomic<bool>> stop;
        std::thread thread;
};


class thread_pool {
    public:
        using size_type = size_t;
        using worker_type = worker;
        using task_type = std::function<void()>;

        thread_pool(size_type concurrency) {
            workers.reserve(concurrency);
            for (size_type i = 0; i < concurrency; ++i) {
                workers.emplace_back(*this);
            }
        }

        void add_task(task_type task) {
            const std::lock_guard lock(tasks_queue_mutex);
            tasks.push(task);
        }

        std::optional<task_type> try_get_task() {
            std::optional<task_type> maybe_task = std::nullopt;
            if (tasks_queue_mutex.try_lock()) {
                if (!tasks.empty()) {
                    maybe_task = std::move(tasks.front());
                    tasks.pop();
                }
                tasks_queue_mutex.unlock();
            }
            return maybe_task;
        }
    private:
        std::mutex tasks_queue_mutex;
        std::queue<task_type> tasks;
        std::vector<worker_type> workers;
};

void worker::run(std::shared_ptr<std::atomic<bool>> stop_flag, thread_pool& pool) {
    while (!*stop_flag) {
        auto next_task = pool.try_get_task();
        if (next_task.has_value()) {
            (*next_task)();
        } else {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1ms);
        }
        std::this_thread::yield();
    }
}

namespace detail {

inline thread_pool _thread_pool{20};

}

} /* namespace parallel */

} /* namespace kypluk */

#endif