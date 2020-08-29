project(kypluk_benchmarks)

function(add_benchmark name)
    set(exe ${ARGN})
    string(CONCAT exe ${CMAKE_CURRENT_SOURCE_DIR} / ${exe})
    add_executable(benchmark_${name} ${exe})
endfunction()

add_benchmark(big_integer_add BigInteger/add.cpp)
add_benchmark(big_integer_mult BigInteger/mult.cpp)
