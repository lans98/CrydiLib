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

using namespace NTL;
using namespace std;

int main(int argc, char* argv[]) {
  crydi::KeyList<ZZ> rsa_keys =crydi::GenRSAKeys(1024);
  crydi::RSACrypto<ZZ> rsa("abcdefghijklmnopqrstuvwxyz ", rsa_keys);
  cout << "Public key (share this): " << rsa.GetPublicKey() << endl;
  cout << "Share it with : " << rsa.GetModulus() << endl;
  cout << "Private key (never share this): " << rsa.GetPrivateKey() << endl;
  string msg = "vamo a jugah papu";

  cout << "Mensaje original: " << msg << endl;
  msg = rsa.Encrypt(msg);
  cout << "Encrypted message: " << msg << endl;
  msg = rsa.Decrypt(msg);
  cout << "Decrypted message: " << msg << endl;
  return 0;
}
