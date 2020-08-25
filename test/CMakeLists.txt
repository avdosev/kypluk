project(kypluk_test)

function(make_test TestFolder)
    string(TOLOWER ${TestFolder} test_folder)
    string(CONCAT exec_test test_ ${test_folder})
    set(exe ${TestFolder}/test.cpp)
    add_executable(${exec_test} ${exe})
    add_test(NAME ${TestFolder}_test COMMAND ${exec_test})
endfunction()

make_test(Trit)
make_test(BigInteger)
make_test(List)
make_test(ThreadPool)