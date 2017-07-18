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

int main(int argc, char *argv[]) {
  uintmax_t rand_num;
  for (int i = 0; i < 25; ++i) {
    rand_num = crydi::GenRandomLong(numeric_limits<uintmax_t>::max());
    cout << rand_num << endl;
  }

  NTL::ZZ rand_zz = crydi::GenRandomZZ(1024);
  cout << rand_zz << endl;
  cout << crydi::CountBits(rand_zz) << endl;

  NTL::ZZ prime_zz = crydi::GenRandomZZPrime(512);
  cout << prime_zz << endl;

  return 0;
}
