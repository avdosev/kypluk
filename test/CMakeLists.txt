project(kypluk_test)

set(test_all main.cpp)
add_executable(test_all ${test_all})
add_test(NAME All_test COMMAND test_all)