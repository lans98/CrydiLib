# Install script for directory: /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/lib/libcrydi3.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/libcrydi3.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/lib/libcrydi3.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/libcrydi3.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/lib" TYPE SHARED_LIBRARY FILES "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/build/libcrydi3.so")
  if(EXISTS "$ENV{DESTDIR}/usr/lib/libcrydi3.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/libcrydi3.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/lib/libcrydi3.so")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/include/crydi3/afin_crypto.h;/usr/include/crydi3/afin_crypto_def.h;/usr/include/crydi3/bit_array.h;/usr/include/crydi3/bit_array_def.h;/usr/include/crydi3/cesar_crypto.h;/usr/include/crydi3/cesar_crypto_def.h;/usr/include/crydi3/crydi3.h;/usr/include/crydi3/crydi3_tools.h;/usr/include/crydi3/crypto.h;/usr/include/crydi3/crypto_def.h;/usr/include/crydi3/div_criteria.h;/usr/include/crydi3/dynamic_int.h;/usr/include/crydi3/elgammal_crypto.h;/usr/include/crydi3/elgammal_crypto_def.h;/usr/include/crydi3/keylist.h;/usr/include/crydi3/keylist_def.h;/usr/include/crydi3/primes_sieve.h;/usr/include/crydi3/rsa_crypto.h;/usr/include/crydi3/rsa_crypto_def.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/include/crydi3" TYPE FILE FILES
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/afin_crypto.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/afin_crypto_def.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/bit_array.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/bit_array_def.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/cesar_crypto.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/cesar_crypto_def.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/crydi3.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/crydi3_tools.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/crypto.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/crypto_def.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/div_criteria.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/dynamic_int.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/elgammal_crypto.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/elgammal_crypto_def.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/keylist.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/keylist_def.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/primes_sieve.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/rsa_crypto.h"
    "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/inc/rsa_crypto_def.h"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/crydi3/primes.dat")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/share/crydi3" TYPE FILE FILES "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/build/primes.dat")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
