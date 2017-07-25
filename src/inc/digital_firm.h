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
  rsa_a_keys(rsa_keys_a),
  rsa_b_keys(rsa_keys_b),
  elg_keys(elgammal_keys) {}

template <class T>
DigitalFirm<T>::DigitalFirm(const KeyList<T>& rsa_keys_a, const KeyList<T>& rsa_keys_b, const KeyList<T>& elgammal_keys, const string& firm):
  rsa_a_keys(rsa_keys_a),
  rsa_b_keys(rsa_keys_b),
  elg_keys(elgammal_keys),
  firm(firm) {}

template <class T>
DigitalFirm<T>::DigitalFirm(const string& alpha):
  alpha(alpha) {}

template <class T>
DigitalFirm<T>::DigitalFirm(const string& alpha, const string& firm):
  alpha(alpha),
  firm(firm) {}

template <class T>
DigitalFirm<T>::DigitalFirm(const string& alpha, const KeyList<T>& rsa_keys_a, const KeyList<T>& rsa_keys_b, const KeyList<T>& elgammal_keys):
  rsa_a_keys(rsa_keys_a),
  rsa_b_keys(rsa_keys_b),
  elg_keys(elgammal_keys),
  alpha(alpha) {}

template <class T>
DigitalFirm<T>::DigitalFirm(const string& alpha, const KeyList<T>& rsa_keys_a, const KeyList<T>& rsa_keys_b, const KeyList<T>& elgammal_keys, const string& firm):
  rsa_a_keys(rsa_keys_a),
  rsa_b_keys(rsa_keys_b),
  elg_keys(elgammal_keys),
  alpha(alpha),
  firm(firm) {}

template <class T>
string DigitalFirm<T>::GetFirm() { return this->firm; }

template <class T>
void DigitalFirm<T>::SetFirm(const string& firm) { this->firm = firm; }

template <class T>
void DigitalFirm<T>::SetReceiverKeys(const KeyList<T>& keys) { this->rsa_b_keys = keys; }

template <class T>
KeyList<T> DigitalFirm<T>::GetReceiverKeys() { return this->rsa_b_keys; }

template <class T>
void DigitalFirm<T>::SetTransmitterKeys(const KeyList<T>& keys) { this->rsa_a_keys = keys; }

template <class T>
KeyList<T> DigitalFirm<T>::GetTransmitterKeys() { return this->rsa_a_keys; }

template <class T>
T DigitalFirm<T>::GetElGammalC() { return this->elg_c; }

template <class T>
void DigitalFirm<T>::SetElGammalC(T c) { this->elg_c = c; }

template <class T>
string DigitalFirm<T>::Encrypt(string msg) {
  if (firm == "") throw NotFirmFounded();

  // Swap private and public keys for
  // transmitter
  KeyList<T> temp_a_keys {
    this->rsa_a_keys[RSA_PRI],
    this->rsa_a_keys[RSA_PUB],
    this->rsa_a_keys[RSA_MOD],
    this->rsa_a_keys[RSA_MOD_P],
    this->rsa_a_keys[RSA_MOD_Q]
  };

  // A is the transmitter
  // B is the receiver
  RSACrypto<T>      rsa_a(this->alpha, temp_a_keys);
  RSACrypto<T>      rsa_b(this->alpha, this->rsa_b_keys);
  ElGammalCrypto<T> elgml(this->alpha, this->elg_keys);

  string msg_block = "";
  string frm_block = "";

  // Encrypt message
  msg_block = elgml.Encrypt(MsgToNumForm(msg, this->alpha));
  msg_block = rsa_b.Encrypt(MsgToNumForm(msg_block, this->alpha));

  // Encrypt firm
  frm_block = rsa_a.Encrypt(MsgToNumForm(this->firm, this->alpha));
  frm_block = rsa_b.Encrypt(MsgToNumForm(frm_block, this->alpha));

  this->elg_c = elgml.GetEncryptedC();

  return msg_block + " " + frm_block;
}

template <class T>
string DigitalFirm<T>::Decrypt(string msg) {
  // Swap private and public keys for
  // transmitter
  KeyList<T> temp_a_keys {
    this->rsa_a_keys[RSA_PRI],
    this->rsa_a_keys[RSA_PUB],
    this->rsa_a_keys[RSA_MOD],
    this->rsa_a_keys[RSA_MOD_P],
    this->rsa_a_keys[RSA_MOD_Q]
  };

  // A is the transmitter
  // B is the receiver
  RSACrypto<T>      rsa_a(this->alpha, temp_a_keys);
  RSACrypto<T>      rsa_b(this->alpha, this->rsa_b_keys);
  ElGammalCrypto<T> elgml(this->alpha, this->elg_keys);

  elgml.SetEncryptedC(this->elg_c);

  ssize_t separator = msg.find(' ');

  string msg_block = msg.substr(0, separator);
  string frm_block = msg.substr(separator +1);

  // Decrypt message
  msg_block = rsa_b.Decrypt(msg_block);
  msg_block = NumFormToMsg(msg_block, this->alpha);
  msg_block = elgml.Decrypt(msg_block);
  msg_block = NumFormToMsg(msg_block, this->alpha);

  // Decrypt firm
  frm_block = rsa_b.Decrypt(frm_block);
  frm_block = NumFormToMsg(frm_block, this->alpha);
  frm_block = rsa_a.Decrypt(frm_block);
  frm_block = NumFormToMsg(frm_block, this->alpha);

  return msg_block + ", " + frm_block;
}

}

#endif
