# CrydiLib

Simple (too much) library for crypto with C++

## Dependencies
- NTL Library

## Tools needed
- CMake

## Compilation
    $ cd CrydiLib
    $ mkdir build
    $ cd build
    $ cmake -G "Unix Makefiles" -DCRYDI3_TEST=ON ..
    $ make

It's suggested that you use ``-DCRYDI3_TEST=ON``, for later testing before installing

## Installation
If you used ``-DCRYDI3_TEST=ON`` is suggested that you use ``ctest`` before
installing library to be sure that it works

    $ ctest
    $ sudo make install

## Using it
Library it self is called ``libcrydi3.so``, for linking with g++ use

    $ g++ -lcrydi3 ...

## Examples
You can see some examples at ``test`` folder.
