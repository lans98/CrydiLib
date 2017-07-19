// =========================================================================
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// =========================================================================

// =========================================================================
// Disclaimer notes:
//  This library is not intended to be a viable option for use in situations
//  of reliability and robustness, several of these algorithms need to be
//  better implemented, this library serves to demonstrate certain algorithms
//  applied to the theory of numbers, also serves as an example as a basis
//  for creating a library (quite simple).
// =========================================================================

#ifndef CRYDI3_CRYDI3_TOOLS_H
#define CRYDI3_CRYDI3_TOOLS_H

#include <NTL/ZZ.h>
#include <ctime>
#include <cstdio>
#include <cstdarg>
#include <cstdint>
#include <cmath>
#include <vector>
#include <deque>
#include <chrono>
#include <random>
#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <exception>
#include <initializer_list>

namespace crydi {

// Namespaces to be used
using namespace std;
using namespace chrono;
using namespace NTL;

class NotFoundedInAlpha : public exception {
public:
  const char* what() const noexcept {
    return "Message contains a char that is not in the alphabet";
  }
};

class NotFirmFounded : public exception {
public:
  const char* what() const noexcept {
    return "This outgoing encrypted message doesn't have firm.";
  }
};

class OutOfRange : public exception {
public:
  const char* what() const noexcept {
    return "KeyList throw access to out ot range!";
  }
};

enum gcd_flag {
	EUCLID_GCD = 0x01,
	STEIN_GCD  = 0x02
};

enum prim_test_flag {
	FERMAT_TEST       = 0x01,
	EULER_TEST        = 0x02,
	MILLER_RABIN_TEST = 0x04
};

/**
 * Compute time for two clock_t define your start clock before calling
 * whatever you want to test and define your end clock after it, then
 * call this function.
 * @param start
 * @param end
 * @return diff time in miliseconds
 */
inline double ComputeTime(clock_t start, clock_t end)
{ return (1000.0 * (end - start) / CLOCKS_PER_SEC); }

/**
 * Compute the modulus of a divided by b
 * @param a
 * @param b
 * @return modulus
 */
template <class T>
inline T Mod(T a, T b)
{ T q {a/b}; return (a - b * ((a < 0)? --q : q)); }

template <>
inline ZZ Mod(ZZ a, ZZ b)
{ ZZ q {a/b}; return (a - b * q); }

/**
 * Compute the gcd of a and b, using Euclid's Algorithm
 * @param a
 * @param b
 * @return gcd
 */
int  EuclidGcd(int a, int b);
long EuclidGcd(long a, long b);
ZZ   EuclidGcd(ZZ  a, ZZ  b);

/**
 * Compute the gcd of a and b, using Stein's Algorithm
 * Well-know as Binary gcd
 * @param a
 * @param b
 * @return gcd
 */
int  SteinGcd(int a, int b);
long SteinGcd(long a, long b);
ZZ   SteinGcd(ZZ  a, ZZ  b);

/**
 * Wrapper for gcd algoritthms, calculate gcd of a and b, by
 * default it uses Stein's Gcd (see gcd_flag)
 * @param a
 * @param b
 * @param algorithm
 * @return gcd
 */
int  Gcd(int a, int b, gcd_flag algorithm = EUCLID_GCD);
long Gcd(long a, long b, gcd_flag algorithm = EUCLID_GCD);
ZZ   Gcd(ZZ  a, ZZ  b, gcd_flag algorithm = EUCLID_GCD);

/**
 * Compute the gcd, and also find two values (x and y) that satisfy
 * Bezout's Identity (using Extended Euclid's Algorithm)
 * @param a
 * @param b
 * @reference mcd
 * @reference x
 * @reference y
 */
void EuclidExtendedGcd(int a, int b, int &mcd, int &x, int &y);
void EuclidExtendedGcd(long a, long b, long &mcd, long &x, long &y);
void EuclidExtendedGcd(ZZ  a, ZZ  b, ZZ  &mcd, ZZ  &x, ZZ  &y);

/**
 * Compute the modular multiplicative inverse for a in modulus b, used
 * on Afin Cipher, RSA, this can be only calculated if gcd(a,b) = 1
 * @param a
 * @param b
 * @return modular multiplicative inverse
 */
int  FindModularInverse(int a, int b);
long FindModularInverse(long a, long b);
ZZ   FindModularInverse(ZZ  a, ZZ  b);

/**
 * Generate a random int between a and b
 * @param a
 * @param b
 * @return random number
 */
int  RandomInt(int a, int b);
long RandomLong(long a, long b);

/**
 * Calculate the result from (base ** exp) % mod
 * @param base
 * @param exp
 * @param mod
 * @return modular exponentiation
 */
int  ModularExp(int base, int exp, int mod);
long ModularExp(long base, long exp, long mod);
ZZ   ModularExp(ZZ  base, ZZ  exp, ZZ  mod);

/**
 * Convert any number (if implemented with stream types) to string
 * @param num
 */
template <class T>
string NumberToString(const T& num) {
	stringstream sstr;
	sstr << num;
	string number_string;
	sstr >> number_string;
	return number_string;
}

/**
 * Convert string (if implemented with stream stypes) to any number type
 * @param num
 */
template <class T>
T StringToNumber(const string& num) {
	stringstream sstr(num);
	T number_type;
	sstr >> number_type;
	return number_type;
}

template <class T>
char NumberToChar(const T& digit) {
	return digit + '0';
}

template <class T>
T CharToNumber(const char digit) {
	return digit - '0';
}

template <class T>
int CountBits(T num) {
  int count = 0;
  while (num != 0) {
    num >>= 1;
    ++count;
  }
  return count;
}

/**
 * Here starts generating numbers and primality tests
 */
static bool __already_init_seed = false;

struct __random__ {
  uintmax_t seed;
  uintmax_t a, c;
};
extern __random__ random;

/**
 * Start "random" seeds, actually it creates an short int and we take
 * its address memory, that may be random
 */
void InitSeeds();

/**
 * Generate Random Long using Linear Congruence, seed is taken from
 * address memory.
 * @param max range to generate (using modulus n)
 */
uintmax_t GenRandomLong(uintmax_t max);

/**
 * Generate Random ZZ using Linear Congruence, seed is taken from
 * address memory, we generate different random longs and then
 * we concatenate them as string, for getting a bigger number.
 * @param num_bits
 */
ZZ GenRandomZZ(int num_bits);

/**
 * Generate a random prime with minimal value
 * And test it with Miller-Rabin with 'k' times
 * @param min, minimal value for generated prime
 * @param k, test k times Miller-Rabin
 */
int  GenRandomIntPrime(int min, uintmax_t k = 25);
long GenRandomLongPrime(long min, uintmax_t k = 25);

/**
 * Generate a random prime with number of bits
 * And test it with Miller-Rabin with 'k' times
 * @param num_bits, number of bits
 * @param k, test k times Miller-Rabin
 */
ZZ	 GenRandomZZPrime(long num_bits, uintmax_t k = 25);

/**
 * Find if a number is prime using Fermat Theorem
 * It will fail with absolute Fermat pseudoprimes
 * @param n odd number to test
 * @param k times to test
 * @return true if n is a probable prime and false if it's composite
 */
bool FermatTest(const int &n, uintmax_t k = 25);
bool FermatTest(const long &n, uintmax_t k = 25);
bool FermatTest(const ZZ &n, uintmax_t k = 25);

/**
 * Find if a number is prime using Euler Theorem
 * It will not fail with absolute Fermat pseudoprimes
 * But it will fail with absolute Euler pseudoprimes
 * @param n odd numer to test
 * @param k times to test
 * @retur true if n is a probable prime and false if it's composite
 */
bool EulerTest(const int &n, uintmax_t k = 25);
bool EulerTest(const long &n, uintmax_t k = 25);
bool EulerTest(const ZZ &n, uintmax_t k = 25);

/**
 * Find if a number is prime using Miller-Rabin Test
 * This theorem also has some pseudoprimes in specific bases 'a'
 * But testing with different bases (10 times) gives real results.
 * @param n odd number to test
 * @param k times to test
 * @return true if n is a probable prime and false if it's composite
 */
bool MillerRabinTest(const int &n, uintmax_t k = 25);
bool MillerRabinTest(const long &n, uintmax_t k = 25);
bool MillerRabinTest(const ZZ &n, uintmax_t k = 25);

/**
 * Find if a number is prime using different methods,
 * by default binded to Miller-Rabin Test
 * @param n odd number to test
 * @return true if n is a probable prime and false if it's composite
 */
bool IsPrime(const int &n, uintmax_t k = 25, prim_test_flag flag = MILLER_RABIN_TEST);
bool IsPrime(const long &n, uintmax_t k = 25, prim_test_flag flag = MILLER_RABIN_TEST);
bool IsPrime(const ZZ  &n, uintmax_t k = 25, prim_test_flag flag = MILLER_RABIN_TEST);

/**
 * Chinese rest theorem for n equations (used in RSA)
 * @param a pointer to list of a_i
 * @param p pointer to list of p_i
 * @param n number of equations (len of list of a_i and p_i)
 */
int CRT(int *a, int *p, int n);
long CRT(long *a, long *p, int n);
ZZ CRT(ZZ *a, ZZ *p, int n);

/**
 * Find a generator for Z*_p (primitive root)
 * This function just works for prime numbers that is secure that
 * at least they have one primitive root.
 * @param prime
 */
ZZ FindGenerator(ZZ prime);

}

#endif
