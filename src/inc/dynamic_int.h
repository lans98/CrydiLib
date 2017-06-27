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

#ifndef CRYDI3_DYNAMIC_INT_H
#define CRYDI3_DYNAMIC_INT_H 

#include "crydi3_tools.h"

namespace crydi {

class DynamicInt {
 public:
	DynamicInt() = default;
	virtual ~DynamicInt() = default;
	virtual operator ZZ() = 0;
	virtual ZZ toZZ() = 0;
};

class UInt8 : public DynamicInt {
 public:
	uint8_t value;

	UInt8() = default;
	UInt8(const ZZ& num);
	UInt8(uint8_t& num);
	UInt8(uint8_t&& num);

	operator ZZ() override;
	ZZ toZZ() override;
};

class UInt16 : public DynamicInt {
 public:
	uint16_t value;

  UInt16() = default;
	UInt16(const ZZ& num);
	UInt16(uint16_t& num);
	UInt16(uint16_t&& num);

	operator ZZ() override;
	ZZ toZZ() override;
};

class UInt32 : public DynamicInt {
 public:
	uint32_t value;

	UInt32() = default;
	UInt32(const ZZ& num);
	UInt32(uint32_t& num);
	UInt32(uint32_t&& num);

	operator ZZ() override;
	ZZ toZZ() override;
};

class UInt64 : public DynamicInt {
 public:
  uint64_t value;

	UInt64() = default;
	UInt64(const ZZ& num);
	UInt64(uint64_t& num);
	UInt64(uint64_t&& num);

	operator ZZ() override;
	ZZ toZZ() override;
};

class ZZInt : public DynamicInt {
 public: 
	ZZ value;

	ZZInt() = default;
	ZZInt(const ZZ& num);
	ZZInt(ZZ&& num);

	operator ZZ() override;
	ZZ toZZ() override;
};

DynamicInt* CreateSpecializedTypeFor(const ZZ& num);

}

#endif
