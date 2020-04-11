project(kypluk_test)

set(test_trit Trit/test.cpp)
add_executable(test_trit ${test_trit})
add_test(NAME Trit_test COMMAND test_trit)


set(test_biginteger BigInteger/test.cpp)
add_executable(test_biginteger ${test_biginteger})
add_test(NAME BigInteger_test COMMAND test_biginteger)