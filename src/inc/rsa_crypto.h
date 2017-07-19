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

#ifndef CRYDI3_RSA_CRYPTO_H
#define CRYDI3_RSA_CRYPTO_H

#include "rsa_crypto_def.h"

namespace crydi {

KeyList<ZZ> GenRSAKeys(long num_bits) {
  ZZ p = GenRandomZZPrime(num_bits >> 1);
  ZZ q = GenRandomZZPrime(num_bits >> 1);
  while (p == q)
    q = GenRandomZZPrime(num_bits >> 1);
  ZZ modulus = p * q;
  ZZ phi_mod = (p - 1) * (q - 1);

  ZZ public_key, private_key;
  do {
    public_key = GenRandomZZ(num_bits - 1);
    public_key = Mod(public_key, phi_mod);
  } while (
    (public_key >= phi_mod) ||
    (Gcd(phi_mod, public_key) != 1)
  );

  private_key = FindModularInverse(public_key, phi_mod);
  KeyList<ZZ> keys {public_key, private_key, modulus, p, q};
  return keys;
}

template <class T>
RSACrypto<T>::RSACrypto(): Crypto<T>() {}

template <class T>
RSACrypto<T>::RSACrypto(const KeyList<T> &keys): Crypto<T>(keys) {
  try {
    this->p = Crypto<T>::keys_[RSA_MOD_P];
  } catch (OutOfRange e) {
    this->p = T(0);
  }
  try {
    this->q = Crypto<T>::keys_[RSA_MOD_Q];
  } catch (OutOfRange e) {
    this->q = T(0);
  }
  Crypto<T>::keys_ = Crypto<T>::keys_.Sub(3);
}

template <class T>
RSACrypto<T>::RSACrypto(const string &alpha): Crypto<T>(alpha) {}

template <class T>
RSACrypto<T>::RSACrypto(const string &alpha, const KeyList<T> &keys):
  Crypto<T>(alpha, keys) {
    try {
      this->p = Crypto<T>::keys_[RSA_MOD_P];
    } catch (OutOfRange e) {
      this->p = T(0);
    }

    try {
      this->q = Crypto<T>::keys_[RSA_MOD_Q];
    } catch (OutOfRange e) {
      this->q = T(0);
    }
    
    Crypto<T>::keys_ = Crypto<T>::keys_.Sub(3);
  }

template <class T>
T RSACrypto<T>::GetPublicKey() {
  return Crypto<T>::keys_[RSA_PUB];
}

template <class T>
T RSACrypto<T>::GetPrivateKey() {
  return Crypto<T>::keys_[RSA_PRI];
}

template <class T>
T RSACrypto<T>::GetModulus() {
  return Crypto<T>::keys_[RSA_MOD];
}

template <class T>
string RSACrypto<T>::MsgToNumericalForm(string msg) {
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
string RSACrypto<T>::NumericalFormToMsg(string msg) {
  string            block_str;
  string::size_type block_int;

  string last = NumberToString(Crypto<T>::alpha_.size() - 1);
  string final_msg = "";
  for (unsigned long i = 0; i < msg.size(); i += last.size()) {
    block_str = msg.substr(i, last.size());
    block_int = StringToNumber<string::size_type>(block_str);
    final_msg += Crypto<T>::alpha_[block_int];
  }
  return final_msg;
}

template <class T>
string RSACrypto<T>::Encrypt(string msg) {
  unsigned long n_size {
    NumberToString(Crypto<T>::keys_[RSA_MOD]).size()
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
  string::size_type space = Crypto<T>::alpha_.find(' ');
  while (Mod(msg.size(), n_size - 1) != 0)
    msg += NumberToString(space);

  // Start encrypting message
  for (unsigned long i = 0; i < msg.size(); i += n_size - 1) {
    block_int = StringToNumber<T>(msg.substr(i, n_size - 1));
    block_int = ModularExp(
      block_int,
      Crypto<T>::keys_[RSA_PUB],
      Crypto<T>::keys_[RSA_MOD]
    );
    block_str = NumberToString<T>(block_int);

    // If the size of encrypted block is less than n_size
    // add as many '0' as needed to the start of the block
    if (block_str.size() < n_size)
      block_str = string(n_size - block_str.size(), '0') + block_str;

    // Add the new encrypted block to the final encrypted message
    encrypted += block_str;
  }
  return encrypted;
}

template <class T>
string RSACrypto<T>::Decrypt(string msg) {
  unsigned long n_size {
    NumberToString(Crypto<T>::keys_[RSA_MOD]).size()
  };

  // Variables to use temporal blocks
  T      block_int;
  string block_str;

  // Used in CRT
  T a[2] { T(), T() };
  T m[2] { this->p, this->q };

  // Final decrypted message
  string decrypted = "";

  // Start decrypting message
  for (unsigned long i = 0; i < msg.size(); i += n_size) {
    block_int = StringToNumber<T>(msg.substr(i, n_size));

    if (!(this->p && this->q)) {
      block_int = ModularExp(
        block_int,
        Crypto<T>::keys_[RSA_PRI],
        Crypto<T>::keys_[RSA_MOD]
      );
    } else {
      // Prepare both 'a' for CRT
      a[0] = ModularExp(
        Mod(block_int, p),
        Mod(Crypto<T>::keys_[RSA_PRI], this->p - 1),
        this->p
      );

      a[1] = ModularExp(
        Mod(block_int, q),
        Mod(Crypto<T>::keys_[RSA_PRI], this->q - 1),
        this->q
      );

      // Decrypt with CRT
      block_int = CRT(a, m, 2);
    }
    block_str = NumberToString<T>(block_int);

    // If the size of the decrypted block is less than n_size - 1
    // add as many '0' as needed to the start of the block
    if (block_str.size() < n_size - 1)
      block_str = string(n_size - 1 - block_str.size(), '0') + block_str;

    // Add the new decrypted block to the final decrypted message
    decrypted += block_str;
  }
  return decrypted;
}

}

#endif
