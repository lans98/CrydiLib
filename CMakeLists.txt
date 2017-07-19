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

	if (CRYDI3_TEST)
		enable_testing()

    include_directories(src/inc)

    add_executable(crydi3_random_bin test/random_test.cc)
    target_link_libraries(crydi3_random_bin crydi3 ntl)
    add_test(crydi3_random_test crydi3_random_bin)

    add_executable(crydi3_rsa_bin test/rsa_test.cc)
    target_link_libraries(crydi3_rsa_bin crydi3 ntl)
    add_test(crydi3_rsa_test crydi3_rsa_bin)

    add_executable(crydi3_elgammal_bin test/elgammal_test.cc)
    target_link_libraries(crydi3_elgammal_bin crydi3 ntl)
    add_test(crydi3_elgammal_test crydi3_elgammal_bin)

    #add_executable(crydi3_dig_firm_bin test/digital_firm_test.cc)
    #target_link_libraries(crydi3_dig_firm_bin crydi3 ntl)
    #add_test(crydi3_digital_firm_test crydi3_dig_firm_bin)

    add_executable(crydi3_tools_bin test/tools_test.cc)
    target_link_libraries(crydi3_tools_bin crydi3 ntl)
    add_test(crydi3_tools_test crydi3_tools_bin)
	endif(CRYDI3_TEST)
endif(NTLLIB_FOUND)

install(TARGETS crydi3 DESTINATION /usr/lib)
install(FILES ${HEADERS} DESTINATION /usr/include/${PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/primes.dat  DESTINATION /usr/share/${PROJECT_NAME})
