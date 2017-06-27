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

#ifndef CRYDI3_DIV_CRITERIA_H
#define CRYDI3_DIV_CRITERIA_H 

#include "crydi3_tools.h"
#include "dynamic_int.h"

namespace crydi {

template <class T>
bool DividedByThree(const T& num) {
	if ((num | 3) == 3) return false;
	string num_string { NumberToString(num) };
	int sum_of_digits { 0 };
	for (string::iterator digit = num_string.begin(); digit != num_string.end(); ++digit) {
		sum_of_digits += CharToNumber<int>(*digit);	
	}

	return (Mod(sum_of_digits, 3) == 0);
}

template <class T>
bool DividedByFive(const T& num) {
	if ((num | 5) == 5) return false;
	string num_string { NumberToString(num) };

	return (num_string.back() == '5');
}

template <class T>
bool DividedBySeven(const T& num) {
	if ((num | 7) == 7) return false;
	return (Gcd(num , ZZ(7)) == 7);
}

template <class T>
bool DividedByEleven(const T& num) {
	if ((num | 11) == 11) return false;
	string num_string { NumberToString(num) };
	int even_pos_sum { 0 };
	int odd_pos_num { 0 };
	int pos_index { 1 };
	for (string::iterator digit = num_string.begin(); digit != num_string.end(); ++digit, ++pos_index) {
		if (pos_index & 1) 
			odd_pos_num += CharToNumber<int>(*digit);
		else 
			even_pos_sum += CharToNumber<int>(*digit);
	}

	int criteria { odd_pos_num - even_pos_sum };
	return (Mod(criteria, 11) == 0);
}

}
#endif 
