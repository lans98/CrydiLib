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

#include "../src/inc/crydi3.h"
#include <cassert>

NTL_CLIENT 

#undef NDEBUG 

int main() {
	ZZ divided_by_3  { 1523145343131L };
	ZZ divided_by_5  { 2142142142145L };
	ZZ divided_by_11 { 9859555087283L };

	ZZ number_3 { 3 };
	ZZ number_5 { 5 };
	ZZ number_7 { 7 };
	ZZ number_11 { 11 };

	assert(crydi::DividedByThree(divided_by_3));
	assert(crydi::DividedByFive(divided_by_5));
	assert(crydi::DividedByEleven(divided_by_11));

	assert(!crydi::DividedByThree(number_3));
	assert(!crydi::DividedByThree(number_5));
	assert(!crydi::DividedByThree(number_7));
	assert(!crydi::DividedByThree(number_11));

	return 0;
}
