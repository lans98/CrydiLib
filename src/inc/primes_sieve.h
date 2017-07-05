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

#ifndef CRYDI3_PRIME_SIEVE_H
#define CRYDI3_PRIME_SIEVE_H 

#include "crydi3_tools.h"
#include "bit_array.h"

namespace crydi {

using ps_flag = uint8_t;

const ps_flag PRINT_IT  = 0x01;
const ps_flag REG_SIEVE = 0x02;
const ps_flag SEG_SIEVE = 0x04;

enum seg_sieve {
	PRIMES = 0,
	SEGMENT = 1
};

class PrimesSieve {
 private:
	BitArray<> *barray;
	uintmax_t   limit;
	ps_flag			flags = 0;

 public:
	PrimesSieve() = default;
	PrimesSieve(uintmax_t limit, bool printit = true); 

	void RegularSieve();
	void SegmentedSieve();
};

}

#endif 
