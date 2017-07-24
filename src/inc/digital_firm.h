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
  if (firm == "") throw NotFirmFounded();

  string alpha = elgammal.GetAlpha();

  string msg_encrypted  = "";
  string firm_encrypted = "";

  // A is the transmitter
  // Create KeyList with private key as public key, to encrypt
  // firm with it
  KeyList<T> temp_a {
    this->a_keys[RSA_PRI],
    this->a_keys[RSA_PUB],
    this->a_keys[RSA_MOD],
    T(0),
    T(0)
  };

  rsa.SetKeys(temp_a);
  firm_encrypted = rsa.Encrypt(MsgToNumForm(this->firm, alpha));

  // Encrypt original message with ElGammal
  msg_encrypted = elgammal.Encrypt(MsgToNumForm(msg, alpha));

  // B is the receiver
  rsa.SetKeys(this->b_keys);
  msg_encrypted  = rsa.Encrypt(MsgToNumForm(msg_encrypted, alpha));
  firm_encrypted = rsa.Encrypt(MsgToNumForm(firm_encrypted, alpha));

  cout << msg_encrypted << "\n" << firm_encrypted << "\n";

  return msg_encrypted + firm_encrypted;
}

template <class T>
string DigitalFirm<T>::Decrypt(string msg) {
  unsigned long rsa_n_size {
    NumberToString(b_keys[RSA_MOD]).size()
  };

  string alpha = elgammal.GetAlpha();

  string msg_block  = msg.substr(0, msg.size() - rsa_n_size);
  string firm_block = msg.substr(msg.size() - rsa_n_size);

  cout << msg_block << "\n" << firm_block << "\n";

  // B is the receiver
  rsa.SetKeys(this->b_keys);

  msg_block  = rsa.Decrypt(msg_block);
  firm_block = rsa.Decrypt(firm_block);

  // Now decrypt message with elgammal
  msg_block  = elgammal.Decrypt(NumFormToMsg(msg_block, alpha));

  // A is the transmitter
  KeyList<T> temp_a {
    this->a_keys[RSA_PRI],
    this->a_keys[RSA_PUB],
    this->a_keys[RSA_MOD],
    T(0),
    T(0)
  };

  rsa.SetKeys(temp_a);

  firm_block = rsa.Decrypt(NumFormToMsg(firm_block, alpha));

  msg_block  = NumFormToMsg(msg_block, alpha);
  firm_block = NumFormToMsg(firm_block, alpha);
  return msg_block + firm_block;
}

}

#endif
