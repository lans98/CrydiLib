cmake_minimum_required(VERSION 3.6)
project(crydi3) 

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release) 
set(CMAKE_CXX_FLAGS "-O3")

file(GLOB SOURCES "src/*.cc")
file(GLOB HEADERS "src/inc/*.h")

find_library(NTLLIB_FOUND ntl) 

if (NTLLIB_FOUND)
	add_library(crydi3 SHARED ${HEADERS} ${SOURCES})
	target_link_libraries(crydi3 ntl)

	add_executable(gen_primes primes/gen_primes.cc)
	target_link_libraries(gen_primes crydi3 ntl)

	add_custom_command(TARGET gen_primes POST_BUILD COMMAND gen_primes)

	if (CRYDI3_TEST)
		enable_testing()

		add_executable(crydi3_tools_bin test/tools_test.cc)
		target_link_libraries(crydi3_tools_bin crydi3 ntl)
		add_test(crydi3_tools_test crydi3_tools_bin)

		add_executable(crydi3_keylist_bin test/keylist_test.cc)
		target_link_libraries(crydi3_keylist_bin crydi3 ntl)
		add_test(crydi3_keylist_test crydi3_keylist_bin)

		add_executable(crydi3_cesar_crypto_bin test/cesar_crypto_test.cc)
		target_link_libraries(crydi3_cesar_crypto_bin crydi3 ntl)
		add_test(crydi3_cesar_crypto_test crydi3_cesar_crypto_bin)
		
		add_executable(crydi3_afin_crypto_bin test/afin_crypto_test.cc)
		target_link_libraries(crydi3_afin_crypto_bin crydi3 ntl)
		add_test(crydi3_afin_crypto_test crydi3_afin_crypto_bin)

		add_executable(crydi3_dynamic_int_bin test/dynamic_int_test.cc)
		target_link_libraries(crydi3_dynamic_int_bin crydi3 ntl)
		add_test(crydi3_dynamic_int_test crydi3_dynamic_int_bin)

		add_executable(crydi3_bit_array_bin test/bit_array_test.cc)
		target_link_libraries(crydi3_bit_array_bin crydi3 ntl)
		add_test(crydi3_bit_array_test crydi3_bit_array_bin)

		add_executable(crydi3_primes_sieve_bin test/primes_sieve_test.cc)
		target_link_libraries(crydi3_primes_sieve_bin crydi3 ntl)
		add_test(crydi3_primes_sieve_test crydi3_primes_sieve_bin)

		add_executable(crydi3_div_criteria_bin test/div_criteria_test.cc)
		target_link_libraries(crydi3_div_criteria_bin crydi3 ntl)
		add_test(crydi3_div_criteria_test crydi3_div_criteria_bin)
	endif(CRYDI3_TEST)
endif(NTLLIB_FOUND)

install(TARGETS crydi3 DESTINATION /usr/lib)
install(FILES ${HEADERS} DESTINATION /usr/include/${PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/primes.dat  DESTINATION /usr/share/${PROJECT_NAME})
