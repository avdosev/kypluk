project(kypluk_test)

set(test_trit Trit/trit.cpp)
add_executable(test_trit ${test_trit})
add_test(NAME Trit_test COMMAND test_trit)