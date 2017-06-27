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

#include "inc/primes_sieve.h"

namespace crydi {

PrimesSieve::PrimesSieve(uintmax_t limit) {
	int sqrt_limit = static_cast<int>(sqrt(limit));
	// Value -1 for char is 11111111
	barray = new BitArray<>(limit + 1, -1);

	cout << "BitArray size: " << barray->Size() << endl;
	for (uintmax_t i = 2; i <= sqrt_limit; ++i) {
		if (!barray->At(i)) continue;
		for (uintmax_t j = i * i; j <= limit; j += i)	{
			barray->Set(j, 0);
		}
	}

	cout << "BitArray size: " << barray->Size() << endl;
	for (uintmax_t i = 2; i <= limit; ++i) {
		if (!barray->At(i)) continue;
		cout << i << endl;
	}
}

}
