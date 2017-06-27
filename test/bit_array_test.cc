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

NTL_CLIENT

#undef NDEBUG

int main() {
#ifndef NDEBUG 
	printf("Debugging mode!\n");
#else 
	printf("Normal mode!\n");
#endif
	
	crydi::BitArray<> arr(20, 0);
	cout << "Created BitArray: \n"
		   << "-> Actual size: " << arr.Size() << endl;

	arr.Set(10, 1);
	arr.Set(12, 1);
	arr.Set(14, 1);

	for (size_t i = 0; i < arr.Size(); ++i) {
		cout << arr[i] << " ";
	} cout << "\n";

	for (size_t i = 0; i < arr.Size(); ++i) {
		if (!arr[i]) continue;
		cout << i << " ";
	} cout << "\n";

	crydi::BitArray<> arr2(25, -1);
	cout << "Created BitArray: \n"
		   << "-> Actual size: " << arr2.Size() << endl;

	arr2.Set(0, 0);
	arr2.Set(4, 0);
	arr2.Set(7, 0);

	for (size_t i = 0; i < arr2.Size(); ++i) {
		cout << arr2[i] << " ";
	} cout << "\n";

	for (size_t i = 0; i < arr2.Size(); ++i) {
		if (!arr2[i]) continue;
		cout << i << " ";
	} cout << "\n";

	return 0;
}
