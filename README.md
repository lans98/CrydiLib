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
    $ ctest
    $ sudo make install

You can put ``-DCRYDI3_TEST=OFF`` and then avoid ``ctest`` command, this is just
to be sure that the library is working fine.

## Using it
Library it self is called ``libcrydi3.so``, for linking with g++ use

    $ g++ -lcrydi3 ...

## Examples
You can see some examples at ``test`` folder.
<<<<<<< HEAD

## Development branch
You can switch to development branch easily to test new features

    $ cd CrydiLib
    $ git checkout develop

After that do the same to compile library
=======
>>>>>>> develop
