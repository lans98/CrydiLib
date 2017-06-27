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

#ifndef CRYDI3_AFIN_CRYPTO_H
#define CRYDI3_AFIN_CRYPTO_H 

#include "afin_crypto_def.h"

namespace crydi {

template <class T>
AfinCrypto<T>::AfinCrypto(): Crypto<T>() {}

template <class T>
AfinCrypto<T>::AfinCrypto(const KeyList<T> &keys): Crypto<T>(keys) {}

template <class T>
AfinCrypto<T>::AfinCrypto(const string &alpha): Crypto<T>(alpha) {}

template <class T>
AfinCrypto<T>::AfinCrypto(const string &alpha, const KeyList<T> &keys): Crypto<T>(alpha, keys) {}

template <class T>
string AfinCrypto<T>::Encrypt(string msg) {
	long alpha_size = Crypto<T>::alpha_.size();
	for (string::iterator ch = msg.begin(); ch != msg.end(); ++ch) {
		string::size_type i = Crypto<T>::alpha_.find(*ch);

		if (i == string::npos)
			return "";

		long index = static_cast<long>(i);

		T new_pos {
			Mod(Crypto<T>::keys_[0] * conv<T>(index) + Crypto<T>::keys_[1], conv<T>(alpha_size))
		};
		long new_pos_compat  = conv<long>(new_pos);
		*ch = Crypto<T>::alpha_[new_pos_compat];
	}
	return msg;
}

template <class T>
string AfinCrypto<T>::Decrypt(string msg) {
	long alpha_size = Crypto<T>::alpha_.size();
	T inv_key { FindModularInverse(Crypto<T>::keys_[0], conv<T>(alpha_size)) };
	cout << inv_key << endl;
	for (string::iterator ch = msg.begin(); ch != msg.end(); ++ch) {
		string::size_type i = Crypto<T>::alpha_.find(*ch);

		if (i == string::npos)
			return "";

		long index = static_cast<long>(i);

		T new_pos {
			Mod(inv_key * (conv<T>(index) - Crypto<T>::keys_[1]), conv<T>(alpha_size))
		};
		long new_pos_compat = conv<long>(new_pos);
		*ch = Crypto<T>::alpha_[new_pos_compat];
	}
	return msg;
}

}

#endif
