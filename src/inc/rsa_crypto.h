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
  this->p = Crypto<T>::keys_[P_R];
  this->q = Crypto<T>::keys_[Q_R];
  Crypto<T>::keys_ = Crypto<T>::keys_.Sub(3);
}

template <class T>
RSACrypto<T>::RSACrypto(const string &alpha): Crypto<T>(alpha) {}

template <class T>
RSACrypto<T>::RSACrypto(const string &alpha, const KeyList<T> &keys):
  Crypto<T>(alpha, keys) {
    this->p = Crypto<T>::keys_[P_R];
    this->q = Crypto<T>::keys_[Q_R];
    Crypto<T>::keys_ = Crypto<T>::keys_.Sub(3);
  }

template <class T>
T RSACrypto<T>::GetPublicKey() {
  return Crypto<T>::keys_[PUBLIC_R];
}

template <class T>
T RSACrypto<T>::GetPrivateKey() {
  return Crypto<T>::keys_[PRIVATE_R];
}

template <class T>
T RSACrypto<T>::GetModulus() {
  return Crypto<T>::keys_[MODULUS_R];
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
string RSACrypto<T>::Encrypt(string msg) {
  string encrypted = "";
  unsigned long modulus_size {
    NumberToString(Crypto<T>::keys_[MODULUS_R]).size()
  };
  T encrypted_block_i;
  string encrypted_block_s;
  for (unsigned long i = 0; i < msg.size(); i += modulus_size - 1) {
    encrypted_block_i = StringToNumber<T>(msg.substr(i, modulus_size - 1));
    encrypted_block_i = ModularExp(
      encrypted_block_i,
      Crypto<T>::keys_[PUBLIC_R],
      Crypto<T>::keys_[MODULUS_R]
    );
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
string RSACrypto<T>::Decrypt(string msg) {
  string decrypted = "";
  unsigned long modulus_size {
    NumberToString(Crypto<T>::keys_[MODULUS_R]).size()
  };
  T decrypted_block_i;
  string decrypted_block_s;
  T a[2] { T(), T() };
  T m[2] { this->p, this->q };
  for (unsigned long i = 0; i < msg.size(); i += modulus_size) {
    decrypted_block_i = StringToNumber<T>(msg.substr(i, modulus_size));

    // Deprecated in order to use CRT
    //decrypted_block_i = ModularExp(
    //  decrypted_block_i,
    //  Crypto<T>::keys_[PRIVATE_R],
    //  Crypto<T>::keys_[MODULUS_R]
    //);
    //

    a[0] = ModularExp(
      Mod(decrypted_block_i, p),
      Mod(Crypto<T>::keys_[PRIVATE_R], this->p - 1),
      this->p
    );
    a[1] = ModularExp(
      Mod(decrypted_block_i, q),
      Mod(Crypto<T>::keys_[PRIVATE_R], this->q - 1),
      this->q
    );
    decrypted_block_i = CRT(a, m, 2);
    decrypted_block_s = NumberToString<T>(decrypted_block_i);
    if (decrypted_block_s.size() < modulus_size - 1) {
      decrypted_block_s = string(modulus_size - 1 - decrypted_block_s.size(), '0')
                          + decrypted_block_s;
    }
    decrypted += decrypted_block_s;
  }
  return decrypted;
}

}

#endif
