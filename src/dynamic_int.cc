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

#include "inc/dynamic_int.h"

namespace crydi {

// =====================================================
//								UInt using just 8 bits
// =====================================================
UInt8::UInt8(const ZZ& num): DynamicInt() {
	ulong num_compat { conv<ulong>(num) };
	value = static_cast<uint8_t>(num_compat);
}

UInt8::UInt8(uint8_t& num): DynamicInt(), value(num) {}

UInt8::UInt8(uint8_t&& num): DynamicInt(), value(num) {}

UInt8::operator ZZ() {
	ulong num_compat { static_cast<ulong>(value) };
	return conv<ZZ>(num_compat);
}

ZZ UInt8::toZZ() {
	return static_cast<ZZ>(*this);
}

// =====================================================
//							UInt using just 16 bits
// =====================================================
UInt16::UInt16(const ZZ& num): DynamicInt() {
	ulong num_compat { conv<ulong>(num) };
	value = static_cast<uint16_t>(num_compat);
}

UInt16::UInt16(uint16_t& num): DynamicInt(), value(num) {}

UInt16::UInt16(uint16_t&& num): DynamicInt(), value(num) {}

UInt16::operator ZZ() {
	ulong num_compat { static_cast<ulong>(value) };
	return conv<ZZ>(num_compat);
}

ZZ UInt16::toZZ() {
	return static_cast<ZZ>(*this);
}

// =====================================================
//							UInt using just 32 bits
// =====================================================
UInt32::UInt32(const ZZ& num): DynamicInt() {
	ulong num_compat { conv<ulong>(num) };
	value = static_cast<uint32_t>(num_compat);
}

UInt32::UInt32(uint32_t& num): DynamicInt(), value(num) {}

UInt32::UInt32(uint32_t&& num): DynamicInt(), value(num) {}

UInt32::operator ZZ() {
	ulong num_compat { static_cast<ulong>(value) };
	return conv<ZZ>(num_compat);
}

ZZ UInt32::toZZ() {
	return static_cast<ZZ>(*this);
}

// =====================================================
//							UInt using just 64 bits
// =====================================================
UInt64::UInt64(const ZZ& num): DynamicInt() {
	ulong num_compat { conv<ulong>(num) };
	value = static_cast<uint64_t>(num_compat);
}

UInt64::UInt64(uint64_t& num): DynamicInt(), value(num) {}

UInt64::UInt64(uint64_t&& num): DynamicInt(), value(num) {}

UInt64::operator ZZ() {
	ulong num_compat { static_cast<ulong>(value) };
	return conv<ZZ>(num_compat);
}

ZZ UInt64::toZZ() {
	return static_cast<ZZ>(*this);
}

// =====================================================
//			 ZZInt for numbers greater than 64 bits
// =====================================================
ZZInt::ZZInt(const ZZ& num): DynamicInt(), value(num) {}

ZZInt::ZZInt(ZZ&& num): DynamicInt(), value(num) {}

ZZInt::operator ZZ() {
	return value;
}

ZZ ZZInt::toZZ() {
	return value;
}

// =====================================================
// Create specialized type for number
// =====================================================
DynamicInt* CreateSpecializedTypeFor(const ZZ& num) {
	uint16_t bits_count = 0;
	ZZ temp_num { num };
	while (num != 0) {
		temp_num >>= 1;
		bits_count += 1;
	} 

	cout << "Number with " << bits_count << " bits.\n";

	if (64 < bits_count) return new ZZInt(num);

	if (bits_count <= 8) return new UInt8(num);	
	if (8 < bits_count && bits_count <= 16) return new UInt16(num);
	if (16 < bits_count && bits_count <= 32) return new UInt32(num);
  return	new UInt64(num);
}

}
