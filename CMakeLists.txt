cmake_minimum_required(VERSION 3.15)
project(kypluk)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -O3" )

include_directories(include)

add_executable(kypluk
        include/kypluk/fast_math/fast_math.h
        include/kypluk/logs/kLogs.cpp
        include/kypluk/logs/kLogs.h
        include/kypluk/num_array/num_array.h
        include/kypluk/algorithm.h
        include/kypluk/big_integer.h
        include/kypluk/bitset.h
        include/kypluk/decimal.h
        include/kypluk/define.h
        include/kypluk/function.h
        include/kypluk/trit.h
        include/kypluk/list.h
        include/kypluk/math.h
        include/kypluk/number_algorithm.h
        include/kypluk/pair.h
        include/kypluk/queue.h
        include/kypluk/smart_ptr.h
        include/kypluk/stack.h
        include/kypluk/typedef.h
        include/kypluk/unrolled_linked_list.h
        include/kypluk/utility.h
        include/kypluk/vector.h
        test/main.cpp test/trit.h test/test.h)
