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

#ifndef CRYDI3_BIT_ARRAY_H 
#define CRYDI3_BIT_ARRAY_H 

#include "bit_array_def.h"

namespace crydi {

template <class T>
BitArray<T>::BitArray(BitArray<T>&& barr) {
	bits = barr.bits;
	wasted = barr.wasted;
}

template <class T>
BitArray<T>::BitArray(const size_t& size) {
	bits = vector<T>(ceil(size/(double)container_size));
	wasted = container_size - (size % container_size);
}

template <class T>
BitArray<T>::BitArray(const size_t& size, T fill_with) {
	bits = vector<T>(ceil(size/(double)container_size), fill_with);
	wasted = container_size - (size % container_size);
}

template <class T>
void BitArray<T>::operator=(BitArray<T>&& barr) {
	bits = barr.bits;
	wasted = barr.wasted;
}

template <class T>
bool BitArray<T>::operator[](const size_t& index) {
	size_t container_index { index / container_size };
	size_t bit_position { index % container_size };

	T container = bits[container_index];
	container >>= container_size - bit_position - 1;
	return (container & 1);
}

template <class T>
bool BitArray<T>::At(const size_t& index) {
	return (*this)[index];
}

template <class T>
void BitArray<T>::Set(const size_t& index, T state) {
	if (state > 2) return;
	size_t container_index { index / container_size };
	size_t bit_position { index % container_size };

	T &container = bits[container_index];
	if (state & 1) {
		container |= (state << container_size - bit_position - 1);
	} else {
		state |= 1;
		container &= ~(state << container_size - bit_position - 1);
	}
}

template <class T>
void BitArray<T>::Fill(T state) {
	fill(bits.begin(), bits.end(), state);
}

template <class T>
size_t BitArray<T>::Size() {
  return bits.size() * container_size - wasted;
}

}

#endif 
