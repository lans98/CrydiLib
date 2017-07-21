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

#ifndef CRYDI3_STRING_TOOLS_H
#define CRYDI3_STRING_TOOLS_H

#include <string>
#include <sstream>

namespace crydi {

using namespace std;

using ssize_t = string::size_type;
using strit_t = string::iterator;
using cstrit_t = string::const_iterator;

/**
 * Convert any number (if implemented with stream types) to string
 * @param num
 */
template <class T>
string NumberToString(const T& num) {
	stringstream sstr;
	sstr << num;
	string number_string;
	sstr >> number_string;
	return number_string;
}

/**
 * Convert string (if implemented with stream stypes) to any number type
 * @param num
 */
template <class T>
T StringToNumber(const string& num) {
	stringstream sstr(num);
	T number_type;
	sstr >> number_type;
	return number_type;
}

/**
 * Convert an digit to char
 * @param digit
 */
template <class T>
char NumberToChar(const T& digit) {
	return digit + '0';
}

/**
 * Convert a char to digit
 * @param digit
 */
template <class T>
T CharToNumber(const char digit) {
	return digit - '0';
}

/**
 * Get the id for a char in the desired alpha as string
 * (ex. alpha is "abcd...z" , wants to get 'b' returns "01")
 */
string GetIdFor(const char& chr, const string& alpha);

/**
 * Function to convert any message to its representation in
 * the desired alpha identifiers
 * (ex. "hi" with alpha = "abcd....z" goes to "0708")
 */
string MsgToNumForm(const string& msg, const string& alpha);

/**
 * Function to convert any numerical form string to its
 * normal representation in the desired alpha
 * (ex. "0708" with alpha = "abcd....z" goes to "hi")
 */
string NumFormToMsg(const string& msg, const string& alpha);

/**
 * Clean the actual message at the end from the less significant character
 * in the given alpha.
 * (ex. "Hello     " goes to "Hello", with char ' ' and alpha "abcd...z ", note ' ' in alpha)
 */
string CleanMsg(const char& chr, const string& msg, const string& alpha);

/**
 * Clean the numeric form at the end from the less significant character
 * in the given alpha.
 * (ex. "010203262626" goes to "010203", with char ' ' as "26" and alpha "abcd...z ",
 * note ' ' in alpha)
 */
string CleanNumForm(const string& id, const string& msg, const string& alpha);

}

#endif
