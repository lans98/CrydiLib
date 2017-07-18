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

#ifndef CRYDI3_ELGAMMAL_DEF_H
#define CRYDI3_ELGAMMAL_DEF_H

#include "crydi3_tools.h"
#include "crypto.h"

namespace crydi {

enum ElGammalIdentifier {
  PUBLIC_1_E = 0,
  PUBLIC_2_E = 1,
  PRIVATE_E  = 2,
  MODULUS_E  = 3
};

KeyList<ZZ> GenElgammalKeys(long num_bits);

template <class T>
class ElGammalCrypto : public Crypto<T> {
private:
  T c;
public:
  string MsgToNumericalForm(string msg);

  ElGammalCrypto();
  ElGammalCrypto(const KeyList<T>& keys);
  ElGammalCrypto(const string& alpha);
  ElGammalCrypto(const string& alpha, const KeyList<T>& keys);
  ~ElGammalCrypto() = default;

  T GetFirstPublicKey();
  T GetSecondPublicKey();
  T GetModulus();

  string Encrypt(string msg);
  string Decrypt(string msg);
};

}

#endif
