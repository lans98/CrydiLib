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

#ifndef CRYDI3_DIGITAL_SIGN_H
#define CRYDI3_DIGITAL_SIGN_H

#include "digital_firm_def.h"

namespace crydi {

template <class T>
DigitalFirm<T>::DigitalFirm(const KeyList<T>& rsa_keys_a, const KeyList<T>& rsa_keys_b, const KeyList<T>& elgammal_keys):
  rsa(rsa_keys_a),
  elgammal(elgammal_keys),
  a_keys(rsa_keys_a),
  b_keys(rsa_keys_b) {}

template <class T>
DigitalFirm<T>::DigitalFirm(const KeyList<T>& rsa_keys_a, const KeyList<T>& rsa_keys_b, const KeyList<T>& elgammal_keys, const string& firm):
  rsa(rsa_keys_a),
  elgammal(elgammal_keys),
  a_keys(rsa_keys_a),
  b_keys(rsa_keys_b),
  firm(firm) {}

template <class T>
DigitalFirm<T>::DigitalFirm(const string& alpha):
  rsa(alpha),
  elgammal(alpha) {}

template <class T>
DigitalFirm<T>::DigitalFirm(const string& alpha, const string& firm):
  rsa(alpha),
  elgammal(alpha),
  firm(firm) {}

template <class T>
DigitalFirm<T>::DigitalFirm(const string& alpha, const KeyList<T>& rsa_keys_a, const KeyList<T>& rsa_keys_b, const KeyList<T>& elgammal_keys):
  rsa(alpha, rsa_keys_a),
  elgammal(alpha, elgammal_keys),
  a_keys(rsa_keys_a),
  b_keys(rsa_keys_b) {}

template <class T>
DigitalFirm<T>::DigitalFirm(const string& alpha, const KeyList<T>& rsa_keys_a, const KeyList<T>& rsa_keys_b, const KeyList<T>& elgammal_keys, const string& firm):
  rsa(alpha, rsa_keys_a),
  elgammal(alpha, elgammal_keys),
  a_keys(rsa_keys_a),
  b_keys(rsa_keys_b),
  firm(firm) {}

template <class T>
string DigitalFirm<T>::GetFirm() { return this->firm; }

template <class T>
void DigitalFirm<T>::SetFirm(const string& firm) { this->firm = firm; }

template <class T>
RSACrypto<T>& DigitalFirm<T>::GetRSACrypto() {
  return this->rsa;
}

template <class T>
ElGammalCrypto<T>& DigitalFirm<T>::GetElGammalCrypto() {
  return this->elgammal;
}

template <class T>
void DigitalFirm<T>::SetReceiverKeys(const KeyList<T>& rsa_keys_b) {
  this->b_keys = rsa_keys_b;
}

template <class T>
KeyList<T> DigitalFirm<T>::GetReceiverKeys() {
  return this->b_keys;
}

template <class T>
string DigitalFirm<T>::Encrypt(string msg) {
  if (firm == "") throw NotSignFounded();

  // Encrypt original message with elgammal
  string msg_encrypted  = elgammal.Encrypt(elgammal.MsgToNumericalForm(msg));

  // A is the transmitter
  rsa.SetKeys(this->a_keys);
  // Treat firm as a RSA encrypted message, so decrypt it with A's keys
  string sign_encrypted = rsa.Decrypt(rsa.MsgToNumericalForm(this->firm));

  // B is the receiver
  rsa.SetKeys(this->b_keys);

  // Now encrypt both msg and firm with RSA and B's keys
  msg_encrypted  = rsa.Encrypt(msg_encrypted);
  sign_encrypted = rsa.Encrypt(sign_encrypted);

  return msg_encrypted + sign_encrypted;
}

template <class T>
string DigitalFirm<T>::Decrypt(string msg) {
  unsigned long rsa_n_size {
    NumberToString(b_keys[RSA_MOD]).size()
  };

  // Separate both with rsa_n_size
  string msg_block  = msg.substr(0, msg.size() - rsa_n_size);
  string sign_block = msg.substr(msg.size() - rsa_n_size);

  // B is the receiver
  rsa.SetKeys(this->b_keys);

  // So decrypt message and firm with RSA and B's keys
  msg_block  = rsa.Decrypt(msg_block);
  sign_block = rsa.Decrypt(sign_block);

  // Now decrypt message with elgammal
  msg_block = elgammal.Decrypt(msg_block);

  // A is the transmitter
  rsa.SetKeys(this->a_keys);

  // Do the inverse process to decrypt (encrypt) with digital firm
  // so encrypt sign_block with RSA and A's keys
  sign_block = rsa.Encrypt(sign_block);

  return msg_block + sign_block;
}

}

#endif
