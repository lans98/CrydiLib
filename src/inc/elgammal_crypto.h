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
  ZZ d { GenRandomZZ(num_bits - 1) };
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
T ElGammalCrypto<T>::GetFirstPublicKey() { return this->keys[EG_PUB_1]; }

template <class T>
T ElGammalCrypto<T>::GetSecondPublicKey() { return this->keys[EG_PUB_2]; }

template <class T>
T ElGammalCrypto<T>::GetPrivateKey() { return this->keys[EG_PRI]; }

template <class T>
T ElGammalCrypto<T>::GetModulus() { return this->keys[EG_MOD]; }

template <class T>
string ElGammalCrypto<T>::Encrypt(string msg) {
  unsigned long n_size {
    NumberToString(this->keys[EG_MOD]).size()
  };

  // Choose a random 'r' to encrypt 'c'
  ZZ r;
  do {
    r = GenRandomZZ(this->keys[EG_MOD].size() * 64);
    r = Mod(r, this->keys[EG_MOD] - 2);
    this->keys[EG_MOD];
  } while (r <= ZZ(2));

  // Encrypt 'c' later used on decrypt method
  this->c = ModularExp(this->keys[EG_PUB_1], r, this->keys[EG_MOD]);

  // Cipher_ref used on encrypt
  T cipher_ref {
    ModularExp(this->keys[EG_PUB_2], r, this->keys[EG_MOD])
  };

  // Variables to use temporal blocks
  T      block_int;
  string block_str;

  // Final encrypted message
  string encrypted = "";

  // Less important character is space = ' '
  // Add as many ' ' as necessary to the end of message
  // until msg.size() is divided by n_size - 1 (needed for
  // n - 1 sized exact blocks)
  string space_str = GetIdFor(' ', this->alpha);
  while (Mod(msg.size(), n_size - 1) != 0)
    msg += space_str;

  // Start encrypting message
  for (unsigned long i = 0; i < msg.size(); i += n_size - 1) {
    block_int = StringToNumber<T>(msg.substr(i, n_size - 1));
    block_int = Mod(block_int * cipher_ref, this->keys[EG_MOD]);
    block_str = NumberToString<T>(block_int);

    // If the size of encrypted block is less that n_size
    // add as many '0' as needed to the start of the block
    if (block_str.size() < n_size)
      block_str = string(n_size - block_str.size(), '0') + block_str;

    // Add the new encrypted block to the final encrypted message
    encrypted += block_str;
  }
  return encrypted;
}

template <class T>
string ElGammalCrypto<T>::Decrypt(string msg) {
  unsigned long n_size {
    NumberToString(this->keys[EG_MOD]).size()
  };

  // Compute modular exponentiation of c with
  // private key of elgammal
  T inv_c = ModularExp(this->c, this->keys[EG_PRI], this->keys[EG_MOD]);

  // Then find modular inverse of the above number
  inv_c = FindModularInverse(inv_c, this->keys[EG_MOD]);

  // Variables to use the temporal blocks
  T      block_int;
  string block_str;

  // Final decrypted message
  string decrypted = "";

  // Start decrypting message
  for (unsigned long i = 0; i < msg.size(); i += n_size) {
    block_int = StringToNumber<T>(msg.substr(i, n_size));
    block_int = Mod(inv_c * block_int, this->keys[EG_MOD]);
    block_str = NumberToString<T>(block_int);

    // If the size of the decrypted block is less than n_size - 1
    // add as many '0' as needed to the start of the block
    if (block_str.size() < n_size - 1)
      block_str = string(n_size - 1 - block_str.size(), '0') + block_str;

    // Add the new decrypted block to the final decrypted message
    decrypted += block_str;
  }
  return CleanNumForm(' ', decrypted, this->alpha);
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
