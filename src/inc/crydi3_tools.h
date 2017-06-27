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
#include <random>
#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <initializer_list>

namespace crydi {

// Defined macro by ntl lib 
NTL_CLIENT

enum gcd_flag {
	EUCLID_GCD = 0x01,
	STEIN_GCD  = 0x02
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

/**
 * Compute the gcd of a and b, using Euclid's Algorithm
 * @param a
 * @param b
 * @return gcd
 */
int EuclidGcd(int a, int b);
ZZ  EuclidGcd(ZZ  a, ZZ  b);

/**
 * Compute the gcd of a and b, using Stein's Algorithm
 * Well-know as Binary gcd
 * @param a
 * @param b
 * @return gcd
 */
int SteinGcd(int a, int b);
ZZ  SteinGcd(ZZ  a, ZZ  b);

/**
 * Wrapper for gcd algoritthms, calculate gcd of a and b, by
 * default it uses Stein's Gcd (see gcd_flag) 
 * @param a
 * @param b
 * @param algorithm
 * @return gcd
 */
int Gcd(int a, int b, gcd_flag algorithm = STEIN_GCD);
ZZ  Gcd(ZZ  a, ZZ  b, gcd_flag algorithm = STEIN_GCD);

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
void EuclidExtendedGcd(ZZ  a, ZZ  b, ZZ  &mcd, ZZ  &x, ZZ  &y);

/**
 * Compute the modular multiplicative inverse for a in modulus b, used 
 * on Afin Cipher, RSA, this can be only calculated if gcd(a,b) = 1
 * @param a
 * @param b
 * @return modular multiplicative inverse
 */
int FindModularInverse(int a, int b);
ZZ  FindModularInverse(ZZ  a, ZZ  b);

/**
 * Generate a random int between a and b
 * @param a
 * @param b
 * @return random number
 */ 
int RandomInt(int a, int b);

/**
 * Calculate the result from (base ** exp) % mod
 * @param base
 * @param exp
 * @param mod
 * @return modular exponentiation
 */
int ModularExp(int base, int exp, int mod);
ZZ  ModularExp(ZZ  base, ZZ  exp, ZZ  mod);

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

/**
 * Find the first n-primes and save them on a file
 * @param n delimiter
 */
void FirstNPrimes(int n);
void FirstNPrimes(ZZ  n);

/**
 * Primality test using square root method and testing just with 
 * the first sqrt(n)-primes
 */
bool IsPrime(int number);
bool IsPrime(ZZ  number);

}

#endif 
