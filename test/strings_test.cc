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

#include "crydi3.h"

using namespace std;
using namespace NTL;

int main() {
  string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789! ";
  string msg_1  = "Hello world!";

  cout << crydi::MsgToNumForm(msg_1, alpha) << endl;

  string msg_2 = "Hello spaces          ";
  cout << msg_2 << ".\n";
  cout << msg_2.size() << endl;

  cout << crydi::CleanMsg(' ', msg_2, alpha) << ".\n";
  cout << crydi::CleanMsg(' ', msg_2, alpha).size() << endl;

  string num_form = crydi::MsgToNumForm(msg_2, alpha);
  cout << num_form << endl;
  cout << crydi::CleanNumForm(' ', num_form, alpha) << endl;
  return 0;
}
