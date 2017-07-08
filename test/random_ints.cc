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

#include "../src/inc/crydi3.h"

using namespace std;

int main(int argc, char *argv[]) {
  int number_int;
  cout << "Generated random ints\n";
  for (int i = 0; i < 250; ++i) {
    number_int = crydi::GenRandomInt(5000);
    cout << number_int << " \n";
  }

  long number_long;
  cout << "Generated random longs\n";
  for (int i = 0; i < 250; ++i) {
    number_long = crydi::GenRandomLong(2356356);
    cout << number_long << " \n";
  }

  return 0;
}
