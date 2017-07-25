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
  crydi::KeyList<ZZ> rsa_a = crydi::GenRSAKeys(1024);
  crydi::KeyList<ZZ> rsa_b = crydi::GenRSAKeys(1024);
  crydi::KeyList<ZZ> elgammal_keys = crydi::GenElgammalKeys(1024);

  string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789! ";
  string firm  = "Kevin Del Castillo Ramirez 20163419";
  string msg   = "Hola mundo!";

  crydi::DigitalFirm<ZZ> dig_sig(alpha, rsa_a, rsa_b, elgammal_keys, firm);

  printf("Mensaje inicial: %s\n", msg.c_str());

  msg = dig_sig.Encrypt(msg);
  printf("Mensaje encriptado: %s\n", msg.c_str());

  msg = dig_sig.Decrypt(msg);
  printf("Mensaje desencriptado: %s\n", msg.c_str());

  return 0;
}
