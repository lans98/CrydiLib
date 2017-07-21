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

#include "inc/crydi3_tools.h"
#include "inc/strings_tools.h"

namespace crydi {


string GetIdFor(const char& chr, string alpha) {
  unsigned long last_size = NumberToString(alpha.size() - 1).size();

  ssize_t id_int = alpha.find(chr);
  if (id_int == string::npos) throw NotFoundedInAlpha();

  string  id_str = NumberToString(id_int);
  if (id_str.size() < last_size)
    id_str = string(last_size - id_str.size(), '0') + id_str;

  return id_str;
}


string MsgToNumForm(string msg, string alpha) {
  // First get the number of digits of the representation
  // of the last character in the given alpha.
  unsigned long last_size = NumberToString(alpha.size() - 1).size();

  string  id_str;

  string num_form("");

  for (strit_t ch = msg.begin(); ch != msg.end(); ++ch) {
    // GetIdFor can throw an exception
    id_str = GetIdFor(*ch, alpha);

    num_form += id_str;
  }
  return num_form;
}

string NumFormToMsg(string msg, string alpha) {
  // First get the number of digits of the representation
  // of the last character in the given alpha.
  unsigned long last_size = NumberToString(alpha.size() - 1).size();

  ssize_t id_int;
  string  id_str;

  string msg_form("");

  for (unsigned long i = 0; i < msg.size(); i += last_size) {
    id_str = msg.substr(i, last_size);
    id_int = StringToNumber<ssize_t>(id_str);

    // alpha.at(x) may throw if not founded index
    msg_form += alpha.at(id_int);
  }
  return msg_form;
}


}
