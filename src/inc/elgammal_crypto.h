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

#ifndef CRYDI3_ELGAMMAL_H
#define CRYDI3_ELGAMMAL_H

#include "elgammal_crypto_def.h"

namespace crydi {

KeyList<ZZ> GenElgammalKeys(long num_bits) {
  ZZ p { GenRandomZZPrime(num_bits) };
  ZZ e { FindGenerator(p) };
  ZZ d { GenRandomZZ(num_bits) };
  d = Mod(d, p);
  KeyList<ZZ> keys {e , ModularExp(e, d, p), d, p };
  return keys;
}

template <class T>
ElGammalCrypto<T>::ElGammalCrypto(): Crypto<T>() {}

template <class T>
ElGammalCrypto<T>::ElGammalCrypto(const KeyList<T>& keys): Crypto<T>(keys) {}

template <class T>
ElGammalCrypto<T>::ElGammalCrypto(const string& alpha): Crypto<T>(alpha) {}

template <class T>
ElGammalCrypto<T>::ElGammalCrypto(const string& alpha, const KeyList<T>& keys): Crypto<T>(alpha, keys) {}

template <class T>
T ElGammalCrypto<T>::GetFirstPublicKey() { return Crypto<T>::keys_[PUBLIC_1_E]; }

template <class T>
T ElGammalCrypto<T>::GetSecondPublicKey() { return Crypto<T>::keys_[PUBLIC_2_E]; }

template <class T>
T ElGammalCrypto<T>::GetModulus() { return Crypto<T>::keys_[MODULUS_E]; }

template <class T>
string ElGammalCrypto<T>::MsgToNumericalForm(string msg) {
  string::size_type identifier_i;
  string identifier_s;
  string last = NumberToString(Crypto<T>::alpha_.size() - 1);
  string numeric_form = "";
  for (string::iterator ch = msg.begin(); ch != msg.end(); ++ch) {
    // Search for the current char identifier on alpha
    // If not founded throw an exception
    identifier_i = Crypto<T>::alpha_.find(*ch);
    if (identifier_i == string::npos)
      throw NotFoundedInAlpha();
    identifier_s = NumberToString(identifier_i);
    // If the actual identifier has less digits than the last one
    // add as many '0' as necessary on the front (ej. 5 -> 05, last = 25)
    if (identifier_s.size() < last.size()) {
      identifier_s = string(last.size() - identifier_s.size(),'0')
                     + identifier_s;
    }
    numeric_form += identifier_s;
  }
  return numeric_form;
}

template <class T>
string ElGammalCrypto<T>::Encrypt(string msg) {
  ZZ r;
  do {
    r = GenRandomZZ(msg.size() - 1);
    r = Mod(r, Crypto<T>::keys_[MODULUS_E]);
  } while (r <= ZZ(1));
  this->c = ModularExp(
    Crypto<T>::keys_[PUBLIC_1_E],
    r,
    Crypto<T>::keys_[MODULUS_E]
  );
  T cipher_ref {
    ModularExp(
      Crypto<T>::keys_[PUBLIC_2_E],
      r,
      Crypto<T>::keys_[MODULUS_E]
    )
  };
  string encrypted = "";
  unsigned long modulus_size {
    NumberToString(Crypto<T>::keys_[MODULUS_E]).size()
  };
  T encrypted_block_i;
  string encrypted_block_s;
  for (unsigned long i = 0; i < msg.size(); i += modulus_size - 1) {
    encrypted_block_i = StringToNumber<T>(msg.substr(i, modulus_size - 1));
    encrypted_block_i = Mod(encrypted_block_i * cipher_ref, Crypto<T>::keys_[MODULUS_E]);
    encrypted_block_s = NumberToString<T>(encrypted_block_i);
    if (encrypted_block_s.size() < modulus_size) {
      encrypted_block_s = string(modulus_size - encrypted_block_s.size(), '0')
                          + encrypted_block_s;
    }
    encrypted += encrypted_block_s;
  }
  return encrypted;
}

template <class T>
string ElGammalCrypto<T>::Decrypt(string msg) {
  T inv_c = ModularExp(
    this->c,
    Crypto<T>::keys_[PRIVATE_E],
    Crypto<T>::keys_[MODULUS_E]
  );
  inv_c = FindModularInverse(inv_c, Crypto<T>::keys_[MODULUS_E]);
  string last = NumberToString(Crypto<T>::alpha_.size() - 1);
  string decrypted = "";
  unsigned long modulus_size {
    NumberToString(Crypto<T>::keys_[MODULUS_E]).size()
  };
  T decrypted_block_i;
  string decrypted_block_s;
  for (unsigned long i = 0; i < msg.size(); i += modulus_size) {
    decrypted_block_i = StringToNumber<T>(msg.substr(i, modulus_size));
    decrypted_block_i = Mod(
      inv_c * decrypted_block_i, Crypto<T>::keys_[MODULUS_E]
    );
    decrypted_block_s = NumberToString<T>(decrypted_block_i);
    if (decrypted_block_s.size() < modulus_size - 1) {
      decrypted_block_s = string(modulus_size - 1 - decrypted_block_s.size(), '0')
                          + decrypted_block_s;
    }
    decrypted += decrypted_block_s;
  }
  return decrypted;
}

template <class T>
T ElGammalCrypto<T>::GetEncryptedC() {
  return this->c;
}

template <class T>
void ElGammalCrypto<T>::SetEncryptedC(const T& c) {
  this->c = c;
}

}

#endif
