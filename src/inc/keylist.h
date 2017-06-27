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

#ifndef CRYDI3_KEYLIST_H
#define CRYDI3_KEYLIST_H

#include "keylist_def.h"

namespace crydi {

template <class T>
KeyList<T>::KeyList() : keys_(nullptr), qkeys_(0) {}

template <class T>
KeyList<T>::KeyList(initializer_list<T> list) {
	qkeys_ = list.size();
	keys_  = new T[qkeys_];
	typename initializer_list<T>::iterator it = list.begin();
	for (int i = 0; it != list.end(); ++it, ++i) {
		keys_[i] = *it;	
	}	
}
	
template <class T>
KeyList<T>::KeyList(const KeyList<T>& other) {
	qkeys_ = other.qkeys_;
	keys_  = new T[qkeys_];
	for (size_t i = 0; i < qkeys_; ++i)
		keys_[i] = other.keys_[i];
}


template <class T>
KeyList<T>::~KeyList() { delete[] keys_; }

template <class T>
void KeyList<T>::SetKeys(T key) {
	keys_[index_] = key;
	changing_keys_ = false; 
}

template <class T>
template <typename... Args>
void KeyList<T>::SetKeys(T key, Args... args) {
	if (!changing_keys_) {
		index_ = 0;
		changing_keys_ = true;
	}

	if (index_ > qkeys_) return;
	keys_[index_++] = key;
	SetKeys(args...);
}

template <class T>
void KeyList<T>::ExpandTo(size_t new_size) {
	if (new_size == qkeys_) return;
	T* new_keys = new T[new_size];
	for (size_t i = 0; i < new_size; ++i) 
		new_keys[i] = keys_[i];
	delete[] keys_;
	keys_  = new_keys;
	qkeys_ = new_size;
}

template <class T>
size_t KeyList<T>::Size() { return qkeys_; }

template <class T>
bool KeyList<T>::IsEmpty() { return (qkeys_ == 0); }

template <class T>
T KeyList<T>::operator[](size_t index) { 
	if (index > qkeys_) throw "Out of index";
	return keys_[index]; 
}

template <class T>
void KeyList<T>::operator=(const KeyList& other) {
	delete[] keys_;
	qkeys_ = other.qkeys_;
	keys_  = new T[qkeys_];
	for (size_t i = 0; i < qkeys_; ++i) {
		keys_[i] = other.keys_[i];
	}
}

template <class U>
ostream& operator<<(ostream& out, KeyList<U>& keylist) {
	out << "KeyList Object: [";
	for (size_t i = 0; i < keylist.qkeys_; ++i) {
		out << "key " << i + 1 << " : " << keylist.keys_[i] << ", ";
	}
	out << "\b\b]";
	return out;
}

template <class T>
KeyList<T> KeyList<T>::Sub(size_t nokeys) {
	if (nokeys > qkeys_)
		return *this;

	KeyList sublist;
	sublist.qkeys_ = nokeys;
	sublist.keys_  = new T[nokeys];

	for (size_t i = 0; i != nokeys; ++i) {
		sublist.keys_[i] = keys_[i];	
	}
	return sublist;
}

}

#endif
