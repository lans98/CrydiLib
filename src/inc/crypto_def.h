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

#ifndef CRYDI3_CRYPTO_DEF_H
#define CRYDI3_CRYPTO_DEF_H

#include "crydi3_tools.h"
#include "keylist.h"

namespace crydi {

template <class T>
class Crypto {
 protected:
	KeyList<T> keys_;
	string     alpha_;

 public:
	Crypto();
	Crypto(const KeyList<T> &keys);
	Crypto(const string &alpha);
	Crypto(const string &alpha, const KeyList<T>& keys);
	virtual ~Crypto() = default;

	void        SetKeys(const KeyList<T> &keys);
	KeyList<T>  GetKeys();

	virtual void SetAlpha(const string &alpha);

	virtual string Encrypt(string msg) = 0;
	virtual string Decrypt(string msg) = 0;
};

}

#endif
