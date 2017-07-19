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

#ifndef CRYDI3_KEYLIST_DEF_H
#define CRYDI3_KEYLIST_DEF_H

#include "crydi3_tools.h"

namespace crydi {

template <class T>
class KeyList {
	private:
		T*			keys_;
		size_t  qkeys_;
		size_t  index_;
		bool    changing_keys_;

	public:
		KeyList();
		KeyList(initializer_list<T> list);
		KeyList(const KeyList& other);
		~KeyList();

		void   SetKeys(T key);

		template <typename... Args>
		void   SetKeys(T key, Args... args);

		void   ExpandTo(size_t new_size);
		size_t Size();
		bool	 IsEmpty();

		T       operator[](size_t index);
    const T operator[](size_t index) const;
		void operator=(const KeyList& other);
    bool operator==(const KeyList& other);
    bool operator!=(const KeyList& other);

		KeyList Sub(size_t nokeys);

		template <class U>
		friend ostream& operator<<(ostream& out, KeyList<U>& keylist);
};

}
#endif
