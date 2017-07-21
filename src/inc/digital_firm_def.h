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

#ifndef CRYDI3_DIGITAL_SIGN_DEF_H
#define CRYDI3_DIGITAL_SIGN_DEF_H

#include "crydi3_tools.h"
#include "strings_tools.h"
#include "crypto.h"
#include "rsa_crypto.h"
#include "elgammal_crypto.h"

namespace crydi {

template <class T>
class DigitalFirm {
private:
  RSACrypto<T>      rsa;
  ElGammalCrypto<T> elgammal;

  KeyList<T>        a_keys;
  KeyList<T>        b_keys;
  string            firm;
public:
  DigitalFirm() = default;
  DigitalFirm(const KeyList<T>& rsa_keys_a, const KeyList<T>& rsa_keys_b, const KeyList<T>& elgammal_keys);
  DigitalFirm(const KeyList<T>& rsa_keys_a, const KeyList<T>& rsa_keys_b, const KeyList<T>& elgammal_keys, const string& firm);
  DigitalFirm(const string& alpha);
  DigitalFirm(const string& alpha, const string& firm);
  DigitalFirm(const string& alpha, const KeyList<T>& rsa_keys_a, const KeyList<T>& rsa_keys_b, const KeyList<T>& elgammal_keys);
  DigitalFirm(const string& alpha, const KeyList<T>& rsa_keys_a, const KeyList<T>& rsa_keys_b, const KeyList<T>& elgammal_keys, const string& firm);
  ~DigitalFirm() = default;

  string GetFirm();
  void   SetFirm(const string& firm);

  RSACrypto<T>&      GetRSACrypto();
  ElGammalCrypto<T>& GetElGammalCrypto();

  void       SetReceiverKeys(const KeyList<T>& rsa_keys_b);
  KeyList<T> GetReceiverKeys();

  string Encrypt(string msg);
  string Decrypt(string msg);
};

}

#endif
